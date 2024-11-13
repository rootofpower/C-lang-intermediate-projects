CC = gcc
CFLAGS = -std=c11 -Wall -Werror -Wconversion
LDLIBS = -lm -lcurses
OUTPUT = ps4

.PHONY:  all clean

all: $(OUTPUT)

$(OUTPUT): main.o bmp.o transformations.o
	@echo "Building project..."
	$ cppcheck --enable=performance,unusedFunction --error-exitcode=1 *.c
	$(CC) $(CFLAGS) $^ $(LDLIBS) -o $@

main.o: main.c
	@echo "Building main..."
	$(CC) $(CFLAGS) -c $^ $(LDLIBS) -o $@

k.o: bmp.c
	@echo "Building BMP module..."
	$(CC) $(CFLAGS) -c $^ $(LDLIBS) -o $@

hof.o: transformations.c
	@echo "Building Transformations module..."
	@$(CC) $(CFLAGS) -c $^ $(LDLIBS) -o $@

clean:
	rm -f *.o ps4

