#include <stdlib.h>
#include <stdbool.h>
#include "k.h"
#include <stdio.h>
#include <math.h>

void add_random_tile(struct game *game){
    int row, col;
    // find random, but empty tile
    do{
        row = rand() % SIZE;
        col = rand() % SIZE;
    }while(game->board[row][col] != ' ');

    // place to the random position 'A' or 'B' tile
    if(rand() % 2 == 0){
        game->board[row][col] = 'A';
    }else{
        game->board[row][col] = 'B';
    }
}


bool is_game_won(const struct game game){
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            if(game.board[i][j] == 'K') return 1;
        }
    }
    return 0;
}

bool is_move_possible(const struct game game){
    for(int i = 0; i < SIZE; i++){
        for(int j = 0; j < SIZE; j+=2){
            if(game.board[i][j] == game.board[i][j+1]) return 1;
            else if(game.board[j][i] == game.board[j+1][i]) return 1;
            else if(game.board[i][1] == game.board[i][2]) return 1;
            else if(game.board[1][i] == game.board[2][i]) return 1;
        }
    }

    return 0;
}




bool update(struct game *game, int dy, int dx) {
    if (dy > 1 || dy < -1 || dx > 1 || dx < -1) return false;
    if (dy == dx) return false;
    if (dy != 0 && dx != 0) return false;

    for (int i = 0; i < SIZE; i++) {
        for (int j = 1; j < SIZE; j++) {
            if (dy == -1) { // for up
                if (game->board[j][i] != ' ') {
                    int k = j;
                    for (; k > 0 && game->board[k - 1][i] == ' '; k--) {
                        game->board[k - 1][i] = game->board[k][i];
                        game->board[k][i] = ' ';
                    }
                    if (k > 0 && game->board[k - 1][i] == game->board[k][i]) {
                        game->board[k - 1][i]++;
                        game->score += (int)pow(2, (game->board[k-1][i] - 'A' + 1));
                        game->board[k][i] = ' ';
                    }
                }
            } 
        }   
    }
    
    for (int i = 0; i < SIZE; i++) {
        for (int j = 1; j < SIZE; j++) {
            if (dx == -1) { // for left
                if (game->board[i][j] != ' ') {
                    int k = j;
                    for (; k > 0 && game->board[i][k - 1] == ' '; k--) {
                        game->board[i][k - 1] = game->board[i][k];
                        game->board[i][k] = ' ';
                    }
                    if (k > 0 && game->board[i][k - 1] == game->board[i][k]) {
                        game->board[i][k - 1]++;
                        game->score += (int)pow(2, (game->board[i][k-1] - 'A' + 1));
                        game->board[i][k] = ' ';
                    }
                }
            } 
        }
    }

    
    for (int i = 0; i < SIZE; i++) {
        for (int j = SIZE - 2; j >= 0; j--) { 
            if (dy == 1) { // for DOWN
                if (game->board[j][i] != ' ') {
                    int k = j;
                    for (; k < SIZE - 1 && game->board[k + 1][i] == ' '; k++) {
                        game->board[k + 1][i] = game->board[k][i];
                        game->board[k][i] = ' ';
                    }
                    if (k < SIZE - 1 && game->board[k + 1][i] == game->board[k][i]) {
                        game->board[k + 1][i]++;
                        game->score += (int)pow(2, (game->board[k+1][i] - 'A' + 1));
                        game->board[k][i] = ' ';
                    }
                }
            }
        }
    }

    
    for (int i = 0; i < SIZE; i++) {
        for (int j = SIZE - 2; j >= 0; j--) { 
            if (dx == 1) { // for RIGHT
                if (game->board[i][j] != ' ') {
                    int k = j;
                    for (; k < SIZE - 1 && game->board[i][k + 1] == ' '; k++) {
                        game->board[i][k + 1] = game->board[i][k];
                        game->board[i][k] = ' ';
                    }
                    if (k < SIZE - 1 && game->board[i][k + 1] == game->board[i][k]) {
                        game->board[i][k + 1]++;
                        game->score += (int)pow(2, (game->board[i][k+1] - 'A' + 1));
                        game->board[i][k] = ' ';
                    }
                }
            }
        }
    }

    return true;
}

