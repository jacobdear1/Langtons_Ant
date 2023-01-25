#ifndef visualiser_h
#define visualiser_h

#include <stdbool.h>
#include "langton.h"

static int max_x;
static int max_y;

typedef enum colour cell;

void start_visualisation();
void visualise_and_advance();

// added functions for general ant
void gen_start_visualisation();
void gen_vis_advance();

bool not_quit();
// didn't need to implement for my torus
cell cell_at_fct(int y, int x);  // optional
void end_visualisation();

// added an end visualisation function for the general ant
void gen_end_visualisation();

const char* direction_to_s(enum direction d);

#endif
