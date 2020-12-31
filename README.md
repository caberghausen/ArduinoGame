# ArduinoGame
 
A 2-player Arduino game of predator and prey that uses a 5x7 hex display. One player uses a simple Java program to control the movement of a 2x2 "predator" dot with the arrow keys of a laptop, communicated to the Arduino via its USB serial port, while the other uses an accelerometer wired to the Arduino to control a faster, 1-pixel "prey" dot. Player 1 wins by overlapping the prey; Player 2 wins by evading the predator for 15 seconds. The hex display shows the score differential after each round and play continues until +/- 3 points.
