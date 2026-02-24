 #include "asynch.h"

/*
Asynchronous:
Movement 
Jump: (W) applies velocity of 400 pixels/second
After Jump is triggered when input is held maintain ~300 pixel/second acceleration downward when released acceleration increases to ~700 pixels/second

When input is released velocity (horizontal and/or positive vertical) is set to 0.

Attack (mouse click)
The sword is summoned in the player's last input direction. Slash animations last 35ticks after which the object disappears and can be used again
The hurt box of the attack interacts with enemies only if there is collision of any amount

Asynchronous (Input) Events
*/

/*
Key bindings

"X":
Call attack function on player

"Space bar":
Call jump function

"D":
Call move(RIGHT) function on player

"A":
Call move(LEFT) function on player

"ESC":
Trap 0
(I think that quits the program 0w0?)

*/