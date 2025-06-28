#include "w25q128.h"



/* --------------------------- private functions --------------------------- */

/**
  * @brief  SPI2 hardware initialization (private function)
  * @note   The pin configuration of SPI2 is as follows:
  *         SCK: PB13
  *         MISO: PB14
  *         MOSI: PB15
  *         CS: PB12
  */
static void W25Q_SPI_Init(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;
    SPI_InitTypeDef  SPI_InitStructure;

    // 1. Enable GPIOB and SPI2 clocks
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_SPI2, ENABLE);

    // 2. Configure SPI2 pins: SCK(PB13), MISO(PB14), MOSI(PB15)
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP; // Alternate function push-pull
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOB, &GPIO_InitStructure);
    
    // 3. Configure CS select pin: PB12
    GPIO_InitStructure.GPIO_Pin = W25Q_CS_PIN;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; // Push-pull output
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(W25Q_CS_PORT, &GPIO_InitStructure);

    // Initialize with CS high, not selecting any device
    W25Q_CS_DESELECT();

    // 4. Configure SPI2 parameters
    SPI_InitStructure.SPI_Direction = SPI_Direction_2Lines_FullDuplex; // Full duplex
    SPI_InitStructure.SPI_Mode = SPI_Mode_Master;                      // Master mode
    SPI_InitStructure.SPI_DataSize = SPI_DataSize_8b;                  // 8-bit data
    SPI_InitStructure.SPI_CPOL = SPI_CPOL_High;                        // Clock polarity: high (Mode 3)
    SPI_InitStructure.SPI_CPHA = SPI_CPHA_2Edge;                       // Clock phase: sample on the second edge (Mode 3)
    SPI_InitStructure.SPI_NSS = SPI_NSS_Soft;                          // Software NSS management
    // Baud rate setting: 72MHz / 4 = 18MHz
    SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_4; 
    SPI_InitStructure.SPI_FirstBit = SPI_FirstBit_MSB;                 // MSB first
    SPI_InitStructure.SPI_CRCPolynomial = 7;
    SPI_Init(SPI2, &SPI_InitStructure);

    // 5. Enable SPI2
    SPI_Cmd(SPI2, ENABLE);
}

/**
  * @brief  Send and receive a byte via SPI (blocking)
  */
static uint8_t SPI_SendReceiveByte(uint8_t byte_to_send)
{
    // Wait for the transmission buffer to be empty (TXE)
    while (SPI_I2S_GetFlagStatus(SPI2, SPI_I2S_FLAG_TXE) == RESET);
    
    // Send a byte
    SPI_I2S_SendData(SPI2, byte_to_send);

    // Wait for the reception buffer to be non-empty (RXNE)
    while (SPI_I2S_GetFlagStatus(SPI2, SPI_I2S_FLAG_RXNE) == RESET);

    // Return the received byte
    return SPI_I2S_ReceiveData(SPI2);
}

/**
  * @brief  Send "Write Enable" command
  */
static void W25Q_Write_Enable(void)
{
    W25Q_CS_SELECT();
    SPI_SendReceiveByte(WRITE_ENABLE_CMD);
    W25Q_CS_DESELECT();
}

/**
  * @brief  Poll the status register, wait for BUSY bit to be cleared
  */
static void W25Q_Wait_Busy(void)
{
    uint8_t status = 0;
    W25Q_CS_SELECT();
    SPI_SendReceiveByte(READ_STATUS_REG1_CMD);
    do {
        status = SPI_SendReceiveByte(W25Q128_DUMMY_BYTE);
    } while ((status & 0x01) == 0x01); // Check BUSY bit (S0)
    W25Q_CS_DESELECT();
}

/**
  * @brief  Write a page of data to W25Q128 (up to 256 bytes)
  */
static void W25Q_Write_Page(uint8_t* pBuffer, uint32_t WriteAddr, uint16_t NumByteToWrite)
{
    W25Q_Write_Enable();
    W25Q_CS_SELECT();
    
    // Send page programming command
    SPI_SendReceiveByte(PAGE_PROGRAM_CMD);
    // Send 24-bit address
    SPI_SendReceiveByte((WriteAddr >> 16) & 0xFF);
    SPI_SendReceiveByte((WriteAddr >> 8) & 0xFF);
    SPI_SendReceiveByte(WriteAddr & 0xFF);
    
    // Loop to send data
    while (NumByteToWrite--)
    {
        SPI_SendReceiveByte(*pBuffer);
        pBuffer++;
    }
    
    W25Q_CS_DESELECT();
    W25Q_Wait_Busy();
}

/* --------------------------- public functions --------------------------- */

/**
  * @brief  Initialize W25Q128 chip (includes SPI and GPIO initialization)
  * @retval 0: Success, 1: Chip ID error
  */
uint8_t W25Q_Init(void)
{
    // Initialize SPI2 hardware
    W25Q_SPI_Init();
    
    uint32_t jedec_id = W25Q_Read_JEDEC_ID();
    
    // Check if the read ID is correct (W25Q128's ID is EF4018)
    if ((jedec_id & 0x00FFFFFF) == 0xEF4018) {
        return 0; // Success
    }
    
    return 1; // Failure
}

/**
  * @brief  Read the JEDEC ID of W25Q128
  */
uint32_t W25Q_Read_JEDEC_ID(void)
{
    uint32_t jedec_id = 0;
    uint8_t id_bytes[3];
    
    W25Q_CS_SELECT();
    
    SPI_SendReceiveByte(JEDEC_ID_CMD);
    id_bytes[0] = SPI_SendReceiveByte(W25Q128_DUMMY_BYTE); // Manufacturer ID
    id_bytes[1] = SPI_SendReceiveByte(W25Q128_DUMMY_BYTE); // Memory Type
    id_bytes[2] = SPI_SendReceiveByte(W25Q128_DUMMY_BYTE); // Capacity
    
    W25Q_CS_DESELECT();
    
    jedec_id = (id_bytes[0] << 16) | (id_bytes[1] << 8) | id_bytes[2];
    
    return jedec_id;
}

/**
  * @brief  Read data from the specified address
  */
void W25Q_Read_Buffer(uint8_t* pBuffer, uint32_t ReadAddr, uint16_t NumByteToRead)
{
    W25Q_CS_SELECT();
    
    // Send read command and 24-bit address
    SPI_SendReceiveByte(READ_DATA_CMD);
    SPI_SendReceiveByte((ReadAddr >> 16) & 0xFF);
    SPI_SendReceiveByte((ReadAddr >> 8) & 0xFF);
    SPI_SendReceiveByte(ReadAddr & 0xFF);

    // Loop to receive data
    while (NumByteToRead--)
    {
        *pBuffer = SPI_SendReceiveByte(W25Q128_DUMMY_BYTE);
        pBuffer++;
    }

    W25Q_CS_DESELECT();
}

/**
  * @brief  Write data to the specified address, the function will automatically handle page crossing
  */
void W25Q_Write_Buffer(uint8_t* pBuffer, uint32_t WriteAddr, uint16_t NumByteToWrite)
{
    uint16_t pageremain;
    pageremain = W25Q128_PAGE_SIZE - (WriteAddr % W25Q128_PAGE_SIZE);
    
    if (NumByteToWrite <= pageremain)
    {
        pageremain = NumByteToWrite;
    }
    
    while(1)
    {
        W25Q_Write_Page(pBuffer, WriteAddr, pageremain);
        NumByteToWrite -= pageremain;
        if (NumByteToWrite == 0)
        {
            break;
        }
        pBuffer += pageremain;
        WriteAddr += pageremain;
        pageremain = (NumByteToWrite > W25Q128_PAGE_SIZE) ? W25Q128_PAGE_SIZE : NumByteToWrite;
    }
}

/**
  * @brief  Erase a sector (4KB)
  */
void W25Q_Erase_Sector(uint32_t SectorAddr)
{
    W25Q_Write_Enable();
    W25Q_Wait_Busy();
    
    W25Q_CS_SELECT();
    SPI_SendReceiveByte(SECTOR_ERASE_CMD);
    SPI_SendReceiveByte((SectorAddr >> 16) & 0xFF);
    SPI_SendReceiveByte((SectorAddr >> 8) & 0xFF);
    SPI_SendReceiveByte(SectorAddr & 0xFF);
    W25Q_CS_DESELECT();
    
    W25Q_Wait_Busy();
}

/**
  * @brief  Erase a block (64KB)
  */
void W25Q_Erase_Block(uint32_t BlockAddr)
{
    W25Q_Write_Enable();
    W25Q_Wait_Busy();

    W25Q_CS_SELECT();
    SPI_SendReceiveByte(BLOCK_ERASE_64K_CMD);
    SPI_SendReceiveByte((BlockAddr >> 16) & 0xFF);
    SPI_SendReceiveByte((BlockAddr >> 8) & 0xFF);
    SPI_SendReceiveByte(BlockAddr & 0xFF);
    W25Q_CS_DESELECT();
    
    W25Q_Wait_Busy();
}

/**
  * @brief  Erase the entire chip
  */
void W25Q_Erase_Chip(void)
{
    W25Q_Write_Enable();
    W25Q_Wait_Busy();
    
    W25Q_CS_SELECT();
    SPI_SendReceiveByte(CHIP_ERASE_CMD);
    W25Q_CS_DESELECT();
    
    W25Q_Wait_Busy();
}
