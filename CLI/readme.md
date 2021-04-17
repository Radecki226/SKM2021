# Relevant Information

This project implements CLI interface for stm32f303k8 board.

# Configuration

- If you use other board, check on which uart interface usb is connected. If interface number is 2 follow below steps. Otherwise just change the index in configuration process.
- Uart can be initialized with STM32CubeMX according to [this](https://www.youtube.com/watch?v=d6MZHdgCQx0) video. Set uart to 9600.
- Initialize TIM3 timer to generate interrupts approximately every 1 second.
- Copy files from the repo to Core/src directory.
- Add files to project.

# Manual 

Connect board to PC via USB, run terminal, choose port and set baud rate to 9600 and enjoy the app!

CLI application offers following commands:

- `ip`: shows ip addres of the board
- `info` : shows information about the board
- `help` : shows available commands
- `monitor` : shows current monitor status
