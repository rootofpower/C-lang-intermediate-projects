#include <stdio.h>
#include "container.h"
#include <stdlib.h>
#include <string.h>

struct container* create_container(struct container* first, enum container_type type, void* entry){
    if(!entry) return NULL;
    if(first){
        if(first->type != type) return NULL;
    }

    struct container* new_container = (struct container*) calloc(1, sizeof(struct container));
    new_container->type = type;
    switch (type) {
        case ROOM:
        new_container->room = (struct room*)entry;
        break;
        
        case ITEM:
        new_container->item = (struct item*)entry;
        break;

        case COMMAND:
        new_container->command = (struct command*)entry;
        break;

        case TEXT:
        new_container->text = (char*)entry;
    }   
    if(!first)
        return new_container;
    else{
        while(first->next){
            first = first->next;
        }
        first->next = new_container;
        return new_container; 
    }
}


struct container* destroy_containers(struct container* first){
    if(!first) return NULL;
    struct container* temp = first;
    struct container* next;
    while(temp){
        next = temp->next;
        free(temp);
        temp = next;
    }
    first = NULL;
    return first;
}


// void* get_from_container_by_name(struct container *first, const char *name){}
//
//
// struct container* remove_container(struct container *first, void *entry){}
//
