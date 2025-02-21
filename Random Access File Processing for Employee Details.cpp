#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int id;
    char name[30];
    float salary;
} Employee;

void addEmployee(FILE *file) {
    Employee e;
    printf("Enter Employee ID: ");
    scanf("%d", &e.id);
    printf("Enter Name: ");
    scanf("%s", e.name);
    printf("Enter Salary: ");
    scanf("%f", &e.salary);

    fseek(file, (e.id - 1) * sizeof(Employee), SEEK_SET);
    fwrite(&e, sizeof(Employee), 1, file);
    printf("Employee record added successfully!\n");
}

void displayEmployee(FILE *file) {
    Employee e;
    int id;
    printf("Enter Employee ID to display: ");
    scanf("%d", &id);

    fseek(file, (id - 1) * sizeof(Employee), SEEK_SET);
    if (fread(&e, sizeof(Employee), 1, file)) {
        printf("Employee ID: %d\nName: %s\nSalary: %.2f\n", e.id, e.name, e.salary);
    } else {
        printf("Employee not found!\n");
    }
}

int main() {
    FILE *file = fopen("employees.dat", "rb+");
    if (!file) file = fopen("employees.dat", "wb+");
    int choice;

    while (1) {
        printf("\n1. Add Employee\n2. Display Employee\n3. Exit\nEnter choice: ");
        scanf("%d", &choice);
        if (choice == 1) addEmployee(file);
        else if (choice == 2) displayEmployee(file);
        else break;
    }

    fclose(file);
    return 0;
}
