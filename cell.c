#include <stdlib.h>
#include "cell.h"

Cell *createCell(int value, int nbLevels) {
    Cell *newCell = (Cell *) malloc(sizeof(Cell));
    newCell->value = value;
    newCell->nbLevels = nbLevels;
    newCell->nexts = (struct Cell **) malloc(nbLevels * sizeof(struct Cell *));

    for (int i = 0; i < nbLevels; i++) {
        newCell->nexts[i] = NULL;
    }
    return newCell;
}