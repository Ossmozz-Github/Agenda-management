#ifndef AGENDA_MANAGEMENT_PROJECT_AGENDA_H
#define AGENDA_MANAGEMENT_PROJECT_AGENDA_H

#include <stdlib.h>
#include <stdio.h>

typedef struct Contact {
    char *nom;
    char *prenom;
} Contact;

typedef struct Date {
    int jour;
    int mois;
    int annee;
} Date;

typedef struct Heure {
    int heure;
    int minute;
} Heure;

typedef struct Duree {
    int heures;
    int minutes;
} Duree;

typedef struct Rdv {
    Date date;
    Heure heureDebut;
    Duree duree;
    char *objet;
} Rdv;

char *scanstring(void);

//LISTE SIMPLEMENT CHAINEE

typedef struct cellRdv {
    Rdv value;
    struct cellRdv *next;
} cellRdv;

typedef struct listRdv {
    cellRdv *head;
} listRdv;

typedef struct Agenda {
    Contact contact;
    listRdv list;
} Agenda;

typedef struct CellAgenda {
    Agenda value;
    struct CellAgenda **nexts;  // Tableau de pointeurs vers les niveaux
    int nbLevels;  // Nombre de niveaux
} CellAgenda;

//LISTE AGENDA

typedef struct AgendaList {
    struct CellAgenda **heads;  // Têtes de la liste pour chaque niveau
} AgendaList;

Agenda *SaisirAgenda(void);

void PrintAgenda(Agenda *agenda);

CellAgenda *createCellAgenda(Agenda value, int nbLevels);

void Cell_AddHeadAgenda(AgendaList *Agenda, CellAgenda *cell, int maxLevels);

AgendaList *createEmptyAgenda(int maxLevels);

void Cell_AddAtAgenda(AgendaList *Agenda, CellAgenda *cell, int level);

void displayLevelAgenda(AgendaList *Agenda, int level, int maxLevels);

void displayAllLevelsAgenda(AgendaList *Agenda, int maxLevels);

#endif