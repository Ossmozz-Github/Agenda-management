#ifndef AGENDA_MANAGEMENT_PROJECT_LIST_H
#define AGENDA_MANAGEMENT_PROJECT_LIST_H

#include "cell.h"

typedef struct List {
    struct Cell **heads;  // Têtes de la liste pour chaque niveau
} List;


List *createEmptyList(int nbLevels);

void Cell_AddHead(List *list, Cell *cell, int maxLevels);

void displayLevel(List *list, int level, int maxLevels);

void displayAllLevels(List *list, int maxLevels);

void Cell_AddAt(List *list, Cell *cell, int level);

int nbDivideBy2(int n);

void Leveled_List(List *list, int n);

void classicSearch(List *list, int val);

void SearchAll(List *list, int val, int maxLevels);

void complexity(int level_min, int level_max);

void displayCell(Cell *cell, int level);

void displaySortedLevel(List *list, int level);

void displaySortedAll(List *list, int maxLevels);

#endif //AGENDA_MANAGEMENT_PROJECT_LIST_H