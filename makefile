SRC = $(wildcard *.c)
OBJ = $(SRC:.c=.o)

all: exec

functions.o: functions.c functions.h
	gcc -c $< -o $@
rules.o: rules.c rules.h functions.h
	gcc -c $< -o $@
draw.o: draw.c draw.h functions.h
	gcc -c $< -o $@
main.o: main.c draw.h rules.h functions.h
	gcc -c $< -o $@

exec: $(OBJ)
	gcc $^ -o $@
clean:
	rm -f *.o
	rm -f exec
fsanitize: $(OBJ)
	gcc $^ -fsanitize=address -o exec
doxy: Doxyfile
	doxygen $<