# Programming Paradigms Summative

## Background

Langton's ant is a two-dimensional universal Turing machine that can demonstrate complexemergent behaviour based on a very simple set of rules. First created by Chris Langton in 1986, Langton's ant runs on a square lattice of black and white cells.
Further details of this can be found in the corresponding paper (https://arxiv.org/pdf/math/9501233.pdf).

## The task

To implement Langton's ant, a basic version and then the more advanced; general ant which can have up to n states, with a rule inputted to define what to do at squares of specific states from 1 to n.

The ant will move around the screen by the user pressing any key except q, q will quit the program and stop the visualisation.

## How to run the code

To run the program use;

```make```

This will launch the executable ```ant```, you can change the inputted rule in the makefile, it is currently ```LR```.

## To compile a dynamically linked library ```libant.so```

```make library```

## Applying general rule for n state ants

If you want to apply the general rule, call the executable ```ant``` followed by a combination of L and R depending on what you want it to do in the states call, for example;

```./ant LRLRR``` where the ant will turn left on states 0 and 2, and right on states 1, 3, 4

Note: This general rule works for rules of length up to 26.

## To clean all of the executable and dynamically linked library

```make clean```

## Notes

* If you are using MacOS, change the ```-lncursesw``` in the Makefile for the command ```make library```to ```-lncurses``` as MacOS does not have support for ```-lncursesw```, unlike Windows.

* You can run the ```./ant``` executable by either doing ```make``` or ```make all``` and this will run the ant automatically.

* To use and the ```libant.so``` to create the executable on MacOS you need to use ```gcc -Wall -Wextra -o ant main.c -L. -lant``` instead of ``` gcc -Wall -Wextra main.o -Wl,-rpath=. -L. -lant -o ant ``` in the ```make all``` command.
