# Relevant Information

This project implements CLI interface for stm32f303k8 board.

# Configuration

- If you use other board, check on which uart interface usb is connected. If interface number is 2 follow below steps. Otherwise just change the index in configuration process.
- Uart can be initialized with STM32CubeMX according to [this](https://www.youtube.com/watch?v=d6MZHdgCQx0) video.
- Copy files from the repo to Core/src directory.

# Manual 

CLI application offers following commands:

- `ip`: shows ip addres of the board
