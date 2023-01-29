#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>  // part of standard library, so okay to use

#include "visualiser.h"

int main(int argc, char** argv) {
    // if nothing is added after the definition of ant, runs the basic
    // variation, will be at least one due to having the executable
    if (argc == 1) {
        // allocate pointer to the struct to be NULL when defining as, 
        // it means that if the memory isnn't allocated properly, the 
        // program will stop due to if condition at line 21
        struct ant *new_ant = NULL;
        // memory to the pointer new_ant, has all of the properties of
        // the struct ant
        new_ant = malloc(sizeof(*new_ant));

        // check that the memory has been allocated properly
        if (new_ant == NULL) {
            printf("Error in malloc() for the struct ant");
            exit(1);
        }
        // at this point an ant has been created and then we start
        // the visualisation with this
        start_visualisation(new_ant);

        // if the user presses q to quit then ends the visualisation
        if (not_quit() == false) {
                end_visualisation(new_ant);
        }
        // loops round until the user presses q, function not_quit()
        // works out if q has been pressed or not
        while (not_quit() != false) {
            // if the user presses q to quit then ends the visualisation
            if (not_quit() == false) {
                    end_visualisation(new_ant);
            }
            visualise_and_advance(new_ant);
        }
        // free allocated memory
        free(new_ant);
    }

    // catches error in the case that the input the incorrect format
    // of more than 2 arguments
    if (argc > 2) {
        printf("Invalid number of arguments passed, max is the exectuable");
        printf(" ./ant and a rule which is a combination of L and R");
        exit(1);
    }

    if (argc == 2) {
        // stores the value of the command line input into the
        // variable rule
        char *rule = argv[1];
        // only have to visualise rules of up to 26 characters, so checks
        // that is is not more than this
        if (strlen(rule) > 26) {
            printf("The maximum length of rules than can be visualised is 26");
            exit(1);
        }

        // checks the rule is of the correct format
        for (unsigned int i=0; i < strlen(rule); i++) {
            // check that the rule is of the correct format
            if (rule[i] != ('L') && rule[i] != 'R' &&
            rule[i] != ('l') && rule[i] != 'r') {
                printf("Rule wasn't of correct format");
                printf("; which is a combination of L, R, l or r");
                exit(1);
            }
            // if the user inputs the rule in lower case it can handle this as
            // well, it works by converting every instance of l or r
            // to uppercase
            if (rule[i] == ('l') || rule[i] == ('r')) {
                rule[i] = toupper(rule[i]);
                }
        }

        struct rule *new_rule = NULL;
        // allocate memory for the rule the user has inputted
        // use the pointer to the struct to alllocate memory correctly
        new_rule = malloc(sizeof(*new_rule));

        // in the case that memory can't be allocated properly
        if (new_rule == NULL) {
            printf("Error in malloc() for the struct rule");
            exit(1);
        }
        // sets the value of the struct to the user inputted rule
        new_rule->rules = rule;

        struct ant *gen_ant = NULL;
        // allocates memory for the general ant
        gen_ant = malloc(sizeof(*gen_ant));
        // to make sure that the memory has been correctly allocated
        if (gen_ant == NULL) {
            printf("Error in malloc() for the struct ant");
            exit(1);
        }
        // pass in the rule so that we can use the length of rule to
        // determine how many different cell types we can have
       gen_start_visualisation(gen_ant, new_rule);
        // loops round until the user presses q, function not_quit()
        // works out if q has been pressed or not
        if (not_quit() == false) {
            gen_end_visualisation(gen_ant);
        }
        while (not_quit() != false) {
            // if the user presses q to quit then ends the visualisation
            if (not_quit() == false) {
                    gen_end_visualisation(gen_ant);
            }
            gen_vis_advance(gen_ant, new_rule);
        }
        // free allocated memory for the rule
        free(new_rule);
        // free allocated memory for the ant
        free(gen_ant);
    }
}
