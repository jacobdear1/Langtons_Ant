#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h> // part of standard library, so okay to use

#include "visualiser.h"

int main(int argc, char** argv){
    //enum direction { UP, DOWN, LEFT, RIGHT };
    // Thread 1: EXC_BAD_ACCESS (code=2, address=0x100011f00), is caused by the allocation to this pointer.
    // need to work out how to intisalise the ant properly, through the correct pointer definitons, look at slides about structs?

    // allocate memory for x;, use malloc and dealloc to assign the memory needed?
   // new_ant->x = malloc(sizeof(int));
    
    // if nothing is added after the definition of ant, runs the basic variation, will be at least one due to having the executable
    if (argc == 1) {
        struct ant *new_ant = NULL;
        // memory to the pointer new_ant, has all of the properties of the struct ant
        new_ant = malloc(sizeof(struct ant));

        if (new_ant == NULL){
            printf("Error in malloc() for the struct ant");
            exit(1);
        }

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
        new_ant->direction = UP;
        printf("value %d\n", new_ant->x);
        printf("value y %d\n", new_ant->y);
        printf("value dir%d\n", new_ant->direction);
        
        // at this point an ant has been created and then we start the visualisation with this
        start_visualisation(new_ant);
        printf("value 2 %d\n", new_ant->x);
        printf("vis started");
        //visualise_and_advance(new_ant);

        // can tell that the visualisation has started as the terminal does something, but just doesn't print the ant onto the screen. -> error with a 
        // a pointer in the visualise and advance function
        // start_visualisation() works perfectly fine

        // loops round until the user presses q, function not_quit() works out if q has been pressed or not
        while(not_quit() != false){
            // new error inside of this function, bad memory allocation, need to look into it
            visualise_and_advance(new_ant);
            //qqqprintf("here 23");

            // if the user presses q to quit then end the visualisation
            // we know this works if the user presses q.
            if (not_quit() == false){
                    //free(new_ant);
                    printf("visualisation ended");
                    end_visualisation(new_ant);

            }

        }
        // free allocated memory
        free(new_ant); 
        
    }

    // catches error in the case that the input the incorrect format of more than 2 arguments
    if (argc > 2){
        printf("Incorrect number of arugments passed, max is the executable and a rule");
        exit(1);
    }

    else{
        // stores the value of the command line input into the variable rule
        char *rule;
        rule = argv[1];

        // checks the rule is of the correct format
        for (int i=0;i<strlen(rule);i++){
            printf(" %d", rule[i]);
            if (rule[i] != ('L') && rule[i] != 'R' && rule[i] != ('l') && rule[i] != 'r'){
                printf("Rule wasn't of correct format; which is a combination of L, R, l or r");
                exit(1);
            }
            // if the user inputs the rule in lower case it can handke this as well, it works by converting every instance of l or r to uppercase
            if (rule[i] == ('l') || rule[i] == ('r')){
                rule[i] = toupper(rule[i]);
                }
        }
        printf("new rule %s", rule);
        printf("rule valid");


    }
    // at this point an ant has been created and then we start the visualisation with this
    
    // free allocated memory
    //free(new_ant);
}
