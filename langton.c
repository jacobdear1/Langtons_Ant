#include <stdio.h>
#include "langton.h"
#include "visualiser.h"

// "after the ant has left a square at state i, the squares state changes to i+1", add this

// struct ant contains an integer x and an integer y, so take these using pointers and an enum called direction
void turn_left(struct ant *ant){
    // want to take in the value of the direction and then change it to,
    // change direction to 'LEFT'

    // x and y will stay the same, just need to chaange direection?
    // int dir;
    // dir = ant->direction;
    // printf("value%d\n", dir);

    ant->direction = LEFT;

};


void turn_right(struct ant *ant){
    // takes in value of direction and then changes it to
    // change direction to 'Right'
    ant->direction = RIGHT;
};

void move_forward(struct ant *ant){
    
    int x_val, y_val;
    // takes in the direction that the ant is facing, needs to get the value of direction from the struct

    // as this will allow it to move one step
    
    // if it is moving left then decrement x by 1
    if(ant->direction == LEFT){
        x_val = ant->x;
        x_val = x_val - 1;
        ant->x = x_val;
    }

    // if it is moving right then increment x by 1
    if(ant->direction == RIGHT){
        x_val = ant->x;
        x_val = x_val + 1;
        ant->x = x_val;       
    }

    // if it is moving up then increment y by 1
    if (ant->direction == UP){
        y_val = ant->y;
        y_val = y_val + 1;
        ant->y = y_val;
    }

    // if it is moving down then decrement by 1
    if (ant->direction == DOWN){
        y_val = ant->y;
        y_val = y_val - 1;
        ant->y = y_val;
    }
    
    else{
        printf("A non-valid direction was given, so the program will now exit");
    }
};

void apply_rule(enum colour *colour, struct ant *ant){

// when colour = white, change direction to left, call turn_left function and then change colour to black?

// when colour = black, change direction to right, call turn_right function and then change colour to white?

// need to add the stars as this means that it will be able to used the value passed by the function?
    if(*colour == WHITE){
        turn_left(ant); 
        *colour = BLACK;
    }

    if(*colour == BLACK){
        turn_right(ant); 
        *colour = WHITE;
    }
    
};

// look at how to do first part with the enums and that

// then look at the grid and its topology, if you go one above the top most value then you go to the bottom row. If you go one, use a function?

// pass the x value from struct ant and compare this to the max value of grid. need to work out how to pass the max value from visualiser.c
