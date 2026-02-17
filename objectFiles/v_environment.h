#ifndef V_ENVIRONMENT_H
#define V_ENVIRONMENT_H

typedef struct v_environment{
    int x, y;
    int size; /* grow from top most side. Example at position (5,10) and size 10, end point will be (5,20)*/
}Wall;


#endif