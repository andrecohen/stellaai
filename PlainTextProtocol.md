## Overview ##

The plain text protocol is the most generic and versatile way to control StellaAI. After the completion of each emulator cycle StellaAI listens for commands from a client. The client can request things such as the contents of the screen and also send key presses that will be used in the next game cycle. The server/client communication continues until the `NEXT` command is sent by the client which indicates StellaAI should proceed to the next cycle.

## The Protocol ##

All communication uses the same format of packets: `[counter][data type][length][data]`.

  * The _counter_ is used to make sure that no command is dropped or delayed. It is an integer incremented by the client and begins at `1`.
  * he _data type_ indicates what type of data the packet carries. A character (char) is used to represent the type  of data being sent: `s` for string, `i` for integer, `r` for 2D matrix.
  * Depending on the type the _length_ (integer) is different. Strings send the length of the string being sent, integers send sizeof(int), and matrixes send two integers corresponding to the number of rows and columns.

### Packet Summary ###

  * **Integer:** `[counter][i][4][value]`
  * **String:** `[counter][s][length][value]`
  * **Matrix:** `[counter][r][columns][rows][value]`

## Conversing ##

After each command received by StellaAI a integer packet is sent back to the client with the value of the counter received. This is to ensure that the packet order is correct. Depending on the command sent StellaAI may also send one or more packets with data.

## Commands ##
  * `FULL_SCREEN` - Sends the full screen back to the client as a 2D matrix.
  * `DIFF_SCREEN` - Sends a 'diff' of the screen since the last time a screen related command was requested. A 2D matrix is sent back with coordinates and new colors.
  * `PREV` - Retrieves state from saved states in FIFO stack (not yet implemented)
  * `SAVE` - Saves the state of the game in a FIFO stack (not yet implemented)
  * `DUMP` - Sends 2D matrix of the RAM (not yet implemented)
  * `RESET` - Unpresses all keys (note that until this command is issued key presses remain pressed over game cycles)
  * `UP` - Simulates the up arrow being pressed
  * `DOWN` - Simulates the down arrow being pressed
  * `LEFT` - Simulates the left arrow being pressed
  * `RIGHT` - Simulates the right arrow being pressed
  * `SPACE` - Simulates the space arrow being pressed
  * `NEXT` - Tells StellaAI to proceed to the next frame
  * `QUIT` - Quits StellaAI (gracefully)