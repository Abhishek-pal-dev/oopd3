#include <iostream>
#include <cctype>
#include "StudentDatabase.h"
#include "Exceptions.h"

void displayMenu() {
    std::cout << "\n===== Student Management System =====\n";
    std::cout << "1. Add a new student\n";
    std::cout << "2. Modify a student's marks\n";
    std::cout << "3. Display all students\n";
    std::cout << "4. Display students sorted by Roll Number\n";
    std::cout << "5. Display students sorted by Total Marks\n";
    std::cout << "6. Display students sorted by Name (Trie)\n";
    std::cout << "7. Exit\n";
    std::cout << "=====================================\n";
    std::cout << "Enter your choice: ";
}

void modifyStudent(StudentDatabase& db) {
    char roll[15];
    std::cout << "Enter roll number of student to modify: ";
    std::cin >> roll;

    Student* student = db(roll); // Using overloaded operator()

    if (student) {
        float marks[5];
        std::cout << "Enter 5 new component marks for " << student->getName() << ": ";
        for (int i = 0; i < 5; ++i) std::cin >> marks[i];

        student->setMarks(marks);
        db.saveDatabase(); // Save changes to the file
        std::cout << "Marks updated successfully.\n";
    } else {
        std::cout << "Student with roll number " << roll << " not found.\n";
    }
}


void addStudent(StudentDatabase& db) {
    int type;
    char roll[15], name[50], branch[4];
    std::cout << "Enter student type (1: BTech, 2: MTech, 3: PhD): ";
    std::cin >> type;
    std::cout << "Enter Roll Number (e.g., 23CS10045): ";
    std::cin >> roll;
    std::cout << "Enter Branch (CSE/ECE): ";
    std::cin >> branch;
    std::cout << "Enter Full Name (e.g., John Doe): ";
    std::cin.ignore(); // Consume newline before getline
    char tempName[60];
    std::cin.getline(tempName, 60);

    if (custom_strlen(tempName) >= 50) throw BufferOverflow();
    custom_strcpy(name, tempName);

    // Roll Number Validation: NNXXNNNNN (N-digit, X-uppercase letters)
    if (!(isdigit(roll[0]) && isdigit(roll[1]) &&
          isupper(roll[2]) && isupper(roll[3]) &&
          isdigit(roll[4]) && isdigit(roll[5]) && isdigit(roll[6]) && isdigit(roll[7]) && isdigit(roll[8]))) {
        throw InvalidRollNumber();
    }

    // Name Validation: should contain at least one space, no digits or special chars except space
    bool hasSpace = false;
    for (int i = 0; name[i] != '\0'; ++i) {
        if (name[i] == ',') throw InvalidName(); // Prevent commas in names
        if (isdigit(name[i]) || (ispunct(name[i]) && name[i] != ' ')) throw InvalidName();
        if (name[i] == ' ') hasSpace = true;
    }
    if (!hasSpace) throw InvalidName();

    Student* newStudent = nullptr;
    if (type == 1) newStudent = new BTechStudent(roll, name, branch);
    else if (type == 2) newStudent = new MTechStudent(roll, name, branch);
    else if (type == 3) newStudent = new PhDStudent(roll, name, branch);
    else {
        std::cout << "Invalid student type.\n";
        return;
    }
    db += newStudent; // This now also saves the new student to the file
    std::cout << "Student added successfully!\n";
}

int main() {
    StudentDatabase db("students.dat"); // Create the database object with a filename
    int choice;

    do {
        displayMenu();
        std::cin >> choice;

        try {
            switch (choice) {
            case 1:
                addStudent(db);
                break;
            case 2:
                modifyStudent(db);
                break;
            case 3:
                db.displayAll();
                break;
            case 4:
                db.sortByRollNumber();
                db.displayAll();
                break;
            case 5:
                db.sortByMarks();
                db.displayAll();
                break;
            case 6:
                db.sortByName();
                // sortByName now just prints, so we don't call displayAll again.
                // If you want to see the unsorted list after, call db.displayAll() here.
                break;
            case 7:
                std::cout << "Exiting...\n";
                break;
            default:
                std::cout << "Invalid choice! Please try again.\n";
            }
        }
        catch (const StudentException& e) {
            e.displayError();
        }
    } while (choice != 7);

    return 0;
}