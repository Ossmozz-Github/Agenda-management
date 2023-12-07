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

Contact createContact(void) {
    Contact contact;
    printf("Saisissez votre nom (appuyez sur Entree pour valider) :");
    contact.prenom = scanstring();
    printf("\n");
    printf("Saisissez votre prénom (appuyez sur Entree pour valider) :");
    contact.nom = scanstring();
    printf("\n");

    return contact;
}

void printContact(Contact contact) {
    printf("Contact: %s %s", contact.nom, contact.prenom);
}

Date *createDate(int jour, int mois, int annee) {
    Date *date = (Date *) malloc(sizeof(Date));
    date->jour = jour;
    date->mois = mois;
    date->annee = annee;
    return date;
}

int verifierDate(Date date) {

    if ((date.jour >= 29) && (date.mois == 02)) {

        if ((date.annee % 4 != 0) || ((date.annee % 4 == 0) && (date.annee % 100 == 0))) {
            return 0;
        }
    }
    if ((date.jour == 31) &&
        ((date.mois == 2) || (date.mois == 4) || (date.mois == 6) || (date.mois == 9) || (date.mois == 11))) {
        return 0;
    }
    if ((date.jour > 31) || (date.mois > 12) || (date.annee < 2023) || (date.jour < 0) || (date.mois < 0) ||
        (date.annee < 0)) {
        return 0;
    }
    return 1;
}

void printDate(Date date) {
    char jour[3], mois[3], annee[5], sdate[11]; // Alloue l'espace pour les chaînes de caractères

    // Convertie le jour, le mois, et l'année en chaînes de caractères
    sprintf(jour, "%02d", date.jour); // %02d ensures at least 2 digits with leading zero if needed
    sprintf(mois, "%02d", date.mois);
    sprintf(annee, "%d", date.annee);

    strcpy(sdate, jour); // Copie le jour dans sdate

    strcat(sdate, "/"); // Ajoute "/" pour séparer

    strcat(sdate, mois); // Ajoute le mois dans sdate
    strcat(sdate, "/"); // Ajoute "/" pour séparer

    strcat(sdate, annee); // Ajoute l'année dans sdate

    printf("Date: %s", sdate);
}

Heure *createHeure(int heure, int minute) {
    Heure *pheure = (Heure *) malloc(sizeof(Heure));
    pheure->heure = heure;
    pheure->minute = minute;
    return pheure;
}


int verifierHeure(Heure heure) {
    if ((heure.minute >= 60) || (heure.minute < 0)) {
        return 0;
    }
    if ((heure.heure >= 24) || (heure.heure < 0)) {
        return 0;
    }
    return 1;
}

void printHeure(Heure pheure) {
    char heure[3], minute[3], sheure[7];
    sprintf(heure, "%02d", pheure.heure);
    sprintf(minute, "%02d", pheure.minute);

    strcpy(sheure, heure);

    strcat(sheure, ":");

    strcat(sheure, minute);
    printf("Heure: %s", sheure);
}

Duree *createDuree(int heures, int minutes) {
    Duree *duree = (Duree *) malloc(sizeof(Duree));
    duree->heures = heures;
    duree->minutes = minutes;
    return duree;
}

/*int verifierDuree(Duree duree) {
    return verifierHeure(duree);
}

void printDuree(Duree duree) {
    printHeure(duree);
 */

Rdv *createRdv(Date date, Heure heureDebut, Duree duree, char *objet) {
    Rdv *rdv = (Rdv *) malloc(sizeof(Rdv));
    rdv->date = date;
    rdv->heureDebut = heureDebut;
    rdv->duree = duree;
    rdv->objet = objet;
    return rdv;
}

/*int verifierRdv(Rdv rdv) {
    if ((verifierDate(rdv.date) == 1) && (verifierDuree(rdv.duree) == 1) && (verifierHeure(rdv.heureDebut) == 1)) {
        return 1;
    } else {
        return 0;
    }
} */

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
    while (temp != NULL && strcmp(temp->value.contact.nom, cell->value.contact.nom) < 0) { // compa
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