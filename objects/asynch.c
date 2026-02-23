 #include "asynch.h"

/*

Asynchronous:
Movement 
Jump: (W) applies velocity of 400 pixels/second
After Jump is triggered when input is held maintain ~300 pixel/second acceleration downward when released acceleration increases to ~700 pixels/second
Left, right.(A / D) Move 3 pixels per tick either way. If a player attempts to walk into a v-environment (aka wall), they are [either pushed back by the same or greater strength, or the movement is canceled before it happens]. Movement is still possible even while jumping or falling. When input is released velocity is set to 0.

Attack (mouse click)
The sword is summoned in the player's last input direction. Slash animations last 35ticks after which the object disappears and can be used again
The hurt box of the attack interacts with enemies only if there is collision of any amount
The size stays the same throughout the animation
Position moves relative to the player


Asynchronous (Input) Events
Event Name          Trigger Input Event         Description
Attack Request      Space bar is pressed        Will set Attacking to 1
Jump Request        “W” key is pressed          Will set players vertical velocity to positive 400 pixels/second 
Move Right Request  “D” key is pressed          Will set players horizontal velocity to positive 200 pixels/second 
Move Left Request   “A” key is pressed          Will set players horizontal velocity to negative 200 pixels/second
Quit                ESC key is pressed          Sets end game flag




*/