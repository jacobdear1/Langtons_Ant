#include <stdio.h>
#include <string.h>
#include "langton.h"
#include "visualiser.h"

void turn_left(struct ant *ant) {
    // changes the ant's direction to turn 90 degrees clockwise, e.g. if the
    // direction is left, then turning left would cause the ant to point down;
    // switch case statement for changing the direction
    switch (ant->direction) {
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

void turn_right(struct ant *ant) {
    // takes in value of direction and then changes it to
    // switch case statement for changing the direction
    switch (ant->direction) {
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

void move_forward(struct ant *ant) {
    // takes the value of the direction that the ant is currently facing and
    // then moves the ant foward, so changes the relevant direction
    switch (ant->direction) {
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

void apply_rule(enum colour *colour, struct ant *ant) {
    // when colour = white, change direction to left, call turn_left function
    // and then change colour to black, opposite for when the colour is black
    if (*colour == WHITE) {
        turn_left(ant);
        *colour = BLACK;
    } else {
        // case when the colour of cell is black
        turn_right(ant);
        *colour = WHITE;
    }
}

// change the function definition to
// function written on 2 lines as cpplint complained about line length
void apply_rule_general(enum gen_cell *gen_cell, struct ant *ant,
struct rule *rule) {
    // an array of the rule split into individual rules
    // position in array relates to the state (represented by j)
    // that the rule applies to, the size of this depends on length
    // of the inputted rule
    int g_array[strlen(rule->rules)];
    for (int j=0; j < strlen(rule->rules); j++) {
        g_array[j] = rule->rules[j];
    }
    // takes the current value (aka state) of the cell that the ant is at
    int rule_val = *gen_cell;
    // if the rule is L then the ant needs to turn left
    if (rule->rules[rule_val] == ('L')) {
        turn_left(ant);
        *gen_cell = *gen_cell + 1;
        // if the colour is greater than the rule length; goes back to state 0
        if (*gen_cell == strlen(rule->rules)) {
            *gen_cell = 0;
        }
    } else {
        // in the case that the rule is R
        turn_right(ant);
        // *gen_cell represents the state of the cell
        *gen_cell = *gen_cell + 1;
        if (*gen_cell == strlen(rule->rules)) {
            *gen_cell = 0;
        }
    }
}
