#ifndef visualiser_h
#define visualiser_h

#include "langton.h"
#include <stdbool.h>

static int max_x;
static int max_y;

typedef enum colour cell;

//enum gen_colours {COLOR_BLACK, COLOR_RED, COLOR_GREEN, COLOR_YELLOW, COLOR_BLUE, COLOR_MAGENTA, COLOR_CYAN, COLOR_WHITE};
//typedef enum gen_colours g_colours;

void start_visualisation();
void visualise_and_advance();

// added functions for general ant
void gen_start_visualisation();
void gen_vis_advance();

bool not_quit();
cell cell_at_fct(int y, int x); //optional
void end_visualisation();
const char* direction_to_s(enum direction d);

#endif
