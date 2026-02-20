#include "door.h"
#include <stdio.h>

void print_exit_status(Exit e){
    printf("X:%d, Y:%d, Size:%d, Type:%d.\n", e.x,e.y,e.size,e.type);
};

Exit create_exit(UINT16 x, UINT16 y, int size, int type){
    Exit e;
    e.x = x;
    e.y =y;
    e.size = size;
    e.type = type;
    return e;
};

/*
int main(){
    Exit e = create_exit(150,300,100,VERTICAL);
    print_status(e);
    return 0;
};*/