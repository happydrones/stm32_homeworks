#ifndef __STACK_H
#define __STACK_H

#include "stm32f10x.h"
#include <stddef.h>  // 包含NULL定义


#define STACK_MAX_SIZE  64  // 可以根据实际需要修改大小

typedef struct {
    int data[STACK_MAX_SIZE];  // 存储数据的数组
    int top;                   // 栈顶索引，初始为 -1
} Stack_t;

// 初始化栈
void Stack_Init(Stack_t *stack);

// 判断栈是否为空
ErrorStatus Stack_IsEmpty(const Stack_t *stack);

// 判断栈是否已满
ErrorStatus Stack_IsFull(const Stack_t *stack);

// 压栈操作（返回 true 表示成功，false 表示失败）
ErrorStatus Stack_Push(Stack_t *stack, int value);

// 弹栈操作（返回 true 表示成功，false 表示失败）
ErrorStatus Stack_Pop(Stack_t *stack, int *value);

// 读取栈顶元素但不弹出（返回 true 表示成功）
ErrorStatus Stack_Peek(const Stack_t *stack, int *value);

#endif // STACK_H
