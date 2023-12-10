
#include "diary-management.h"
char *scanString(void) {
    char buffer[256];
    char *dynamicCharArray;

    printf("Enter a string: ");
    scanf("%255s", buffer);

    // Allocate memory for the dynamic character array
    dynamicCharArray = (char *)malloc(strlen(buffer) + 1);

    if (dynamicCharArray != NULL) {
        strcpy(dynamicCharArray, buffer);
    } else {
        // Handle memory allocation failure
        printf("Memory allocation failed.\n");
        exit(EXIT_FAILURE);
    }

    // Consume any additional characters, such as the newline, left in the buffer
    while (getchar() != '\n');

    return dynamicCharArray;
}
// Function to compare two strings in lexicographical order
int compareStrings(const char *str1, const char *str2) {
    while (*str1 && *str2) {
        char ch1 = tolower(*str1);
        char ch2 = tolower(*str2);

        if (ch1 < ch2) {
            return -1;
        } else if (ch1 > ch2) {
            return 1;
        }

        str1++;
        str2++;
    }

    // Strings are equal up to the length of the shorter string
    if (*str1) {
        return 1; // str1 is longer
    } else if (*str2) {
        return -1; // str2 is longer
    }

    return 0; // Strings are equal
}

// Function to convert a string to lowercase
void toLowerCase(char *str) {
    while (*str) {
        *str = tolower(*str);
        str++;
    }
}

// Function to get the level based on the current index
int getLevel(const char *str, int index) {
    if (str[index] == '\0') {
        return -1; // End of string
    }

    char ch = tolower(str[index]);

    if (ch >= 'a' && ch <= 'z') {
        return ch - 'a';
    }

    return 26; // For characters outside 'a' to 'z'
}

// Function to insert a calendar entry into the level list
void insertIntoLevelList(struct LevelList *levelList, struct CalendarEntry *entry) {
    struct LevelListNode *newNode = (struct LevelListNode *)malloc(sizeof(struct LevelListNode));
    if (newNode == NULL) {
        // Handle memory allocation failure
        printf("Memory allocation failed.\n");
        exit(EXIT_FAILURE);
    }

    newNode->entry = entry;
    newNode->next = NULL;

    int level = 3; // Start at the highest level

    struct LevelListNode **current = &levelList->nodes[level];

    while (level >= 0) {
        // Find the appropriate position at the current level
        while (*current != NULL && compareStrings((*current)->entry->contact.surname, entry->contact.surname) < 0) {
            current = &(*current)->next;
        }

        // Insert the node at the current level
        newNode->next = *current;
        *current = newNode;
        level--;

        if (level >= 0) {
            // Move to the next level
            current = &newNode->next;
        }
    }
}
// Function to search for a contact in the level list
struct CalendarEntry *searchInLevelList(struct LevelList *levelList, const char *searchKey) {
    int level = 3; // Start at the highest level

    struct LevelListNode *current = levelList->nodes[level];

    // Convert the search key to lowercase
    char lowercaseSearchKey[256];
    strcpy(lowercaseSearchKey, searchKey);
    toLowerCase(lowercaseSearchKey);

    while (level >= 0 && current != NULL) {
        // Search for the contact at the current level
        while (current != NULL && compareStrings(current->entry->contact.surname, lowercaseSearchKey) < 0) {
            current = current->next;
        }

        if (current != NULL && compareStrings(current->entry->contact.surname, lowercaseSearchKey) == 0) {
            // Contact found
            return current->entry;
        }

        level--;

        if (level >= 0) {
            // Move to the next level
            current = current->next;
        }
    }

    // Contact not found
    return NULL;
}

// Function to search for a contact and propose automatic completion
void searchContact(struct LevelList *levelList) {
    char searchKey[256];
    printf("Enter the contact's name for search: ");
    scanf("%255s", searchKey);
    getchar(); // Consume the newline character left by scanf

    // Search for the contact in the level list
    struct CalendarEntry *foundEntry = searchInLevelList(levelList, searchKey);

    if (foundEntry != NULL) {
        // Contact found
        printf("Contact found: %s, %s\n", foundEntry->contact.surname, foundEntry->contact.firstName);
        // Additional actions for displaying or processing the contact information
    } else {
        printf("Contact not found.\n");
        // Additional actions for handling the case when the contact is not found
    }
}

// Function to view a contact's appointments
void viewAppointments(struct LevelList *levelList) {
    char searchKey[256];
    printf("Enter the contact's name for viewing appointments: ");
    scanf("%255s", searchKey);
    getchar(); // Consume the newline character left by scanf

    // Convert the search key to lowercase
    toLowerCase(searchKey);

    // Search for the contact in the level list
    struct CalendarEntry *foundEntry = searchInLevelList(levelList, searchKey);

    if (foundEntry != NULL) {
        // Contact found, display appointments
        printf("Appointments for %s, %s:\n", foundEntry->contact.surname, foundEntry->contact.firstName);
        struct Appointment *currentAppointment = foundEntry->contact.appointments;

        while (currentAppointment != NULL) {
            // Display or process each appointment
            printf("Date: %d/%d/%d, Time: %02d:%02d, Duration: %02d:%02d, Purpose: %s\n",
                   currentAppointment->day, currentAppointment->month, currentAppointment->year,
                   currentAppointment->hour, currentAppointment->minute,
                   currentAppointment->durationHour, currentAppointment->durationMinute,
                   currentAppointment->purpose);

            currentAppointment = currentAppointment->next;
        }
    } else {
        printf("Contact not found.\n");
        // Additional actions for handling the case when the contact is not found
    }
}

// Function to create a contact and insert it into the level list
void createContact(struct LevelList *levelList) {
    struct CalendarEntry *newEntry = (struct CalendarEntry *)malloc(sizeof(struct CalendarEntry));
    if (newEntry == NULL) {
        // Handle memory allocation failure
        printf("Memory allocation failed.\n");
        exit(EXIT_FAILURE);
    }

    // Initialize the new contact
    printf("Enter the contact's surname: ");
    newEntry->contact.surname = scanString();
    printf("Enter the contact's first name: ");
    newEntry->contact.firstName = scanString();
    newEntry->contact.appointments = NULL;
    // Insert the contact into the level list
    insertIntoLevelList(levelList, newEntry);

    printf("Contact created and inserted into the level list.\n");
}
void createAppointment(struct LevelList *levelList) {
    char searchKey[256]; // Adjust the buffer size accordingly
    printf("Enter the contact's name for appointment: ");
    scanf("%255s", searchKey);
    getchar(); // Consume the newline character left by scanf

    // Convert the search key to lowercase
    toLowerCase(searchKey);

    // Search for the contact in the level list
    struct CalendarEntry *foundEntry = searchInLevelList(levelList, searchKey);

    if (foundEntry != NULL) {
        // Contact found, create and insert appointment
        struct Appointment *newAppointment = (struct Appointment *)malloc(sizeof(struct Appointment));
        if (newAppointment == NULL) {
            // Handle memory allocation failure
            printf("Memory allocation failed.\n");
            exit(EXIT_FAILURE);
        }

        // Initialize the new appointment
        printf("Enter appointment date (day month year): ");
        scanf("%d %d %d", &newAppointment->day, &newAppointment->month, &newAppointment->year);
        getchar(); // Consume the newline character left by scanf

        printf("Enter appointment time (hour minute): ");
        scanf("%d %d", &newAppointment->hour, &newAppointment->minute);
        getchar(); // Consume the newline character left by scanf

        printf("Enter appointment duration (hour minute): ");
        scanf("%d %d", &newAppointment->durationHour, &newAppointment->durationMinute);
        getchar(); // Consume the newline character left by scanf

        printf("Enter the purpose of the appointment: ");
        newAppointment->purpose = scanString();


        // Insert the appointment into the contact's list
        newAppointment->next = foundEntry->contact.appointments;
        foundEntry->contact.appointments = newAppointment;

        printf("Appointment created and inserted for %s, %s.\n", foundEntry->contact.surname, foundEntry->contact.firstName);
    } else {
        printf("Contact not found.\n");
        // Additional actions for handling the case when the contact is not found
    }
}
void deleteAppointment(struct LevelList *levelList) {
    char searchKey[256]; // Adjust the buffer size accordingly
    printf("Enter the contact's name for appointment deletion: ");
    scanf("%255s", searchKey);
    getchar(); // Consume the newline character left by scanf

    // Convert the search key to lowercase
    toLowerCase(searchKey);

    // Search for the contact in the level list
    struct CalendarEntry *foundEntry = searchInLevelList(levelList, searchKey);

    if (foundEntry != NULL) {
        // Contact found, delete appointment
        int appointmentNumber;
        printf("Enter the number of the appointment to delete: ");
        scanf("%d", &appointmentNumber);
        getchar(); // Consume the newline character left by scanf

        struct Appointment *currentAppointment = foundEntry->contact.appointments;
        struct Appointment *previousAppointment = NULL;
        int count = 1;

        while (currentAppointment != NULL && count < appointmentNumber) {
            previousAppointment = currentAppointment;
            currentAppointment = currentAppointment->next;
            count++;
        }

        if (currentAppointment != NULL) {
            // Delete the appointment
            if (previousAppointment != NULL) {
                previousAppointment->next = currentAppointment->next;
            } else {
                foundEntry->contact.appointments = currentAppointment->next;
            }

            free(currentAppointment->purpose);
            free(currentAppointment);

            printf("Appointment deleted for %s, %s.\n", foundEntry->contact.surname, foundEntry->contact.firstName);
        } else {
            printf("Invalid appointment number.\n");
        }
    } else {
        printf("Contact not found.\n");

    }
}

void saveAppointments(struct LevelList *levelList) {
    char filename[256]; // Adjust the buffer size accordingly
    printf("Enter the filename to save appointments: ");
    scanf("%255s", filename);
    getchar(); // Consume the newline character left by scanf

    FILE *file = fopen(filename, "w");
    if (file == NULL) {
        // Handle file opening failure
        printf("Error opening file for writing.\n");
        return;
    }

    // Write appointments to the file
    for (int i = 3; i >= 0; i--) {
        struct LevelListNode *currentNode = levelList->nodes[i];
        while (currentNode != NULL) {
            struct CalendarEntry *currentEntry = currentNode->entry;

            // Write contact information
            fprintf(file, "Contact: %s, %s\n", currentEntry->contact.surname, currentEntry->contact.firstName);

            // Write appointments
            struct Appointment *currentAppointment = currentEntry->contact.appointments;
            while (currentAppointment != NULL) {
                fprintf(file, "Appointment: %d/%d/%d %02d:%02d %02d:%02d %s\n",
                        currentAppointment->day, currentAppointment->month, currentAppointment->year,
                        currentAppointment->hour, currentAppointment->minute,
                        currentAppointment->durationHour, currentAppointment->durationMinute,
                        currentAppointment->purpose);

                currentAppointment = currentAppointment->next;
            }

            currentNode = currentNode->next;
        }
    }

    fclose(file);
    printf("Appointments saved to %s.\n", filename);
}

void loadContacts(struct LevelList *levelList) {
    char filename[256]; // Adjust the buffer size accordingly
    printf("Enter the filename to load contacts: ");
    scanf("%255s", filename);
    getchar(); // Consume the newline character left by scanf

    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        // Handle file opening failure
        printf("Error opening file for reading.\n");
        return;
    }

    // Read contacts from the file
    while (!feof(file)) {
        char line[256];
        fgets(line, sizeof(line), file);
        // Remove the newline character at the end
        line[strcspn(line, "\n")] = '\0';

        // Convert the contact name to lowercase
        toLowerCase(line);

        // Create and insert a new contact into the level list
        struct CalendarEntry *newEntry = (struct CalendarEntry *)malloc(sizeof(struct CalendarEntry));
        newEntry->contact.surname = strdup(line);
        newEntry->contact.firstName = ""; // Assuming a contact line doesn't contain first name
        newEntry->contact.appointments = NULL;

        // Insert the contact into the level list
        insertIntoLevelList(levelList, newEntry);
    }

    fclose(file);
    printf("Contacts loaded from %s.\n", filename);
}

void loadAppointments(struct LevelList *levelList) {
    char filename[256]; // Adjust the buffer size accordingly
    printf("Enter the filename to load appointments: ");
    scanf("%255s", filename);
    getchar(); // Consume the newline character left by scanf

    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        // Handle file opening failure
        printf("Error opening file for reading.\n");
        return;
    }

    // Read appointments from the file
    while (!feof(file)) {
        char line[256];
        fgets(line, sizeof(line), file);

        // Check if the line starts with "Contact:" or "Appointment:"
        if (strncmp(line, "Contact:", 8) == 0) {
            // Parse and add a new contact
            char *contactName = line + 8;
            toLowerCase(contactName);
            struct CalendarEntry *newEntry = (struct CalendarEntry *)malloc(sizeof(struct CalendarEntry));
            newEntry->contact.surname = strdup(contactName);
            newEntry->contact.firstName = ""; // Assuming a contact line doesn't contain first name
            newEntry->contact.appointments = NULL;

            // Insert the contact into the level list
            insertIntoLevelList(levelList, newEntry);
        } else if (strncmp(line, "Appointment:", 12) == 0) {
            // Parse and add a new appointment
            char *appointmentInfo = line + 12;
            int day, month, year, hour, minute, durationHour, durationMinute;
            char purpose[256];

            sscanf(appointmentInfo, "%d/%d/%d %d:%d %d:%d %[^\n]",
                   &day, &month, &year, &hour, &minute, &durationHour, &durationMinute, purpose);

            // Find the contact in the level list
            char contactName[256];
            strcpy(contactName, purpose); // Assuming the contact name is stored in the purpose field
            toLowerCase(contactName);

            struct CalendarEntry *foundEntry = searchInLevelList(levelList, contactName);

            if (foundEntry != NULL) {
                // Create and insert the new appointment
                struct Appointment *newAppointment = (struct Appointment *)malloc(sizeof(struct Appointment));
                newAppointment->day = day;
                newAppointment->month = month;
                newAppointment->year = year;
                newAppointment->hour = hour;
                newAppointment->minute = minute;
                newAppointment->durationHour = durationHour;
                newAppointment->durationMinute = durationMinute;
                newAppointment->purpose = strdup(purpose);

                // Insert the appointment into the contact's list
                newAppointment->next = foundEntry->contact.appointments;
                foundEntry->contact.appointments = newAppointment;
            }
        }
    }

    fclose(file);
    printf("Appointments loaded from %s.\n", filename);
}

void calculateInsertionTimes(struct LevelList *levelList) {
    // Measure execution times for insertion at each level
    clock_t start, end;

    // Insertion at level 0 only
    start = clock();
    // Create and insert a contact at level 0
    struct CalendarEntry *newEntry = (struct CalendarEntry *)malloc(sizeof(struct CalendarEntry));
    printf("Enter surname: ");
    newEntry->contact.surname = scanString();
    getchar();
    printf("Enter firstname: ");
    newEntry->contact.firstName = scanString();
    getchar();
    newEntry->contact.appointments = NULL;
    end = clock();
    printf("Time for insertion at level 0: %f seconds\n", ((double) (end - start)) / CLOCKS_PER_SEC);

    // Insertion from the highest level
    start = clock();
    printf("Enter surname: ");
    newEntry->contact.surname = scanString();
    getchar();
    printf("Enter firstname: ");
    newEntry->contact.firstName = scanString();
    getchar();
    newEntry->contact.appointments = NULL;

    end = clock();
    printf("Time for insertion from the highest level: %f seconds\n", ((double) (end - start)) / CLOCKS_PER_SEC);
}


