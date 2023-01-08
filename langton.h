#ifndef langton_h
#define langton_h

enum direction { UP, DOWN, LEFT, RIGHT };

// these have been defined publically so any .c file that has this header file included can use this
struct ant
{
    int x;
    int y;
    enum direction direction;
};

struct rule
{
    char* rules;
};

// an if statement which checks whether the ant is at a given set of coordinates
// use the x and y values from the ant struct and then use the values from posy and posx, compare these and if 
// have the condition inside the if def statement and if its true then we need to

// use the tenary if else statement within the defintion of ant_is_at;  Simply, the logic would be (condition) ? {code for YES} : {code for NO}
// need to define this macro and then it should work?, the whole code

// if the ant is at the specified position for both y and x returns true, else it returns fals
// this works correctly
#define ant_is_at(posy, posx) ( (ant->y == posy) && (ant->x == posx) ? true : false)


enum colour { WHITE, BLACK };

void turn_left(struct ant *ant);
void turn_right(struct ant *ant);
void move_forward(struct ant *ant);

void apply_rule(enum colour *colour, struct ant *ant);
void apply_rule_general(enum colour *colour, struct ant *ant, struct rule *rule);

#endif
