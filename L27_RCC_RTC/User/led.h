#ifndef __LED_H__
#define __LED_H__





void LED_GPIO_Init(void);  // gpio输出 IO配置
void LED_Out (void);       //led 输出 
void MCO_PA8_GPIO_Init(void);     //配置MCO 端口 PA8 模式配置  
void LEDout_P15_GPIO_Init(void) ; //配置PA15  端口 PA8 模式配置 led点亮输出
#endif
