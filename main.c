#include <stdio.h>
#include <stdlib.h>

#include "langton.h"
#include "visualiser.h"

int main(){
    // creates an ant and starts the visualisation
    printf("here");
    struct ant* ant = {0, 0, RIGHT};
    start_visualisation(ant);

    // loops round until the user presses q, function not_quit() works out if q has been pressed or not
    while(not_quit() != false){
        visualise_and_advance(ant);

        // if the user presses q to quit then end the visualisation
        if (not_quit() == true){
                end_visualisation(ant);
        }
    }
}