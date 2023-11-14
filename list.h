#ifndef AGENDA_MANAGEMENT_PROJECT_LIST_H
#define AGENDA_MANAGEMENT_PROJECT_LIST_H

#include "cell.h"

typedef struct List {
    struct Cell** heads;  // Têtes de la liste pour chaque niveau
} List;


List* createEmptyList(int nbLevels);
void Cell_AddHead(List* list, Cell* cell, int maxLevels);
void displayLevel(List* list, int level, int maxLevels);
void displayAllLevels(List* list, int maxLevels);
void Cell_AddAt(List* list, Cell* cell, int level);
void classicSearch(List* list, int target);

#endif //AGENDA_MANAGEMENT_PROJECT_LIST_H