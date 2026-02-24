#include "synch.h"

/*
Synchronous (Timed) Events
*/

/*
Every second:
- Increment Timer (every 70 ticks(frames)?)

Every movement frame (.5 seconds):
- Move player according to horizontal velocity
- Move player according to jump (vertical) velocity
- If player not grounded, fall according to vertical velocity
- If player not on ground, make player fall
- Move enemy one step forward
- Lower Attack count down (Max is set in attack function)

Every frame:
- Check if there is a floor under the player. Set grounded value accordingly
- Check if there is a wall in front of the player according to the horizontal velocity. If so, set horizzontal velocity = 0;
*/

