Welcome to our TETRIS game!!!!


HOW TO BUILD AND RUN

1. Plug the board into your computer with USB and connect a
   screen to the VGA port.

2. Check that the computer can see the board:
       jtagconfig

3. If ithere is an error, run:
       killall jtagd
       jtagconfig

4. In this folder, press KEY0 on the board and then build the game:
       make

5. Send it to the board:
       dtekv-run main.bin

6. A short performance test runs first and prints its results
   in the terminal.

7. When you see "Tests done. TIME TO PLAY!", the game starts on
   the screen.


HOW TO PLAY

1. SW1 moves the piece left when the state changes one cell.

2. SW0 moves the piece right when the state changes one cell.

3. The button rotates the piece.

4. A full row disappears and gives you one point.

5. Your score is shown on the 7-segment displays.

6. The game ends when there is no room for a new piece to fit on top of the current stack.

7. Press the button to play again.

