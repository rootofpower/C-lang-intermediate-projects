CC = gcc
CFLAGS = -std=c11 -Wall -Werror -Wconversion
LDLIBS = -lm -lcurses
OUTPUT = ps2

.PHONY: tests all clean

all: $(OUTPUT)

$(OUTPUT): main.o k.o hof.o ui.o
	@echo "Building project..."
	$ cppcheck --enable=performance,unusedFunction --error-exitcode=1 *.c
	$(CC) $(CFLAGS) $^ $(LDLIBS) -o $@

main.o: main.c
	@echo "Building main..."
	$(CC) $(CFLAGS) -c $^ $(LDLIBS) -o $@

k.o: k.c
	@echo "Building K module..."
	$(CC) $(CFLAGS) -c $^ $(LDLIBS) -o $@

hof.o: hof.c
	@echo "Building HOF module..."
	@$(CC) $(CFLAGS) -c $^ $(LDLIBS) -o $@

ui.o: ui.c 
	@echo "Building UI module..."
	@$(CC) $(CFLAGS) -c $^ $(LDLIBS) -o $@

clean:
	rm -f *.o ps2

