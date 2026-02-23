#ifndef ROOM_DOOR_H
#define ROOM_DOOR_H
#include "TYPES.H" /* for bool, UINT and LEFT/RIGHT */

typedef enum {
    VERTICAL,
    HORIZONTAL,
};

typedef struct room_door{
    UINT16 x, y;
    int size;           /* if type VERTICAL: grow from top most side. Example at position (5,10) and size 10, end point will be (5,20)*/
    int type;          /* if type HORIZONTAL: grow from left most side. Example at position (5,10) and size 10, end point will be (15,10)*/
}Exit;

Exit create_exit(UINT16 x, UINT16 y, int size, int type);

void print_exit_status(Exit e);

#endif