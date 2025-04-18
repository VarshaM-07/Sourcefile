// admin_search.c
#include <stdio.h>
#include <string.h>
#include "admin_search.h"

void searchStudentByID() {
    char id[8];
    struct Student s;
    int found = 0;

    FILE *fp = fopen("students.txt", "r");
    if (fp == NULL) {
        printf("? Error: Could not open student data file.\n");
        return;
    }

    printf("Enter 7-digit Digital ID of the student: ");
    scanf("%7s", id);

    while (fscanf(fp, "%[^|]|%[^|]|%[^|]|%[^|]|%[^|]|%[^|]|%[^\n]\n",
                  s.digitalID, s.name, s.department, s.college, s.year, s.phone, s.email) != EOF) {
        if (strcmp(s.digitalID, id) == 0) {
            found = 1;
            printf("\n? Student Found!\n");
            printf("--------------------------\n");
            printf("Digital ID  : %s\n", s.digitalID);
            printf("Name        : %s\n", s.name);
            printf("Department  : %s\n", s.department);
            printf("College     : %s\n", s.college);
            printf("Year        : %s\n", s.year);
            printf("Phone       : %s\n", s.phone);
            printf("Email       : %s\n", s.email);
            printf("--------------------------\n");
            break;
        }
    }

    if (!found) {
        printf("\n? No student found with Digital ID: %s\n", id);
    }

    fclose(fp);
}

