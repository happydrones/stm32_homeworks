#ifndef __W25Q128_H
#define __W25Q128_H

// 包含 STM32F10x 标准库的主头文件
#include "stm32f10x.h"

// CS 片选引脚的宏定义 (PB12)
#define W25Q_CS_PIN         GPIO_Pin_12
#define W25Q_CS_PORT        GPIOB
#define W25Q_CS_SELECT()    GPIO_ResetBits(W25Q_CS_PORT, W25Q_CS_PIN)
#define W25Q_CS_DESELECT()  GPIO_SetBits(W25Q_CS_PORT, W25Q_CS_PIN)


/* W25Q128 Flash Memory 参数宏定义 */
#define W25Q128_FLASH_SIZE      0x1000000   // 16 MBytes
#define W25Q128_SECTOR_SIZE     0x1000      // 4 KBytes
#define W25Q128_PAGE_SIZE       0x100       // 256 Bytes

#define W25Q128_DUMMY_BYTE      0xA5

/* W25Q128 指令集 */
#define WRITE_ENABLE_CMD        0x06
#define WRITE_DISABLE_CMD       0x04
#define READ_STATUS_REG1_CMD    0x05
#define READ_STATUS_REG2_CMD    0x35
#define WRITE_STATUS_REG_CMD    0x01
#define PAGE_PROGRAM_CMD        0x02
#define SECTOR_ERASE_CMD        0x20
#define BLOCK_ERASE_64K_CMD     0xD8
#define CHIP_ERASE_CMD          0xC7
#define READ_DATA_CMD           0x03
#define JEDEC_ID_CMD            0x9F

/**
  * @brief  W25Q128 驱动核心函数
  */

/**
  * @brief  初始化W25Q128芯片 (包含SPI和GPIO的初始化)
  * @retval 0: 成功, 1: 失败
  */
uint8_t W25Q_Init(void);

/**
  * @brief  读取W25Q128的JEDEC ID
  * @param  None
  * @retval uint32_t: 芯片的JEDEC ID (例如: 0xEF4018)
  */
uint32_t W25Q_Read_JEDEC_ID(void);

/**
  * @brief  从指定地址开始读取数据
  * @param  pBuffer: 指向存储读取数据的缓冲区
  * @param  ReadAddr: 读取的起始地址 (0 ~ 16M-1)
  * @param  NumByteToRead: 要读取的字节数
  * @retval None
  */
void W25Q_Read_Buffer(uint8_t* pBuffer, uint32_t ReadAddr, uint16_t NumByteToRead);

/**
  * @brief  在指定地址开始写入数据 (最大65535字节)
  * @note   写入前必须确保目标区域已被擦除
  * @param  pBuffer: 指向包含要写入数据的缓冲区
  * @param  WriteAddr: 写入的起始地址 (0 ~ 16M-1)
  * @param  NumByteToWrite: 要写入的字节数
  * @retval None
  */
void W25Q_Write_Buffer(uint8_t* pBuffer, uint32_t WriteAddr, uint16_t NumByteToWrite);

/**
  * @brief  擦除一个扇区 (4KB)
  * @param  SectorAddr: 要擦除的扇区的地址，地址不需要对齐，函数内部会自动处理
  * @retval None
  */
void W25Q_Erase_Sector(uint32_t SectorAddr);

/**
  * @brief  擦除一个块 (64KB)
  * @param  BlockAddr: 要擦除的块的地址
  * @retval None
  */
void W25Q_Erase_Block(uint32_t BlockAddr);

/**
  * @brief  擦除整片芯片
  * @note   此操作非常耗时，大约需要几十秒到几分钟
  * @retval None
  */
void W25Q_Erase_Chip(void);

#endif /* __W25Q128_H */
