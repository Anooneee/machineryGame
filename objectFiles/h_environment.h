#ifndef H_ENVIRONMENT_H
#define H_ENVIRONMENT_H

typedef struct h_environment{
    int x, y;
    int size; /* grow from left most side. Example at position (5,10) and size 10, end point will be (15,10)*/
}Floor;


#endif