#include "stack.h"

void Stack_Init(Stack_t *stack) {
    stack->top = -1;
}

ErrorStatus Stack_IsEmpty(const Stack_t *stack) {
    return (stack->top == -1) ? SUCCESS : ERROR;
}

ErrorStatus Stack_IsFull(const Stack_t *stack) {
    return (stack->top == STACK_MAX_SIZE - 1) ? SUCCESS : ERROR;
}

ErrorStatus Stack_Push(Stack_t *stack, int value) {
    if (Stack_IsFull(stack)) {
        return ERROR; // 栈满
    }
    stack->data[++(stack->top)] = value;
    return SUCCESS;
}

ErrorStatus Stack_Pop(Stack_t *stack, int *value) {
    if (Stack_IsEmpty(stack)) {
        return ERROR; // 栈空
    }
    if (value != NULL) {
        *value = stack->data[stack->top];
    }
    stack->top--;
    return SUCCESS;
}

ErrorStatus Stack_Peek(const Stack_t *stack, int *value) {
    if (Stack_IsEmpty(stack)) {
        return ERROR;
    }
    if (value != NULL) {
        *value = stack->data[stack->top];
    }
    return SUCCESS;
}
