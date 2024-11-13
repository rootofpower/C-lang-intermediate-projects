#include <stdio.h>
#include "container.h"
#include "game.h"
#include "backpack.h"
#include "command.h"
#include "item.h"
#include "parser.h"
#include "room.h"
#include "world.h"

int main(int argc, char *argv[])
{
    struct container* first_cont = create_container(NULL, 1, NULL);
    if(first_cont == NULL) printf("1\n");
    first_cont = destroy_containers(NULL);
    if(first_cont == NULL) printf("2\n");
    return 0;
}
