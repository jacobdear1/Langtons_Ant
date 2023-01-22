DEPS = langton.h visualiser.h

all: visualiser.o langton.o main.c
	gcc -o ant main.c visualiser.o langton.o -lncurses

	# need to add ncursesw before submission?

visualiser.o: visualiser.c visualiser.h
	gcc -c visualiser.c

langton.o: langton.c langton.h
	gcc -c langton.c

%.o: %.c $(DEPS)
	gcc -c $< -0


library:
	gcc -fPIC  -c *.c
	gcc -shared -o libant.so *.o -lncurses
	# add ncursesw before submission
	gcc -Wall -Wextra -o ant main.c -L. -lant 

# -f means that it will won't produce an error in the case that one of the executables or the library doesn't exist
clean:
	rm -rf *.o ant libant.so