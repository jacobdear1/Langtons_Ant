#include <stdio.h>
#include <string.h>
#include "langton.h"
#include "visualiser.h"

// look into whether switch case statements are more memory efficient


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

    // switch case statement for changing the direction
    //ant->direction;
    switch (ant->direction)
    {
    // up
    case 0:
        ant->direction = LEFT;
        break;
    // down
    case 1:
        ant->direction = RIGHT;
        break;
    // left
    case 2:
        ant->direction = DOWN;
        break;
    // right 
    case 3:
        ant->direction = UP;
        break;    
    default:
        printf("invalid direction entered");
        break;
    }
};


void turn_right(struct ant *ant){
    // takes in value of direction and then changes it to
    // change direction to 'Right'
    //enum direction dir_right = RIGHT;

    //ant->direction = dir_right;

    // switch case statement for changing the direction
    //ant->direction;
    switch (ant->direction)
    {
    // up
    case 0:
        ant->direction = RIGHT;
        break;
    // down
    case 1:
        ant->direction = LEFT;
        break;
    // left
    case 2:
        ant->direction = UP;
        break;
    // right 
    case 3:
        ant->direction = DOWN;
        break;    
    default:
        printf("invalid direction entered");
    }
};

// this function works perfectly fine.
void move_forward(struct ant *ant){
    
    //printf("ant dir in move foward %d", ant->direction);
    int x_val = 0; 
    int y_val = 0;
    // takes in the direction that the ant is facing, needs to get the value of direction from the struct

    // as this will allow it to move one step
    
    switch (ant->direction)
    {
    // up
    case 0:
        ant->y = ant->y - 1;
        break;
    // down
    case 1:
        ant->y = ant->y + 1;
        break;
    // left
    case 2:
        ant->x = ant->x - 1;
        break;
    // right 
    case 3:
        ant->x = ant->x + 1;  
        break;    
    default:
        printf("invalid direction entered");
    }

};

void apply_rule(enum colour *colour, struct ant *ant){

// when colour = white, change direction to left, call turn_left function and then change colour to black?

// when colour = black, change direction to right, call turn_right function and then change colour to white?

// need to add the stars as this means that it will be able to used the value passed by the function?
    //printf("val of colour %d", *colour);
    
    // this isn't working due to the colout being sent, should be a 0 or 1, not 1342361600 for example.
    if(*colour == WHITE){
        turn_left(ant); 
        *colour = BLACK;
    }

    // case when the colour of cell is black
    else{
        turn_right(ant); 
        *colour = WHITE;
    }

};

// need to change the state, once it has visited the state i it changes to state i+1;

// don't want to access all rules, only the one for the specific state
void apply_rule_general(enum gen_cell *gen_cell, struct ant *ant, struct rule *rule){
    //printf("rule %c",*rule->rules);
    
    // puts the rule into an array and then find out the position of the colour and then apply the rule based off this? 
    // -> array is equal to the strlen (rule), so knows how many states it can give?
    // creates an array that has a length of all the rules in, and adds each one individually
    int array[strlen(rule->rules)];
    for (int j=0; j<strlen(rule->rules); j++){
        array[j] = rule->rules[j];
        //printf("array %d", array[j]);

    }
    // takes the current value (aka state) of the cell that the ant is at 
    int rule_val = *gen_cell;
    // loop takes in the value of rules and then the for loop lets you gain access to each of them
    // states are represnted by j, as intially it is zero, as the ant is also defined to start at 0
    //printf("rule {j}%c",rule->rules[rule_val]);
    // if the rule is L then the ant needs to turn left
    if (rule->rules[rule_val] == ('L')){
        turn_left(ant);
        // change the state of this square -> change this in visualiser function? as this is what will corrrepsond to the symbols
        *gen_cell = *gen_cell + 1;
        //printf("col%d", *gen_cell); 
        // if the colour is greater than the rule length; should go back to state 0
        // e.g. a length of rule 10; will have states 0 to 9, so if it has value 10 then it should go back to 0
        if (*gen_cell == strlen(rule->rules)){
            *gen_cell = 0;
        }
    }
    // in the case that the rule is R
    else{
        turn_right(ant);
        // *colour represents the state of the cell
        *gen_cell = *gen_cell + 1;
        // e.g. a length of rule 10; will have states 0 to 9, so if it has value 10 then it should go back to 0
        if (*gen_cell == strlen(rule->rules)){
            *gen_cell = 0;
        }            
    }

}