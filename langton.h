#ifndef langton_h
#define langton_h

enum direction { UP, DOWN, LEFT, RIGHT };

struct ant{
    int x;
    int y;
    enum direction direction;
};

struct rule{
    char* rules;
};
// if the ant is at the specified position for both y and x
// returns true, else it returns false
#define ant_is_at(posy, posx) ((ant->y == posy) && (ant->x == posx))


enum colour { WHITE, BLACK };

// new data structure to help visualise the general function,
enum gen_cell { A, B, C, D, E, F, G, H, I, J, K, L, M, N,
    O, P, Q, R, S, T, U, V, W, X, Y, Z, Aa, Bb, Cc, Dd };

void turn_left(struct ant *ant);
void turn_right(struct ant *ant);
void move_forward(struct ant *ant);

void apply_rule(enum colour *colour, struct ant *ant);

// I have changed the name of the enum passed, as this will
// allow me to visualise rules of up to length 26
// function written on 2 lines as cpplint complained about line length
void apply_rule_general(enum gen_cell *gen_cell, struct ant *ant,
struct rule *rule);

#endif
