#ifndef DIARY_MANAGEMENT_H
#define DIARY_MANAGEMENT_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
// Structure for an appointment
struct Appointment {
    int day, month, year;
    int hour, minute;
    int durationHour, durationMinute;
    char *purpose;
    struct Appointment *next;
};

// Structure for a contact
struct Contact {
    char *surname;
    char *firstName;
    struct Appointment *appointments;  // Linked list of appointments for this contact
};

// Structure for a calendar entry
struct CalendarEntry {
    struct Contact contact;
    struct CalendarEntry *next;  // Linked list of calendar entries
};

// Structure for a level list node
struct LevelListNode {
    struct CalendarEntry *entry;
    struct LevelListNode *next;
};

// Structure for a level list
struct LevelList {
    struct LevelListNode *nodes[4];
};

// Function to input dynamic arrays of characters
char *scanString(void);

// Function to compare two strings in lexicographical order
int compareStrings(const char *str1, const char *str2);

// Function to convert a string to lowercase
void toLowerCase(char *str);

// Function to insert a calendar entry into the level list
void insertIntoLevelList(struct LevelList *levelList, struct CalendarEntry *entry);

// Function to search for a contact in the level list
struct CalendarEntry *searchInLevelList(struct LevelList *levelList, const char *searchKey);

// Function to search for a contact and propose automatic completion
void searchContact(struct LevelList *levelList);

// Function to view a contact's appointments
void viewAppointments(struct LevelList *levelList);

// Function to create a contact and insert it into the level list
void createContact(struct LevelList *levelList);

// Function to create an appointment for a contact
void createAppointment(struct LevelList *levelList);

// Function to delete an appointment
void deleteAppointment(struct LevelList *levelList);

// Function to save the file of all appointments
void saveAppointments(struct LevelList *levelList);

// Function to load an appointment file
void loadAppointments(struct LevelList *levelList);

// Function to provide calculation times for inserting a new contact
void calculateInsertionTimes(struct LevelList *levelList);

void loadContacts(struct LevelList *levelList);
#endif // DIARY_MANAGEMENT_H
