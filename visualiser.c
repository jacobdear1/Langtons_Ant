#include <ncurses.h>
#include <locale.h>
#include <stdlib.h>
#include <stdbool.h>

#include "visualiser.h"
#include "langton.h"

// macro cell_at is defined here, also needs to be a ternary if else statement as due to the definition in mvprintw
// use the typedef enum colour cell; to help define the cell_at(y,x) -> *colour is the pointer to the values of the enum 
enum colour colour;

// takes the value of the enum colour and if it is black returns true, if not it returns false
#define cell_at(y, x) ( (colour  == BLACK) ? BLACK : WHITE)

#define cell_under_ant cell_at(ant->y, ant->x)
cell *cells;

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
   // add in here about how to implement the torus?

   // if this is wrong, try to implement it without this and see if it works first?
   // the other coordinate of either x or y will stay the same however
   // if the ant goes above the max x coordinate, then it goes to the leftmost row
   if (ant->x > max_x){
      ant->x = 0;
        // min_x?
    }

   if (ant->y > max_y){
      ant->y = 0;
    }

    // if the ant goes below 0 (the bottom), then it goes to the rightmost row
   if (ant->x < 0){
      ant->x = max_x;
        // min_x?
    }

   if (ant->y < 0){
      ant->y = max_y;
    }
}

void visualise_and_advance(struct ant* ant) {
      /* Draw cells and ant */
      for (int y=0; y<max_y; y++)
      {
         for (int x=0; x<max_x; x++)
         {
            // codes defines; if(ant_is_at(y, x)) {
                                 //direction_to_s(ant->direction);
                                 //} else {
                                 // if(cell_at(y,x)){
                                    // ""
                                 //};
                                 //}
            // tenary if else statement Simply, the logic would be (condition) ? {code for YES} : {code for NO}
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

      // need to fix this error; error: no member named 'ant' in 'struct ant'
      // need to remove the 
      // either do this or,

      // enum colour takes the value of cell_under_ant, and then uses this in the parameter when calling apply rule
      //*colour = cell_under_ant;
      //apply_rule(colour, ant);
      // from, https://stackoverflow.com/questions/46330784/expression-must-be-an-l-value-or-function-designator-error-when-taking-the-add

      // need to get rid of & as it gives the error; expression must be an lvalue or a function designator
      
      // this line is causing an issue, as we need cell_under_ant to be an enum for the definition of apply_rule, it is currently an integer
      
      // uses the enum colour temp as a temporary variable, which stores the return value of the macro cell_under_ant, as you can't access the address of an rvalue
      // but when you had &cell_under_ant this returned an rvalue, and then passes to the function the address of the temporary variable
      enum colour temp = cell_under_ant;
      apply_rule(&temp, ant);
      move_forward(ant);
}

// Check if the user has input "q" to quit
bool not_quit() {
   return 'q' != getch();
}

// implement the cell_at_fct for the torus?, tells you what cell the ant is at
//cell cell_at_fct(int y, int x){
   //printf("at cell%d%d\n", y, x);
  // return(y, x);
//};

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