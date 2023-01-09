#include <stdio.h>
#include <string.h>
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

    // want to change the ant to go 90 degrees clockwise, e.g. if the direction is left, then turning left would cause the ant to point down;

    if (ant->direction == LEFT){
        ant->direction = DOWN;
    }
    else{

        if (ant->direction == DOWN){
            ant->direction = RIGHT;
        }
        else{
        
            if (ant->direction == RIGHT){
                //printf("right");
                ant->direction = UP;
                //printf("dir changed?%d", ant->direction);
            }

            // direction changes, but for some reason when it is passed back it doesn't change?

            else{
                if (ant->direction == UP){
                    ant->direction = LEFT;
                }
            }
        }
    }
};


void turn_right(struct ant *ant){
    // takes in value of direction and then changes it to
    // change direction to 'Right'
    //enum direction dir_right = RIGHT;

    //ant->direction = dir_right;

    // want to change the ant to go 90 degrees clockwise, e.g. if the direction is left, then turning left would cause the ant to point down;

    if (ant->direction == LEFT){
        ant->direction = UP;
    }
    else{

        if (ant->direction == DOWN){
            ant->direction = LEFT;
        }
        else{
        
            if (ant->direction == RIGHT){
                //printf("right");
                ant->direction = DOWN;
                //printf("dir changed?%d", ant->direction);
            }

            // direction changes, but for some reason when it is passed back it doesn't change?

            else{
                if (ant->direction == UP){
                    ant->direction = RIGHT;
                }
            }
        }
    }
};

// this function works perfectly fine.
void move_forward(struct ant *ant){
    
    //printf("ant dir in move foward %d", ant->direction);
    int x_val = 0; 
    int y_val = 0;
    // takes in the direction that the ant is facing, needs to get the value of direction from the struct

    // as this will allow it to move one step
    
    // if it is moving left then decrement x by 1
    if(ant->direction == LEFT){
        ant->x = ant->x - 1;
    }

    // if it is moving right then increment x by 1
    if(ant->direction == RIGHT){
        ant->x = ant->x + 1;   
         
    }

    // if it is moving up then increment y by 1
    if (ant->direction == UP){
        ant->y = ant->y - 1;
    }

    // if it is moving down then decrement by 1
    if (ant->direction == DOWN){
        ant->y = ant->y + 1;
    }
    
    else{
        //printf("direction given was%d\n",ant->direction);
        //printf("A non-valid direction was given, so the program will now exit");
    }
};

void apply_rule(enum colour *colour, struct ant *ant){

// when colour = white, change direction to left, call turn_left function and then change colour to black?

// when colour = black, change direction to right, call turn_right function and then change colour to white?

// need to add the stars as this means that it will be able to used the value passed by the function?
    //printf("val of colour %d", *colour);
    
    // this isn't working due to the colout being sent, should be a 0 or 1, not 1342361600 for example.
    if(*colour == WHITE){
        //printf("white");
        //printf("ant dir before %d", ant->direction);
        turn_left(ant); 
        //printf("turned left");
        //printf("ant dir=%d", ant->direction);
        *colour = BLACK;
        //printf("colour%d", *colour);
    }

    else{
        turn_right(ant); 
        *colour = WHITE;
    }

};

  