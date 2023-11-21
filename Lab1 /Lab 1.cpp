#include <stdio.h>
#include <string.h>

// Define the Employee struct
typedef struct {
    char name[100];
    float taxRate;
    float (*calcSalary)(void*);
} Employee;

// Define the SalariedEmployee struct that inherits from the Employee struct
typedef struct {
    Employee employee;
    float salary;
} SalariedEmployee;

// Define the HourlyEmployee struct that inherits from the Employee struct
typedef struct {
    Employee employee;
    float hours;
    float hourlyRate;
} HourlyEmployee;

// Define the CommissionedEmployee struct that inherits from the Employee struct
typedef struct {
    Employee employee;
    float sales;
    float commissionRate;
} CommissionedEmployee;

// Define the calcSalary_SalariedEmployee function
float calcSalary_SalariedEmployee(void* var) {
    SalariedEmployee* e = (SalariedEmployee*)var;
    return e->salary * (1 - e->employee.taxRate);
}

// Define the calcSalary_HourlyEmployee function
float calcSalary_HourlyEmployee(void* var) {
    HourlyEmployee* e = (HourlyEmployee*)var;
    return e->hours * e->hourlyRate * (1 - e->employee.taxRate);
}

// Define the calcSalary_CommissionedEmployee function
float calcSalary_CommissionedEmployee(void* var) {
    CommissionedEmployee* e = (CommissionedEmployee*)var;
    return e->sales * e->commissionRate * (1 - e->employee.taxRate);
}

int main() {
    int i;
    // Create a SalariedEmployee object
    SalariedEmployee salariedEmployee = {
      { "Talha", 0.1, calcSalary_SalariedEmployee },
      5000
    };

    // Create an HourlyEmployee object
    HourlyEmployee hourlyEmployee = {
      { "Ali", 0.15, calcSalary_HourlyEmployee },
      40,
      20
    };

    // Create a CommissionedEmployee object
    CommissionedEmployee commissionedEmployee = {
      { "Asad", 0.2, calcSalary_CommissionedEmployee },
      10000,
      0.05
    };

    // Create an array of pointers to Employee objects
    Employee* employees[] = {
      (Employee*)&salariedEmployee,
      (Employee*)&hourlyEmployee,
      (Employee*)&commissionedEmployee
    };

    // Loop through the array of Employee objects
    for (i = 0; i < 3; i++) {
        Employee* e = employees[i];
        float salary = e->calcSalary(e);
        printf("Employee %s has a salary of Rs %.2f\n", e->name, salary);
    }

    return 0;
}
