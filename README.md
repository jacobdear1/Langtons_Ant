# Programming Paradigms Summative

### Background
Langton's ant is a two-dimensional universal Turing machine that can demonstrate complexemergent behaviour based on a very simple set of rules. First created by Chris Langton in 1986,Langton's ant runs on a square lattice of black and white cells. 
Further details of this can be found in the corresponding paper(https://arxiv.org/pdf/math/9501233.pdf).

### The task

To implement Langton's ant, a basic version and then the more advanced; general ant which can have up to n states, with a rule inputted to define what to do at squares of specific states from 1 to n.

The ant will move around the screen by the user pressing any key except q, q will quit the program and stop the visualisation

### How to run the code 

To run the program use;

```make```

and then to run the executable 

```./ant```

### To compile a dynamically linked library ```libant.so```

```make library```

and then the executable

```./ant```
### Applying general rule for n state ants
If you want to apply the general rule, call the executable ```ant``` followed by a combination of L and R depending on what you want it to do in the states call, for example

```./ant LRLRR``` where the ant will turn left on states 0 and 2, and right on states 1, 3, 4

Note: This general rule works for rules of length up to 26.
### To clean all of the executable and dynamically linked library

```make clean```

Note: If you are using MacOS, change the ```-lncursesw``` in the Makefile, in these 2 functions; ```make all``` and ```make library``` 
to ```-lncurses``` as MacOS does not have support for ```-lncursesw```, unlike Windows.
