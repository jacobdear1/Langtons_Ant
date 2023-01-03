#include <stdio.h>
#include <stdlib.h>

#include "langton.h"
#include "visualiser.h"

int main(){
    // creates an ant and starts the visualisation
    printf("here");
    struct ant *new_ant = NULL;
    // memory to the pointer new_ant, has all of the properties of the struct ant
    new_ant = malloc(sizeof(struct ant));

    int first = 0;
    int second = 0;
    //enum direction { UP, DOWN, LEFT, RIGHT };
    printf("i work");
    // Thread 1: EXC_BAD_ACCESS (code=2, address=0x100011f00), is caused by the allocation to this pointer.
    // need to work out how to intisalise the ant properly, through the correct pointer definitons, look at slides about structs?

    // allocate memory for x;, use malloc and dealloc to assign the memory needed?
   // new_ant->x = malloc(sizeof(int));

    new_ant->x = first;
    printf("have reached x\n");
    new_ant->y = second;
    printf("have reached y\n");
    new_ant->direction = RIGHT;
    printf("value %d\n", new_ant->x);
    printf("value y %d\n", new_ant->y);
    printf("value dir%d\n", new_ant->direction);
    
    // at this point an ant has been created and then we start the visualisation with this
    start_visualisation(new_ant);
    printf("value 2 %d\n", new_ant->x);
    printf("vis started");

    // can tell that the visualisation has started as the terminal does something, but just doesn't print the ant onto the screen. -> error with a 
    // a pointer in the visualise and advance function
    // start_visualisation() works perfectly fine

    // loops round until the user presses q, function not_quit() works out if q has been pressed or not
    while(not_quit() != false){
        // new error inside of this function, bad memory allocation, need to look into it
        visualise_and_advance(new_ant);

        // if the user presses q to quit then end the visualisation
        // we know this works if the user presses q.
        if (not_quit() == true){
                printf("visualisation ended");
                end_visualisation(new_ant);

        }

    }
    // free allocated memory;
    free(new_ant);

}
