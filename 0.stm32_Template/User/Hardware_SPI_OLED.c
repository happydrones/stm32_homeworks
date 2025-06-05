#include  "Hardware_SPI_OLED.h"


void SPI_OLED_Init(void)
{
    //Initialize SPI
    SPI_InitTypeDef  SPI_InitStructure;
    GPIO_InitTypeDef GPIO_InitStructure;

    //Enable the SPI clock
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_SPI1, ENABLE);

    //Enable the GPIOA clock
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA |RCC_APB2Periph_AFIO, ENABLE);

    //Configure the GPIOA pins
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4 | GPIO_Pin_5 | GPIO_Pin_6 | GPIO_Pin_7 ;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA, &GPIO_InitStructure);
    //Configure the SPI pins
    SPI_InitStructure.SPI_Direction = SPI_Direction_1Line_Tx;  //Tx only
    SPI_InitStructure.SPI_Mode = SPI_Mode_Master;
    SPI_InitStructure.SPI_DataSize = SPI_DataSize_8b;
    SPI_InitStructure.SPI_CPOL = SPI_CPOL_High;   //根据从设备选择，高电平或低电平
    SPI_InitStructure.SPI_CPHA = SPI_CPHA_2Edge;  //第二个边缘采样
    SPI_InitStructure.SPI_NSS = SPI_NSS_Soft;
    SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_2;
    SPI_InitStructure.SPI_FirstBit = SPI_FirstBit_MSB;
    SPI_Init(SPI1, &SPI_InitStructure);
    //confige the other pins
 	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);	 //使能A端口时钟
	GPIO_InitStructure.GPIO_Pin   =	GPIO_Pin_0| GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3 ;	 
 	GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_Out_PP; 		 //推挽输出
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;			//速度50MHz
 	GPIO_Init(GPIOA, &GPIO_InitStructure);	

}    
