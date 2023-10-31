#include <stdlib.h>
#include <stdio.h>
#include "list.h"


List* createEmptyList(int maxLevels) {
    List* list = (List*)malloc(sizeof(List));
    list->heads = (struct Cell**)malloc(maxLevels * sizeof(struct Cell*));

    for (int i = 0; i < maxLevels; i++) {
        list->heads[i] = NULL;
    }
    return list;
}

void Cell_AddHead(List* list, Cell* cell, int maxLevels) {
    int nbLevels = cell->nbLevels;

    if (nbLevels > maxLevels) {    // reduit le nombre de cellule d'une valeur si ça depasse le nombre de niveaux total
        nbLevels = maxLevels;
    }

    for (int i = 0; i < nbLevels; i++) {
        cell->nexts[i] = list->heads[i];
        list->heads[i] = cell;
    }
}

void displayLevel(List* list, int level, int maxLevels) {
    if (level < 0 || level >= maxLevels) {
        printf("Niveau invalide\n");  // Affiche un message d'erreur si le niveau qu'on veut n'existe pas
        return;
    }

    printf("[list head_%d @-]-->", level);

    Cell* temp = list->heads[level];
    if ( temp== NULL){
        printf("NULL");
    }else {
        while (temp != NULL) {
            printf("[ %d|@-]-->", temp->value);
            temp = temp->nexts[level];
        }
        printf("NULL");
    }
    printf("\n");
}

void displayAllLevels(List* list, int maxLevels) {
    for (int i = 0; i < maxLevels; i++) {
        displayLevel(list, i, maxLevels);
    }
}