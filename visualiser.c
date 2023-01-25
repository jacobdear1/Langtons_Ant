#include <ncurses.h>
#include <locale.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#include "visualiser.h"
#include "langton.h"

// looks in the cells array, using the x and y coordinates to find the 'state'
// that it is at, could be 1 or 0 depending on whether the cell is currently
// black (1) or white (0)
#define cell_at(y, x) (cells[ (y*max_x) + x])
// similar definition to the cell_at(y,x) macro, but using the gen_cells that
// allow us to visualise up to our 26 different states, it returns the 'state'
// which is the number associated to the cell which we are at in the array
// gen_cells
#define gen_cell_at(y, x) (gen_cells[ (y*max_x) + x])

#define cell_under_ant cell_at(ant->y, ant->x)
// macro to define the general cell_at function, as it has a different
// set of cells, as the original cells only have 2 states; need 26 at least
#define gen_cell_under_ant gen_cell_at(ant->y, ant->x)
cell *cells;
// defines the new enum, gen_colours that I will use to visualise
// the general ant
typedef enum gen_cell gen_colours;
// use gen_colours
gen_colours *gen_cells;

void start_visualisation(struct ant* ant) {
      setlocale(LC_ALL, "");

      initscr();
      curs_set(FALSE);
      max_x = getmaxx(stdscr);
      max_y = getmaxy(stdscr);
      // sets boundaries of the finite rectangular grid
      cells = calloc(max_y*max_x, sizeof(cell));
      ant->x = max_x/2;
      ant->y = max_y/2;
      ant->direction = RIGHT;
}

void visualise_and_advance(struct ant* ant) {
      /* Draw cells and ant */
      for (int y=0; y < max_y; y++) {
         for (int x=0; x < max_x; x++) {
            mvprintw(y, x ,
               ant_is_at(y, x)
                 ? direction_to_s(ant->direction)
                 : cell_at(y, x)
                    ? "█"
                    : " ");
         }
      }
      refresh();
      /* Advance to next step */
      apply_rule(&cell_under_ant, ant);
      move_forward(ant);
      // implementation of the torus
      // if the ant goes above the top row, it will go down to the bottom row
      if (ant->x >= max_x) {
         ant->x -= max_x;
      }
      // if the ant reaches the one column to the right of the rightmost column,
      // it will reach the leftmost column
      if (ant->y >= max_y) {
         ant->y -= max_y;
      }
      // if the ant goes below the bottom row, it will go back up to the top row
      if (ant->x < 0) {
         ant->x += max_x;
      }
      // if the ant reaches the one column to the left of the leftmost column,
      // it will reach the rightmost column
      if (ant->y < 0) {
         ant->y += max_y;
      }
}

// function to start the visualisation of the new cells in the //
// case of the general ant
void gen_start_visualisation(struct ant* ant, struct rule* rule) {
      setlocale(LC_ALL, "");

      initscr();
      curs_set(FALSE);
      max_x = getmaxx(stdscr);
      max_y = getmaxy(stdscr);
      // these 2 lines mean that; gen_cells is only allocated as many states as
      // equal to the length of the rules as e.g. we don't want to have 26
      // different values the cell can take, when the rule has a length of 2
      int length_rule = strlen(rule->rules);
      // sets boundaries of the finite rectangular grid, but with the
      // capacity to visualise 26 states
      gen_cells = calloc(max_y*max_x, sizeof(length_rule));
      ant->x = max_x/2;
      ant->y = max_y/2;
      ant->direction = RIGHT;
}

// array to visualise the different states
char *vis_array[28] = {" ", "B", "C", "D", "E", "F", "H", "I", "J", "K",
   "L", "M", "N", "O", "P", "Q", "R", "S", "T", "U", "V", "X", "Y", "Z",
   "!", "?"};
// function to allow use to visualise the states
void gen_vis_advance(struct ant* ant, struct rule* rule) {
      /* Draw general cells and general ant */
      for (int y=0; y < max_y; y++) {
         for (int x=0; x < max_x; x++) {
            mvprintw(y, x,
               ant_is_at(y, x)
                 ? direction_to_s(ant->direction)
                 : gen_cell_at(y, x)
                     // this changes the value of the cuurent cell at,
                     // looks up the value of the state in the vis_array
                     // that has all of the values that can be visualised
                     // and then prints the correct one depending on the state
                    ? vis_array[gen_cell_at(y, x)]
                    // original value, is equal to the state 0,
                    // also known as colour white or a blank cell
                    : " ");
         }
      }
      refresh();
      // passes the value of the current gen_cell_under_ant, I have adapted
      // cell_under_ant to work for my general ant, the ant and then the rule
      apply_rule_general(&gen_cell_under_ant, ant, rule);
      move_forward(ant);
      // implementation of the torus
      // if the ant goes above the top row, it will go down to the bottom row
      if (ant->x >= max_x) {
         ant->x -= max_x;
      }
      // if the ant reaches the one column to the right of the rightmost column,
      // it will reach the leftmost column
      if (ant->y >= max_y) {
         ant->y -= max_y;
      }
      // if the ant goes below the bottom row, it will go back up to the top row
      if (ant->x < 0) {
         ant->x += max_x;
      }
      // if the ant reaches the one column to the left of the leftmost column,
      // it will reach the rightmost column
      if (ant->y < 0) {
         ant->y += max_y;
      }
}

// Check if the user has input "q" to quit
bool not_quit() {
      return 'q' != getch();
}

void end_visualisation() {
      // uses free to free up the memory up once the visualisation has ended
      free(cells);
      endwin();
}

// the general ant is defined differently so needs to free up the cells
// it uses instead
void gen_end_visualisation() {
      free(gen_cells);
      endwin();
}

// direction to set the ant off to
const char* direction_to_s(enum direction d) {
      return UP   == d ? "^" :
         DOWN == d ? "v" :
         LEFT == d ? "<" :
         /* else */  ">";
}
