---

# RTC Clock Display with Keypad Control for STM32F10x

## Overview
This project demonstrates the implementation of a real-time clock (RTC) display using an STM32F10x microcontroller. The clock is displayed on a 1602 LCD, and the time can be adjusted using a matrix keypad.

## Features
- **Real-Time Clock (RTC):** Utilizes the RTC module of the STM32F10x to keep track of the current time accurately.
- **1602 LCD Display:** Displays the current date and time on a 1602 LCD screen.
- **Keypad Control:** Allows the user to adjust the time settings using a matrix keypad.
- **Setting Modes:**
  - **Normal Mode:** Displays the current time without any adjustments.
  - **Set Second Mode:** Allows the user to adjust the seconds.
  - **Set Minute Mode:** Allows the user to adjust the minutes.
  - **Set Hour Mode:** Allows the user to adjust the hours.
  - **Set Day Mode:** Allows the user to adjust the day.
  - **Set Month Mode:** Allows the user to adjust the month.
  - **Set Year Mode:** Allows the user to adjust the year.
- **Blinking Indicator:** The seconds display blinks to indicate that the clock is running.

## Components
- **STM32F10x Microcontroller:** The main processor.
- **1602 LCD Module:** Used to display the date and time.
- **Matrix Keypad:** Used for user input to adjust the clock settings.
- **LEDs:** Optional, for additional status indicators.
- **Delays:** Custom delay functions for timing control.

## Files and Structure
- **main.c:** The main source file containing the initialization and main loop of the project.
- **led.h:** Header file for LED control functions.
- **1602lcd.h:** Header file for 1602 LCD control functions.
- **delay.h:** Header file for custom delay functions.
- **sys_config.h:** Header file for system configuration settings.
- **rtc.h:** Header file for RTC control and initialization functions.
- **matrix_keypad.h:** Header file for matrix keypad initialization and scanning functions.

## Usage
1. **Initialization:**
   - Configure the system clock to 72 MHz using `RCC_Configuration()`.
   - Enable the clock security system using `RCC_ClockSecuritySystemCmd(ENABLE)`.
   - Initialize the RTC using `RTC_Config()`.
   - Initialize the matrix keypad using `Keypad_Init()`.
   - Initialize the 1602 LCD using `Lcd_1602_Init()`.

2. **Main Loop:**
   - In normal mode, the current time is continuously read from the RTC and displayed on the 1602 LCD.
   - Pressing the K13 key on the keypad enters setting mode.
   - In setting mode, pressing the direction keys adjusts the corresponding time parameter (seconds, minutes, hours, days, months, years).
   - The seconds display blinks to indicate active time adjustment.

3. **Setting Modes:**
   - **Set Second Mode:** Press K13 to enter, adjust seconds using direction keys, press K13 to exit.
   - **Set Minute Mode:** Adjust minutes using direction keys, press K8 to move to set hour mode, press K16 to move to set second mode, press K13 to exit.
   - **Set Hour Mode:** Adjust hours using direction keys, press K8 to move to set day mode, press K16 to move to set minute mode, press K13 to exit.
   - **Set Day Mode:** Adjust days using direction keys, press K8 to move to set month mode, press K16 to move to set hour mode, press K13 to exit.
   - **Set Month Mode:** Adjust months using direction keys, press K8 to move to set year mode, press K16 to move to set day mode, press K13 to exit.
   - **Set Year Mode:** Adjust years using direction keys, press K8 to exit, press K16 to move to set month mode, press K13 to exit.

## Notes
- Ensure that the `matrix_keypad.h` header file is included in `main.c` to avoid implicit declarations.
- The `Keypad_Init()` function must be properly declared in `matrix_keypad.h` to match its definition.
- The project uses a custom delay function for timing control, which should be defined in `delay.c` and declared in `delay.h`.

## License
This project is licensed under the MIT License. See the `LICENSE` file for more details.

## Author
- **Author:** Oscar
- **Date:** 2025-05-01

---