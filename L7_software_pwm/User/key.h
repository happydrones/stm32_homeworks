#ifndef __KEY_H__
#define __KEY_H__


#include "stm32f10x.h"


//按键结构体
struct key_struct
{
    GPIO_TypeDef* GPIO_Group;
    uint16_t GPIO_Pin;
    uint8_t key_flag;
};

//创建四个独立按键
extern struct key_struct up_key    ;
extern struct key_struct down_key  ;
extern struct key_struct left_key  ;
extern struct key_struct right_key ;
extern struct key_struct common_Pin;


void Common_Pin_Init(struct key_struct* Key);
void Key_Init(struct key_struct* Key);
void Key_Scan(struct key_struct* Key);



#endif 
