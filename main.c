#include <stdio.h>
#include <stdlib.h>
#include "list.h"

int main() {
    int maxLevels = 5;

    List* list = createEmptyList(maxLevels);
    List* mylist = createEmptyList(maxLevels);

    Cell* cell1 = createCell(4, 3);
    Cell* cell2 = createCell(9, 4);
    Cell* cell3 = createCell(5, 2);

    Cell_AddHead(list, cell1, maxLevels);
    Cell_AddHead(list, cell2, maxLevels);
    Cell_AddHead(list, cell3, maxLevels);

    displayAllLevels(list, maxLevels);
    printf("\n");
    displayAllLevels(mylist, maxLevels);

    return 0;
}