Things such as score and time left in a game, can be extremely difficult to extract from pixels alone. For that reason there is a special set of commands that can be used to retrieve such information.

  * `REWARD_SCORE` - The current score
  * `REWARD_TIME` - Time component of the game
  * `REWARD_LIVES` - Lives left in the current game

All of these commands may mean slightly different things from game to game and must be manually implemented for each game.

## Adding a new game ##

To add a new game first one must know where in the RAM the score, lives, and time are stored. There is no easy way to do this, with luck one execution of the following steps should be enough to find all the rewards.

  1. Start StellaAI with your favorite game. After a few seconds playing press `````. This will take you to the Debug console.
  1. The RAM is the rectangle on upper right of the screen.
  1. Look for numbers that reflect the time, score, and lives. Note that many times the numbers are not converted to hex, so if the score is currently 2000 then in the RAM you might see 20 and 00 next to each other. Make note of the possible addresses.
  1. Press ````` again to go back to the game. Play until things have changed some more and see which parts in the RAM have changed now.

Once the addresses have been figured out, you need to add them to the `rewards.txt` file which should be in the same directory as the StellaAI executable. The entry for Pitfall for instance looks like this:
```
ROM:	Pitfall.rom
SCORE:	d8 d9;
TIME:	d6 d7;
```

**Note:** There should be no empty lines except for the last line of the file.

**Note:** At the end of each reward line (ie. `SCORE, TIME, LIVES`) there should be a semicolon.

**Note:** Each reward is assumed to be a integer.