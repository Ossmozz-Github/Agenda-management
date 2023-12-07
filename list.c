#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "list.h"
#include "timer.h"

List *createEmptyList(int maxLevels) {
    List *list = (List *) malloc(sizeof(List));
    list->heads = (struct Cell **) malloc(maxLevels * sizeof(struct Cell *));

    for (int i = 0; i < maxLevels; i++) {
        list->heads[i] = NULL;
    }
    return list;
}

void Cell_AddHead(List *list, Cell *cell, int maxLevels) {
    int nbLevels = cell->nbLevels;

    if (nbLevels > maxLevels) {    // reduit le nombre de cellule d'une valeur si ça depasse le nombre de niveaux total
        nbLevels = maxLevels;
    }

    for (int i = 0; i < nbLevels; i++) {
        cell->nexts[i] = list->heads[i];
        list->heads[i] = cell;
    }
}

void displayCell(Cell *cell, int level) {
    if (level <= cell->nbLevels) {     // seulement si le niveau actuel est inferieur au niveau max de la cellule
        printf("-->[%2d|@-]", cell->value);   //Affiche la cellule
    } else {
        printf("----------");
    }
}

void displaySortedLevel(List *list, int level) {
    printf("[list head_%d @-]--", level);

    Cell *temp = list->heads[0];
    while (temp != NULL) {              // tant que different de NULL appelle displayCell
        displayCell(temp, level);
        temp = temp->nexts[0];
    }
    printf(">NULL\n");
}

void displaySortedAll(List *list, int maxLevels) {
    for (int i = 0; i < maxLevels; ++i) {
        displaySortedLevel(list, i);
    }
    printf("\n");
}

void displayLevel(List *list, int level, int maxLevels) {
    if (level < 0 || level > maxLevels) {
        printf("Niveau invalide\n");  // Affiche un message d'erreur si le niveau qu'on veut n'existe pas
        return;
    }
    printf("[list head_%d @-]-->", level);

    Cell *temp = list->heads[level];
    if (temp == NULL) {
        printf("NULL");
    } else {
        while (temp != NULL) {
            printf("[ %d|@-]-->", temp->value);
            temp = temp->nexts[level];
        }
        printf("NULL");
    }
    printf("\n");
}

void displayAllLevels(List *list, int maxLevels) {
    for (int i = 0; i < maxLevels; i++) {
        displayLevel(list, i, maxLevels);
    }
    printf("\n");
}

void Cell_AddAt(List *list, Cell *cell, int level) {
    Cell *temp = list->heads[level];
    Cell *prev = NULL;    // Car prev est la cellule avant temp
    while (temp != NULL && temp->value <= cell->value) {
        prev = temp;
        temp = temp->nexts[level];
    }
    if (prev == NULL) {    // Si la nouvelle cellule est plus petite que la tete
        cell->nexts[level] = list->heads[level];
        list->heads[level] = cell;
    } else {
        prev->nexts[level] = cell;
        cell->nexts[level] = temp;
    }
}

int nbDivideBy2(int n) {
    int result = 0;
    while ((n % 2 == 0) && (n != 0)) {
        result++;
        n = n / 2;
    }
    return result;
}

void Leveled_List(List *list, int n) {
    int *levels;
    int cases = pow(2, n) - 1;
    //On cree le tableau levels pour savoir les levels de chaque membre de la leveled list
    Cell *temp = list->heads[0];
    levels = (int *) malloc(cases * sizeof(int));
    Cell *tempcase = list->heads[0];
    int taille;
    //Boucle pour savoir la taille logique/reel de la liste
    //Niv 0 plus grand ds une lvl_list -> faire le test de taille que sur niv 0
    while (tempcase != NULL) {
        tempcase = tempcase->nexts[0];
        taille++;
    }
    //Remplie le tableau de levels
    for (int i = 0; i < taille; i++) {
        levels[i] = nbDivideBy2(i + 1);
        temp->nbLevels = levels[i];
        temp = temp->nexts[0];
    }
    //Systeme de double boucle conditionnel complexe
    //Permet de leveliser la liste a partir d'une liste a niv remplie au niv 0
    for (int i = 1; i < n; i++) {
        temp = list->heads[0];
        for (int j = 0; j < taille; j++) {
            if (levels[j] == i && list->heads[i] == NULL) { //insere a la head pr niv i
                list->heads[i] = temp;
                list->heads[i]->nexts[i] = NULL;
            }
            if (levels[j] >= i && list->heads[i] != NULL) {  //insere au milieu ou fin pr niv i
                Cell *subtemp = list->heads[i];
                while (subtemp->nexts[i] != NULL) {
                    subtemp = subtemp->nexts[i];
                }
                subtemp->nexts[i] = temp;
                subtemp = subtemp->nexts[i];
                subtemp->nexts[i] = NULL;
            }
            temp = temp->nexts[0];
        }
    }
}

void classicSearch(List *list, int val) {  // Recherche au niveau 0
    displayLevel(list, 0, list->heads[0]->nbLevels);
    Cell *temp = list->heads[0];
    while (temp != NULL && temp->value != val) {
        temp = temp->nexts[0];
    }
    if (temp != NULL && temp->value == val) {
        //printf("%d found at level 0\n", val);
        return;
    } else {
        //printf("%d not found at level 0\n", val);
    }
}

void SearchAll(List *list, int val, int maxLevels) {
    unsigned short alwaysAtHead = 1;
    Cell *temp = list->heads[maxLevels - 1];
    while (maxLevels > 0 && temp->value != val) {
        if (temp->nexts[maxLevels - 1] == NULL || temp->nexts[maxLevels - 1]->value > val) {
            maxLevels--;
            if (alwaysAtHead) {
                if ((temp->value > val)) {
                    temp = list->heads[maxLevels - 1];
                } else {
                    alwaysAtHead = 0;
                }
            }
        } else {
            temp = temp->nexts[maxLevels - 1];
            alwaysAtHead = 0;
        }
    }
    if (maxLevels <= 0) {
        printf("%d not found in any level\n", val);
    } else {
        printf("%d found et level %d\n", val, maxLevels);
    }
}

void complexity(int min, int max) {
    srand(time(NULL));
    for (int Levelact = min; Levelact < max; Levelact++) {
        printf("Test du niveau %d :", Levelact);
        List *list = createEmptyList(Levelact);
        Leveled_List(list, Levelact);
        int limite = (1 << Levelact) - 1;
        startTimer();
        for (int num = 0; num < 10000; num++) {
            classicSearch(list, rand() % limite + 1);
        }
        stopTimer();
        displayTime();
        startTimer();
        for (int num = 0; num < 10000; num++) {
            SearchAll(list, rand() % limite + 1, Levelact);
        }
        stopTimer();
        displayTime();
    }
}