#include <stdio.h>
#include <stdlib.h>º
#include "list.h"

int main() {
    int maxLevels = 5;

    List* list = createEmptyList(maxLevels);
    List* mylist = createEmptyList(maxLevels);

    Cell* cell1 = createCell(4, 3);
    Cell* cell2 = createCell(9, 4);
    Cell* cell3 = createCell(5, 2);
    Cell* cell4 = createCell(6, 2);

    Cell_AddHead(list, cell1, maxLevels);
    Cell_AddHead(list, cell2, maxLevels);
    Cell_AddHead(list, cell3, maxLevels);

    displayAllLevels(list, maxLevels);
    printf("\n");
    displayAllLevels(mylist, maxLevels);
    printf("\n");

    for (int i=0; i<maxLevels; i++){
        Cell_AddAt(list, cell4, i);
    }
    displayAllLevels(list, maxLevels);
    printf("\n");

    classicSearch(list, 4);
    classicSearch(list, 6);
    classicSearch(list, 0);

    printf("\n");

    return 0;
}