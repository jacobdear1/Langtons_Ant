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
#define gen_cell_at(y, x) (gen_cells [ (y*max_x) + x]) // will have a different definition;

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
struct rule *rule;

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

      if (ant->x >= max_x){
         ant->x -= max_x;
      }
      if (ant->y >= max_y){
         ant->y -= max_y;
      }
      if (ant->x < 0){
         ant->x += max_x;
      }
      if (ant->y < 0){
         ant->y += max_y;
      }
      // if the ant goes below 0 (the bottom), then it goes to the rightmost row


}

// need to define 2 enums that hold the colours and one that holds the shading?

// function to start the visualisation of the new cells in the case of the general ant
void gen_start_visualisation(struct ant* ant, struct rule* rule) {
  setlocale(LC_ALL, "");

   initscr();
   curs_set(FALSE);
   max_x = getmaxx(stdscr);
   max_y = getmaxy(stdscr);
   // size of cell needs to be changed, as it means that currently it only has 2 values it can take; black and white
   // change this defintion, so the sizeof is equal to the number of representations that the ant can have 
   int length_rule = strlen(rule->rules);
   gen_cells = calloc(max_y*max_x, sizeof(length_rule)); // sets boundaries of the finite rectangular grid
   ant->x = max_x/2;
   ant->y = max_y/2;
   ant->direction = RIGHT;
}

// function to allow use to visualise the states
void gen_vis_advance(struct ant* ant, struct rule* rule){
      /* Draw cells and ant */
      for (int y=0; y<max_y; y++)
      {
         for (int x=0; x<max_x; x++)
         {
            mvprintw(y,x,
               ant_is_at(y,x)
                 ? direction_to_s(ant->direction)
                 // change this to display the colour based on the state that the ant is currently at using the rule length and the state representations?
                 : gen_cell_at(y,x) // value of this is changed by the apply_rule_general function, just need a way to represent this
                 // needs to represent the colour / value related to its position in the enum?
                    //attron(COLOR_PAIR())
                    // need to work out a way to visualise different things depending on their state.
                    ? "█"
                    : " "
            );
         }
      }
      refresh();
      //int y, x = 0;
      //printf("gen_cells at %d", gen_cell_at(ant->y,ant->x));
      //printf("val%d",gen_cell_under_ant);
      // this function isn't working properly
      // maybe we need to pass the individual value of the rule, so it only applies the function to one rule at a time
      apply_rule_general(&gen_cell_under_ant, ant, rule);
      move_forward(ant);
      //printf("has finished the function");
      
      // implementation of the torus 

      if (ant->x >= max_x){
         ant->x -= max_x;
      }
      if (ant->y >= max_y){
         ant->y -= max_y;
      }
      if (ant->x < 0){
         ant->x += max_x;
      }
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

// direction to set the ant off to 
const char* direction_to_s(enum direction d) {
   return UP   == d ? "^" :
          DOWN == d ? "v" :
          LEFT == d ? "<" :
          /* else */  ">" ;
}

// .h.gch happen when you precompile header files that do not need to be recomplied?