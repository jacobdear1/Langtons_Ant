DEPS = langton.h visualiser.h

all: visualiser.o langton.o main.c
	gcc -o ant main.c visualiser.o langton.o -lncurses

	# need to add ncursesw before submission?

visualiser.o: visualiser.c visualiser.h
	gcc -c visualiser.c

langton.o: langton.c langton.h
	gcc -c langton.c

%.o: %.c (DEPS)
	
library:
	gcc -fPIC  -c langton.c visualiser.c -o libant.so
	gcc -Wall -Wextra -o main main.c -L. -lant
clean:
	rm *.o ant