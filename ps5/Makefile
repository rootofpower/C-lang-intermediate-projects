CC = gcc
CFLAGS = -std=c11 -Wall -Werror -Wconversion
LDLIBS = -lm
OUTPUT = ps5

.PHONY:  all clean

all: $(OUTPUT)

$(OUTPUT): main.o backpack.o command.o container.o game.o item.o parser.o room.o world.o
	@echo "Building project..."
	$ cppcheck --enable=performance,unusedFunction --error-exitcode=1 *.c
	$(CC) $(CFLAGS) $^ $(LDLIBS) -o $@

main.o: main.c
	@echo "Building main..."
	$(CC) $(CFLAGS) -c $^ $(LDLIBS) -o $@

backpack.o: backpack.c
	@echo "Building Backpack module..."
	$(CC) $(CFLAGS) -c $^ $(LDLIBS) -o $@

command.o: command.c
	@echo "Building Command module..."
	@$(CC) $(CFLAGS) -c $^ $(LDLIBS) -o $@

container.o: container.c
	@echo "Building Container module..."
	@$(CC) $(CFLAGS) -c $^ $(LDLIBS) -o $@

game.o: game.c 
	@echo "Building Game module..."
	@$(CC) $(CFLAGS) -c $^ $(LDLIBS) -o $@

item.o: item.c 
	@echo "Building Item module..."
	@$(CC) $(CFLAGS) -c $^ $(LDLIBS) -o $@

parser.o: parser.c 
	@echo "Building Parser module..."
	@$(CC) $(CFLAGS) -c $^ $(LDLIBS) -o $@

room.o: room.c 
	@echo "Building Room module..."
	@$(CC) $(CFLAGS) -c $^ $(LDLIBS) -o $@

world.o: world.c 
	@echo "Building World module..."
	@$(CC) $(CFLAGS) -c $^ $(LDLIBS) -o $@

clean:
	rm -f *.o ps5

