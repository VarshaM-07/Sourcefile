#include <stdio.h>
#include <string.h>
#include "admin_search.h"

void searchStudentByID() {
    char id[50];  // match size with teammate's format
    struct Student s;
    int found = 0;

    FILE *fp = fopen("students.txt", "r");
    if (fp == NULL) {
        printf("? Error: Could not open student data file.\n");
        return;
    }

    printf("Enter Digital ID of the student: ");
    scanf("%s", id);

    char line[256];
    while (fgets(line, sizeof(line), fp)) {
        if (strncmp(line, "  Digital ID:", 13) == 0) {
            sscanf(line, "  Digital ID: %[^\n]", s.digitalID);

            fgets(line, sizeof(line), fp); sscanf(line, "  Name: %[^\n]", s.name);
            fgets(line, sizeof(line), fp); sscanf(line, "  Email: %[^\n]", s.email);
            fgets(line, sizeof(line), fp); sscanf(line, "  Phone: %[^\n]", s.phone);
            fgets(line, sizeof(line), fp); sscanf(line, "  Digital ID: %[^\n]", s.digitalID);  // redundant, but keeping the order
            fgets(line, sizeof(line), fp); sscanf(line, "  Year: %[^\n]", s.year);

            if (strcmp(s.digitalID, id) == 0) {
                found = 1;
                printf("\n? Student Found!\n");
                printf("--------------------------\n");
                printf("Digital ID  : %s\n", s.digitalID);
                printf("Name        : %s\n", s.name);
                printf("Email       : %s\n", s.email);
                printf("Phone       : %s\n", s.phone);
                printf("Year        : %s\n", s.year);
                printf("--------------------------\n");
                break;
            }
        }
    }

    if (!found) {
        printf("\n? No student found with Digital ID: %s\n", id);
    }

    fclose(fp);
}

void deleteStudentByID() {
    char id[50];
    printf("Enter Digital ID of the student to delete: ");
    scanf("%s", id);

    FILE *fp = fopen("students.txt", "r");
    FILE *temp = fopen("temp.txt", "w");
    if (fp == NULL || temp == NULL) {
        printf("? Error: Could not open file.\n");
        return;
    }

    char line[256];
    int found = 0;
    int skip = 0;

    while (fgets(line, sizeof(line), fp)) {
        if (strncmp(line, "  Digital ID:", 13) == 0) {
            char currID[50];
            sscanf(line, "  Digital ID: %[^\n]", currID);

            if (strcmp(currID, id) == 0) {
                found = 1;
                skip = 1;
            }

            if (!skip) fprintf(temp, "%s", line);
        } else {
            if (!skip) fprintf(temp, "%s", line);
            if (strstr(line, "-------------------------")) {
                skip = 0;
            }
        }
    }

    fclose(fp);
    fclose(temp);

    if (found) {
        remove("students.txt");
        rename("temp.txt", "students.txt");
        printf("? Student with ID %s has been removed.\n", id);
    } else {
        remove("temp.txt");
        printf("?? No student found with ID %s.\n", id);
    }
}
