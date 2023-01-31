
# to change the variation of the ant, you can add a rule in the place
# of the test rule I have written (LR), if you want the basic ant
# then don't add a rule
# makes a call to the command library, which uses
# this library to create the executable ./ant
# the -rpath=. allows you to find the dynamically linked library on 
# mira, doesn't work for MacOS, change the first line to this for Mac;
# gcc -Wall -Wextra -o ant main.c -L. -lant
all: library 
	gcc -Wall -Wextra main.o -Wl,-rpath=. -L. -lant -o ant
	./ant LR

# complies the dynamically linked library
library:
	gcc -fPIC  -c *.c
	gcc -shared -o libant.so *.o -lncursesw

# -f means that it will won't produce an error in the case that 
# one of the executables or the library doesn't exist
clean:
	rm -rf *.o ant libant.so