#include "agenda.h"
#include "string.h"
#include <ctype.h>

char *scanstring(void) {
    char string[100];
    scanf("%s", string);  // Use %s to read a string

    size_t length = strlen(string);

    // Allocate memory for the buffer (including space for the null terminator)
    char *buffer = (char *) malloc((length + 1) * sizeof(char));

    // Copy the string to the dynamically allocated buffer
    strcpy(buffer, string);

    for (size_t i = 0; i < length; ++i) {
        buffer[i] = tolower(buffer[i]);
    }

    return buffer;
}

Agenda *SaisirAgenda(void) {
    Agenda *agenda = (Agenda *) malloc(sizeof(Agenda));
    printf("Prenom:");
    agenda->contact.prenom = scanstring();
    printf("Nom:");
    agenda->contact.nom = scanstring();
    return agenda;
}

CellAgenda *createCellAgenda(Agenda value, int nbLevels) {
    CellAgenda *newCell = (CellAgenda *) malloc(sizeof(CellAgenda));
    newCell->value = value;
    newCell->nbLevels = nbLevels;
    newCell->nexts = (struct CellAgenda **) malloc(nbLevels * sizeof(struct CellAgenda *));
    for (int i = 0; i < nbLevels; i++) {
        newCell->nexts[i] = NULL;
    }
    return newCell;
}

void PrintAgenda(Agenda *agenda) {
    printf("%s %s", agenda->contact.nom, agenda->contact.prenom);
}

AgendaList *createEmptyAgenda(int maxLevels) {
    AgendaList *Agenda = (AgendaList *) malloc(sizeof(AgendaList));
    Agenda->heads = (struct CellAgenda **) malloc(maxLevels * sizeof(struct Cell *));

    for (int i = 0; i < maxLevels; i++) {
        Agenda->heads[i] = NULL;
    }
    return Agenda;
}

void Cell_AddHeadAgenda(AgendaList *Agenda, CellAgenda *cell, int maxLevels) {
    int nbLevels = cell->nbLevels;

    if (nbLevels > maxLevels) {    // reduit le nombre de cellule d'une valeur si ça depasse le nombre de niveaux total
        nbLevels = maxLevels;
    }

    for (int i = 0; i < nbLevels; i++) {
        cell->nexts[i] = Agenda->heads[i];
        Agenda->heads[i] = cell;
    }
}

void Cell_AddAtAgenda(AgendaList *Agenda, CellAgenda *cell, int level) {
    CellAgenda *temp = Agenda->heads[level];
    CellAgenda *prev = NULL;    // Car prev est la cellule avant temp
    int i = 0;
    while (temp != NULL && strcmp(temp->value.contact.nom, cell->value.contact.nom) < 0) {
        prev = temp;
        temp = temp->nexts[level];
    }
    if (prev == NULL) {    // Si la nouvelle cellule est plus petite que la tete
        cell->nexts[level] = Agenda->heads[level];
        Agenda->heads[level] = cell;
    } else {
        prev->nexts[level] = cell;
        cell->nexts[level] = temp;
    }
}

//LISTE AGENDA

void displayLevelAgenda(AgendaList *Agenda, int level, int maxLevels) {
    if (level < 0 || level > maxLevels) {
        printf("Niveau invalide\n");  // Affiche un message d'erreur si le niveau qu'on veut n'existe pas
        return;
    }
    printf("[list head_%d @-]-->", level);

    CellAgenda *temp = Agenda->heads[level];
    if (temp == NULL) {
        printf("NULL");
    } else {
        while (temp != NULL) {
            printf("[ ");
            PrintAgenda(&temp->value);
            printf(" |@-]-->");
            temp = temp->nexts[level];
        }
        printf("NULL");
    }
    printf("\n");
}

void displayAllLevelsAgenda(AgendaList *list, int maxLevels) {
    for (int i = 0; i < maxLevels; i++) {
        displayLevelAgenda(list, i, maxLevels);
    }
}





