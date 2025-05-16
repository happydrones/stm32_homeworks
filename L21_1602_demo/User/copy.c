#include <stdio.h> // 用于 sprintf 函数

void Display_Time_LCD1602(u8 X_1602, u8 Y_1602, u8 Hours, u8 Minutes, u8 Seconds) {
    char timeBuffer[10]; // 缓冲区，用于存储时间字符串（包含 \0）
    
    // 将时间格式化为 "HH-MM-SS"
    sprintf(timeBuffer, "%02d-%02d-%02d", Hours, Minutes, Seconds);

    // 调用 Display_Lcd_1602 函数显示
    Display_Lcd_1602(X_1602, Y_1602, (u8 *)timeBuffer, 8); // 显示时间（长度为8）
}

int main(void) {
    // 示例调用
    u8 Hours = 0;
    u8 Minutes = 0;
    u8 Seconds = 0;

    // 假设显示在 LCD 第一行，起始位置第1列
    Display_Time_LCD1602(1, 0, Hours, Minutes, Seconds);

    // 示例时间更新（随实际需求更新时间变量）
    Hours = 12;
    Minutes = 30;
    Seconds = 45;

    Display_Time_LCD1602(1, 0, Hours, Minutes, Seconds);

    while (1) {
        // 你的主程序逻辑
    }

    return 0;
}
