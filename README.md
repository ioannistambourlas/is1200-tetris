# Tetris on RISC-V

Tetris we made for IS1200 Computer Hardware Engineering at KTH. Written in C and runs on the DTEK-V board without an OS.

## What it does
- Shows the game on a VGA screen
- Score shows on the 7-segment displays
- Next piece preview
- Runs a short performance test before the game starts

## Controls
- SW1: move left
- SW0: move right
- Button: rotate / restart after game over

## How to run
- Connect the board with USB and a screen to the VGA port
- Run `make`
- Run `dtekv-run main.bin`

## Files
- main.c: game loop
- board.c: game rules, moving, rotating, clearing lines, score
- pieces.c: the shapes
- render.c / vga.c: drawing on the screen
- io.c: timer, switches, button, displays
- perf.c: performance tests

## Made by
Ioannis Tambourlas and Antreas
