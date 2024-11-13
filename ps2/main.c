#include <stdio.h>
#include "k.h"
#include "hof.h"
#include "ui.h"

int main(int argc, char *argv[]) {
    struct game game = {
        .board = {
            {'A', 'A', 'C', 'D'},
            {'A', ' ', 'G', 'H'},
            {'I', ' ', 'J', 'A'},
            {' ', ' ', ' ', 'E'}
        },
        .score = 0
    };

    struct game game1 = {
        .board = {
            {'F', 'E', 'B', 'I'},
            {'B', 'H', 'J', 'G'},
            {'G', 'H', 'D', 'F'},
            {'B', 'F', 'E', 'C'}
        },
        .score = 0
    };

    struct game game2 = {
        .board = {
            {'A', ' ', ' ', ' '},
            {'B', ' ', ' ', 'B'},
            {'C', 'C', 'C', ' '},
            {'D', 'D', 'D', 'D'}
        },
        .score = 0
    };

    bool result = update(&game2, 0, 1);
    render(game2);
    printf("first func\n");
    printf("is won: %d\n", is_game_won(game1));
    render(game1);
    printf("is won: %d\n", is_game_won(game));
    printf("game 1 is move possible: %d\n", is_move_possible(game1));
    printf("game is move possible: %d\n", is_move_possible(game));
    printf("game2 is move possible: %d\n", is_move_possible(game2));
    
    struct game game3 = {
        .board = {
            {' ', ' ', ' ', ' '},
            {' ', ' ', ' ', ' '},
            {' ', ' ', ' ', ' '},
            {' ', ' ', ' ', ' '}
        },
        .score = 0
    };
    struct game game4 = {
.score=4237,
.board={
	{' ', ' ', ' ', ' '},
	{' ', ' ', 'J', 'F'},
	{' ', ' ', ' ', ' '},
	{' ', ' ', ' ', ' '}
}};
    add_random_tile(&game3);
    printf("result game 3 %d\n", result);
    result = update(&game4, 0, 1);
    printf("(false statement)result game 3 %d\n", result);
    render(game4);
    struct player hof[10];
    int size = load(hof);
    bool saved = save(hof, size);
    
    if(saved) {
        printf("saved\n");
    }
    else {
        printf("not saved\n");
    }

    struct player list[10];
    size = load(list);
    saved = save(list, size);
    struct player player = {
        .name = "abalay",
        .score = 666
    };

    result = add_player(list, &size, player);
    
    return 0;
}

