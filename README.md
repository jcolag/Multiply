# Multiply
A simple multiplication-based multiplication puzzle.

___NOTE___: This is _very_ old code.  Like a lot of old projects, I'll try to whip it into a coherent shape, but it's fairly certain that there are no comments, terrible naming conventions, poor organization, and very possibly significant bugs.

_Multiply_ is a simple puzzle game, where the user can guess and deduce which letters (`A` through `J`) map to which digits (`0` through `9`).  Running the program produces the following:

      HJD
    x  CF
    -----
    FBEDD
    (0 guesses - 0 wrong)
    
     > 

While I'm certain this idea isn't at all original to me in any respect, I don't recall where I first saw it, and have written and lost several versions, over the years.

## Usage

_Multiply_ makes use of several command-line arguments.

| Short Form | Long Form | Description |
| :--------- | :-------- | :---------- |
| __`-h`__   | `--help` | Show program usage |
| __`-p`__ ___X___ | `--use-padding=`_X_ | Pad out each character with _X_ spaces |
| __`-s`__   | `--show-intermediate` | Shows intermediate products, providing more information |

There are also certain commands within the game.

| Command | Description |
|:-------:|:----------- |
| __L__ | Print this help                    |
| __N__ | Print solved numbers               |
| __Q__ | Quit the game                      |
| __R__ | Restart the game with a new puzzle |
| __S__ | Toggle intermediate results        |

Note that the letters used for commands aren't entirely obvious because they would otherwise conflict with letters (__A__-__J__) used for substitution.

