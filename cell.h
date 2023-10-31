#ifndef AGENDA_MANAGEMENT_PROJECT_CELL_H
#define AGENDA_MANAGEMENT_PROJECT_CELL_H

#include "stdlib.h"
#include "stdio.h"


typedef struct Cell {
    int value;
    struct Cell** nexts;  // Tableau de pointeurs vers les niveaux
    int nbLevels;  // Nombre de niveaux
} Cell;

Cell* createCell(int value, int nbLevels);

#endif //AGENDA_MANAGEMENT_PROJECT_CELL_H
