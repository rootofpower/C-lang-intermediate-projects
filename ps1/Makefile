CC = gcc
CFLAGS = -std=c11 -Wall -Werror
LDLIBS = -lm
OUTPUT = ps1

.PHONY: tests all clean

all: $(OUTPUT)

$(OUTPUT): main.o bmp.o playfair.o
	@echo "Building project..."
	$ cppcheck --enable=performance,unusedFunction --error-exitcode=1 *.c
	$(CC) $(CFLAGS) $^ $(LDLIBS) -o $@

main.o: main.c
	@echo "Building main..."
	$(CC) $(CFLAGS) -c $^ $(LDLIBS) -o $@

bmp.o: bmp.c
	@echo "Building BMP module..."
	$(CC) $(CFLAGS) -c $^ $(LDLIBS) -o $@

playfair.o: playfair.c
	@echo "Building Playfair module..."
	@$(CC) $(CFLAGS) -c $^ $(LDLIBS) -o $@

tests: bmp.c tests/test_reverse.c
	@echo "Running tests..."
	@$(CC) $(CFLAGS) $^ $(LDLIBS) -o test_reverse
clean:
	rm -f *.o ps1

