#include "synch.h"

/*
Synchronous:
Inquire floor: check for floor under entities. If found vertical velocity is set to 0. If not found, add downward acceleration at 300 pixels per second.
Inquire wall: when moving, check for walls ahead of entities in the direction of travel. If a wall is detected horizontal velocity is set to 0.
Timer: increments by 1 second  until seconds reach 59 at which point the next increment will set seconds to 0 and increment minutes by 1

Synchronous (Timed) Events

*/

/*
Every second:
- Increment Timer (every 70 ticks(frames))
- Lower Attack count down

Every movement frame (.5 seconds):
- Move player according to horizontal velocity
- Move player accoring to jump (vertical) velocity
- If player not on ground, make player fall
- Move enemy one step forward
- 

*/