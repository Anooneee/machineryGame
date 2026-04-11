#include "input.h"

volatile char mouse_state = 0;
volatile char mouse_header = 0;
volatile int mouse_coords[] = {0,0};
volatile char keyboard[128];
