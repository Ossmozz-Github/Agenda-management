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

void Cell_AddAt(List* list, Cell* cell, int level){
    Cell* temp=list->heads[level];
    Cell* prev=NULL;    // Car prev est la cellule avant temp
    while(temp!=NULL && temp->value <= cell->value){
        prev=temp;
        temp=temp->nexts[level];
    }
    if(prev==NULL){    // Si la nouvelle cellule est plus petite que la tete
        cell->nexts[level] = list->heads[level];
        list->heads[level] = cell;
    }else {
        prev->nexts[level] = cell;
        cell->nexts[level] = temp;
    }
}

void classicSearch(List* list, int val) {  // Recherche au niveau 0
    displayLevel(list, 0, list->heads[0]->nbLevels);
    Cell* temp = list->heads[0];
    while (temp != NULL && temp->value != val) {
        temp = temp->nexts[0];
    }
    if (temp != NULL && temp->value == val) {
        printf("%d found at level 0\n", val);
    } else {
        printf("%d not found at level 0\n", val);
    }
}

