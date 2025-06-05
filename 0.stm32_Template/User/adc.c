#include  "adc.h"

void my_ADC_Init(void) 
{
	/*
    if you are not sure wheather you have enabled the ADC clock before configuring the ADC,
    you can disable the ADC clock first and then enable it after configuring the ADC
    to make sure the new configuration takes effect.
    */
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC3, DISABLE);
	RCC_ADCCLKConfig(RCC_PCLK2_Div6);
    // 使能ADC1和GPIOA时钟
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC3 | RCC_APB2Periph_GPIOF, ENABLE);

    // 配置GPIOA的PA0为模拟输入
    GPIO_InitTypeDef GPIO_InitStructure;
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;  // 模拟输入模式
    GPIO_Init(GPIOF, &GPIO_InitStructure);
    // 配置ADC参数
    ADC_InitTypeDef ADC_InitStructure;
    ADC_InitStructure.ADC_Mode = ADC_Mode_Independent;
    ADC_InitStructure.ADC_ScanConvMode = DISABLE;             // 扫描模式
    ADC_InitStructure.ADC_ContinuousConvMode = DISABLE;     // 单次转换
    ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;
    ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;
    ADC_InitStructure.ADC_NbrOfChannel = 1;
    ADC_Init(ADC3, &ADC_InitStructure);

    // 配置ADC通道
    ADC_RegularChannelConfig(ADC3, ADC_Channel_6, 1, ADC_SampleTime_55Cycles5);  // 通道0，第1次转换，采样时间为1.5周期

    // 使能ADC3
    ADC_Cmd(ADC3, ENABLE);

    // calibration ADC
    ADC_ResetCalibration(ADC3);
    while(ADC_GetResetCalibrationStatus(ADC3));
    ADC_StartCalibration(ADC3);
    while(ADC_GetCalibrationStatus(ADC3));
}
