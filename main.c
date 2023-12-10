#include <stdio.h>
#include <stdlib.h>
#include "diary-management.h"
#include "list.h"


int main() {
    int maxLevels = 3;

    List* list = createEmptyList(6);
    List* mylist = createEmptyList(maxLevels);


    //TEST LEVELED_LIST
    List *leveled_list = createEmptyList(maxLevels);

    Cell *cell1 = createCell(1, 3);
    Cell *cell2 = createCell(2, 3);
    Cell *cell3 = createCell(3, 3);
    Cell *cell4 = createCell(4, 3);
    Cell *cell5 = createCell(5, 3);
    Cell *cell6 = createCell(6, 3);
    Cell *cell7 = createCell(7, 3);

    displayAllLevels(leveled_list, 3);
    printf("\n");

    Cell_AddAt(leveled_list, cell1, 0);
    Cell_AddAt(leveled_list, cell2, 0);
    Cell_AddAt(leveled_list, cell3, 0);
    Cell_AddAt(leveled_list, cell4, 0);
    Cell_AddAt(leveled_list, cell5, 0);
    Cell_AddAt(leveled_list, cell6, 0);
    Cell_AddAt(leveled_list, cell7, 0);

    displayAllLevels(leveled_list, 3);

    Leveled_List(leveled_list, 3);

    printf("\n");

    displayAllLevels(leveled_list, 3);

    //Display List Ethetique

    printf("\n");

    displaySortedAll(leveled_list, 3);




    //COMPLEXITY

    FILE *log_file = fopen("log.txt","a");
    char format[] = "%d\t%s\t%s\n" ;
    char *time_lvl0;
    char *time_all_levels;
    int nb_recherche = 1000;
    fprintf(log_file, "\n");
    fprintf(log_file, "Nombre de recherche: %d\n\n", nb_recherche);
    for (int i = 7 ; i<16 ; i++)
    {
        int level = i;
        complexity(level,nb_recherche,&time_lvl0, &time_all_levels);
        fprintf(log_file,format,level,time_lvl0, time_all_levels);
    }
    fclose(log_file);


    //PART 3

    // Initialize the level list
    struct LevelList levelList;
    for (int i = 0; i < 4; i++) {
        levelList.nodes[i] = NULL;
    }

    int choice;

    do {
        printf("\nMenu:\n");
        printf("1. Search for a contact\n");
        printf("2. View a contact's appointments\n");
        printf("3. Create a contact\n");
        printf("4. Create an appointment for a contact\n");
        printf("5. Delete an appointment\n");
        printf("6. Save appointments\n");
        printf("7. Load appointments\n");
        printf("8. Load Contacts\n");
        printf("9. Calculate insertion times\n");
        printf("0. Exit\n");

        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                searchContact(&levelList);
                break;
            case 2:
                viewAppointments(&levelList);
                break;
            case 3:
                createContact(&levelList);
                break;
            case 4:
                createAppointment(&levelList);
                break;
            case 5:
                deleteAppointment(&levelList);
                break;
            case 6:
                saveAppointments(&levelList);
                break;
            case 7:
                loadAppointments(&levelList);
                break;
            case 8:
                loadContacts(&levelList);
                break;
            case 9:
                calculateInsertionTimes(&levelList);
                break;

            case 0:
                printf("Exiting the program.\n");
                break;
            default:
                printf("Invalid choice. Please try again.\n");
        }

    } while (choice != 0);


    return 0;
}