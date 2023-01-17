#include <stdio.h>
#include <string.h>
#include "langton.h"
#include "visualiser.h"

void turn_left(struct ant *ant){
    // changes the ant's direction to turn 90 degrees clockwise, e.g. if the direction is left, then turning left would cause the ant to point down;
    // switch case statement for changing the direction
    switch (ant->direction)
    {
    // if current direction is up
    case 0:
        ant->direction = LEFT;
        break;
    // if current direction is down
    case 1:
        ant->direction = RIGHT;
        break;
    // if current direction is left
    case 2:
        ant->direction = DOWN;
        break;
    // if current direction is right 
    case 3:
        ant->direction = UP;
        break;   
    // in the case that the direction is assigned the wrong value 
    default:
        printf("invalid direction entered, cannot turn left");
        break;
    }
}


void turn_right(struct ant *ant){
    // takes in value of direction and then changes it to
    // switch case statement for changing the direction
    switch (ant->direction)
    {
    // if current direction is up
    case 0:
        ant->direction = RIGHT;
        break;
    // if current direction is down
    case 1:
        ant->direction = LEFT;
        break;
    // if current direction is left
    case 2:
        ant->direction = UP;
        break;
    // if current direction is right 
    case 3:
        ant->direction = DOWN;
        break; 
    // in the case that the direction is assigned the wrong value    
    default:
        printf("invalid direction entered, cannot turn right");
    }
}

void move_forward(struct ant *ant){
    // takes the value of the direction that the ant is currently facing and then moves the ant foward, so changes the relevant direction
    switch (ant->direction)
    {
    // if current direction is up
    case 0:
        ant->y = ant->y - 1;
        break;
    // if current direction is down
    case 1:
        ant->y = ant->y + 1;
        break;
    // if current direction is left
    case 2:
        ant->x = ant->x - 1;
        break;
    // if current direction is left 
    case 3:
        ant->x = ant->x + 1;  
        break; 
    // in the case that the direction is assigned the wrong value    
    default:
        printf("invalid direction entered, cannot move foward");
    }
}

void apply_rule(enum colour *colour, struct ant *ant){
    // when colour = white, change direction to left, call turn_left function and then change colour to black, opposite for when the colour is black
    if(*colour == WHITE){
        turn_left(ant); 
        *colour = BLACK;
    }

    // case when the colour of cell is black
    else{
        turn_right(ant); 
        *colour = WHITE;
    }
}

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
        // if the colour is greater than the rule length; should go back to state 0
        // e.g. a length of rule 6; will have states 0 to 5, so if it has value 6 then it should go back to 0, which it does
        if (*gen_cell == strlen(rule->rules)){
            //printf("max gen_cell %d", *gen_cell);
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