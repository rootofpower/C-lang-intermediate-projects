#include <stdbool.h>
#include "hof.h"
#include <stdio.h>
#include <string.h>


void sort_players(struct player list[], int size) {
    for (int i = 0; i < size - 1; i++) {
        for (int j = 0; j < size - i - 1; j++) {
            if (list[j].score < list[j + 1].score) {
                struct player temp = list[j];
                list[j] = list[j + 1];
                list[j + 1] = temp;
            }
        }
    }
}

bool save(const struct player list[], const int size) {
    struct player temp[10];
    memcpy(temp, list, (unsigned long)size * sizeof(struct player));
    sort_players(temp, size);

    FILE *file = fopen(HOF_FILE, "w");
    if (file == NULL) {
        return false;
    }

    for (int i = 0; i < size; i++) {
        fprintf(file, "%s %d\n", temp[i].name, temp[i].score);
    }

    fclose(file);
    return true;
}

int load(struct player list[]) {
    FILE *file = fopen(HOF_FILE, "r");
    if (file == NULL) {
        return -1;
    }
    
    int count = 0;
    while (count < 10 && fscanf(file, "%s %d", list[count].name, &list[count].score) == 2) {
        count++;
    }

    fclose(file);
    sort_players(list, count);
    return count;
}

bool add_player(struct player list[], int *size, const struct player new_player) {
    if (*size == 0) {
        list[0] = new_player;
        (*size)++;
        return true;
    }

    if (new_player.score < list[*size - 1].score && *size >= 10) {
        return false;
    }

    int insert_index = *size;
    if (insert_index > 0) {
        while (new_player.score >= list[insert_index - 1].score) {
            insert_index--;
            if (insert_index == 0) {
                break;
            }
        }
    }

    if (*size < 10) {
        (*size)++;
    }

    int i = *size - 1;
    for (; i > insert_index; i--) {
        list[i] = list[i - 1];
    }

    list[insert_index] = new_player;

    if (*size > 10) {
        *size = 10;
    }

    sort_players(list, *size);
    return true;
}
