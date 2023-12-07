#include <stdio.h>
#include <stdlib.h>
#include "list.h"

int main() {
    int maxLevels = 5;

    List *list = createEmptyList(maxLevels);

    Cell *cell1 = createCell(1, 5);
    Cell *cell2 = createCell(2, 5);
    Cell *cell3 = createCell(3, 5);
    Cell *cell4 = createCell(4, 5);
    Cell *cell5 = createCell(5, 5);
    Cell *cell6 = createCell(6, 5);
    Cell *cell7 = createCell(7, 5);

    displayAllLevels(list, maxLevels);
    printf("\n");

    Cell_AddAt(list, cell1, 0);
    Cell_AddAt(list, cell2, 0);
    Cell_AddAt(list, cell3, 0);
    Cell_AddAt(list, cell4, 0);
    Cell_AddAt(list, cell5, 0);
    Cell_AddAt(list, cell6, 0);
    Cell_AddAt(list, cell7, 0);

    displayAllLevels(list, maxLevels);

    Leveled_List(list, 3);

    printf("\n");

    displayAllLevels(list, maxLevels);

    printf("\n");

    displaySortedAll(list, maxLevels);

    return 0;
}