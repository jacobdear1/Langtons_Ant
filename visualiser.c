#include <ncurses.h>
#include <locale.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#include "visualiser.h"
#include "langton.h"

// macro cell_at is defined here, also needs to be a ternary if else statement as due to the definition in mvprintw
// use the typedef enum colour cell; to help define the cell_at(y,x) -> *colour is the pointer to the values of the enum ce colour; 

// takes the value of the enum colour and if it is black returns true (BLACK has val 1 which is the same as true), if not it returns false (WHITE has val 0 which is the same as false)
#define cell_at(y, x) (cells[ (y*max_x) + x])  // finds the value that the cells is at
#define gen_cell_at(y, x) (gen_cells[ (y*max_x) + x]) // will have a different definition;

// macro definition seems to be fine, as it returns the correct colour for cell under ant
// 

// macro to define the colour of the cell that the ant is currently on/at
// the address of cell_under_ant, needs to be a pointer into the array of cells, change this definition of this macro?

// have this macro return an integer so the pointer will be into the array if cells?
// address of this should be a cell; Because rvalues are ones which do “not represent an object occupying some identifiable location in memory”, we cannot use the & (addressof) operator on them.
// or an identifiable location in memory;
#define cell_under_ant cell_at(ant->y, ant->x)
#define gen_cell_under_ant gen_cell_at(ant->y, ant->x) // macro to define the general cell_at function, as it has a differet set of cells, as the origianl cells only have 2 states; need 26 at least

// enum holds the 8 colours that n curses supports
//enum gen_colours {COLOR_BLACK, COLOR_RED, COLOR_GREEN, COLOR_YELLOW, COLOR_BLUE, COLOR_MAGENTA, COLOR_CYAN, COLOR_WHITE};
//typedef enum gen_colours g_colours;

// cell has the value of 0 or 1 due to the defintion of its enum
cell *cells;
//enum gen_cell {A, B, C, D, E};

// defines the new enum that I will use to visualise the general ant
typedef enum gen_cell g_colours;
// change defintion to produce a set of cells that can be represented by 
// g_colours is how many different values the cell can take?
g_colours *gen_cells;

// defines the rule for use?
//struct rule *rule;

// use an enum to represent colours?

// shading of colours?

void start_visualisation(struct ant* ant) {
  setlocale(LC_ALL, "");

   initscr();
   curs_set(FALSE);
   max_x = getmaxx(stdscr);
   max_y = getmaxy(stdscr);
   cells = calloc(max_y*max_x, sizeof(cell)); // sets boundaries of the finite rectangular grid
   ant->x = max_x/2;
   ant->y = max_y/2;
   ant->direction = RIGHT;
}

void visualise_and_advance(struct ant* ant) {
      /* Draw cells and ant */
      for (int y=0; y<max_y; y++)
      {
         for (int x=0; x<max_x; x++)
         {
            mvprintw(y,x,
               ant_is_at(y,x)
                 ? direction_to_s(ant->direction)
                 : cell_at(y,x)
                    ? "█"
                    : " "
            );
         }
      }
      refresh();
      
      /* Advance to next step */
      apply_rule(&cell_under_ant, ant);
      move_forward(ant);
      
      // implementation of the torus 
      // if the ant goes above the top row, it will go down to the bottom row
      if (ant->x >= max_x){
         ant->x -= max_x;
      }
      // if the ant reaches the one column to the right of the rightmost column, it will reach the leftmost column
      if (ant->y >= max_y){
         ant->y -= max_y;
      }
      // if the ant goes below the bottom row, it will go back up to the top row
      if (ant->x < 0){
         ant->x += max_x;
      }
      // if the ant reaches the one column to the left of the leftmost column, it will reach the rightmost column
      if (ant->y < 0){
         ant->y += max_y;
      }
}


// function to start the visualisation of the new cells in the case of the general ant
void gen_start_visualisation(struct ant* ant, struct rule* rule) {
  setlocale(LC_ALL, "");

   initscr();
   curs_set(FALSE);
   max_x = getmaxx(stdscr);
   max_y = getmaxy(stdscr);

   // these 2 lines mean that; gen_cells is only allocated as many states as equal to the length of the rule,
   // as e.g. we don't want to have 26 different values the cell can take, when the rule has a length of 2 
   int length_rule = strlen(rule->rules);
   gen_cells = calloc(max_y*max_x, sizeof(length_rule)); // sets boundaries of the finite rectangular grid
   
   ant->x = max_x/2;
   ant->y = max_y/2;
   ant->direction = RIGHT;
}

// function to allow use to visualise the states
void gen_vis_advance(struct ant* ant, struct rule* rule){
      /* Draw cells and ant */

      // define the array here;
      // "█"

      // also the original value, so state 0 needs to equal value of whatever is at the end of the conditonal statement
      char *vis_array[10] = {" ", "B", "C", "D", "E", "F", "H", "I"};

      // fix the pointer conversion issue, turn the value produced by the vis_array into a char somehow

      // could do 
      //int vis_array[g_colours]? just so the size is correct

      // make sure that the value is greater than or equal to 1 to apply this otheriwse it won't work

      //printf("cell at%d", gen_cell_at(ant->y, ant->x));
      //char* v = vis_array[gen_cell_at(ant->y, ant->x)];
      //printf("val%s", v);

      for (int y=0; y<max_y; y++)
      {
         for (int x=0; x<max_x; x++)
         {
            char* v = vis_array[gen_cell_at(ant->y, ant->x)];
            mvprintw(y,x,
               ant_is_at(y,x)
                 ? direction_to_s(ant->direction)
                 // change this to display the colour based on the state that the ant is currently at using the rule length and the state representations?
                 // if the current cell has a value of 0, then we have it as the original state and visualise it as white
                 
                 // **this condtional means that it changes the value of every 'cell' that has been 'visited', rather than the last one we were at**
                 // this issue needs fixing. 
                 : gen_cell_at(y,x) // value of this is changed by the apply_rule_general function, just need a way to represent this
                 // needs to represent the colour / value related to its position in the enum?
                    //attron(COLOR_PAIR())
                    // need to work out a way to visualise different things depending on their state.

                    // have an array here that has 26 values in it, and then use the value of gen_cell_at(y, x), to reference the array
                    // and this referenece to the array then points to the value that will be outputted
                    // could also use the typedef gen_cells, and reference this and then visualise this value that has been specified in the enum / array?
                    

                    // do it so if the value = 0 then do white else call the array?
                    // maybe change the if statement
                    //? use array[gen_cell_at(ant->, ant)]
                    //? "█"

                    // somewhat works, but instead of changing the specific cell it was at, it changes the whole screen?
                    // it changes all of the visited values rather than the value that the cell is at?
                    ? v
                    : " "
            );
         }
      }
      refresh();
      // passes the value of the current gen_cell_under_ant, I have adapted cell_under_ant to work for my general ant, the ant and then the rule
      //printf("cell at val %d ", gen_cell_at(ant->y, ant->x));
      apply_rule_general(&gen_cell_under_ant, ant, rule);
      move_forward(ant);
      
      // implementation of the torus 
      // if the ant goes above the top row, it will go down to the bottom row
      if (ant->x >= max_x){
         ant->x -= max_x;
      }
      // if the ant reaches the one column to the right of the rightmost column, it will reach the leftmost column
      if (ant->y >= max_y){
         ant->y -= max_y;
      }
      // if the ant goes below the bottom row, it will go back up to the top row
      if (ant->x < 0){
         ant->x += max_x;
      }
      // if the ant reaches the one column to the left of the leftmost column, it will reach the rightmost column
      if (ant->y < 0){
         ant->y += max_y;
      }
}

// Check if the user has input "q" to quit
bool not_quit() {
   return 'q' != getch();
}

void end_visualisation() {
   free(cells); // uses free to free up the memory up once the visualisation has ended
   endwin();
}

// the general ant is defined differently so needs to free up the cells it uses instead
void gen_end_visualisation() {
   free(gen_cells);
   endwin();
}

// direction to set the ant off to 
const char* direction_to_s(enum direction d) {
   return UP   == d ? "^" :
          DOWN == d ? "v" :
          LEFT == d ? "<" :
          /* else */  ">" ;
}