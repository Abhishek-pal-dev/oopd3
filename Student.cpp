#include "Student.h"
#include <iostream>

// --- BTechStudent Implementation ---

void BTechStudent::displayDetails() const {
    std::cout << "Level: BTech | Roll: " << rollNumber << " | Branch: " << branch
              << " | Name: " << name << " | Total Marks: " << getTotalMarks()
              << " | Grade: " << getGrade() << std::endl;
}

char BTechStudent::getGrade() const {
    float total = getTotalMarks();
    if (total > 90) return 'A';
    if (total > 80) return 'B';
    if (total > 70) return 'C';
    return 'D';
}

// ADDED: Implementation to write BTechStudent data to a file stream
void BTechStudent::writeToFile(std::ostream& os) const {
    // '1' is the type identifier for BTechStudent
    os << "1," << rollNumber << "," << name << "," << branch;
    for (int i = 0; i < numComponents; ++i) {
        os << "," << marks[i];
    }
}


// --- MTechStudent Implementation ---

void MTechStudent::displayDetails() const {
    std::cout << "Level: MTech | Roll: " << rollNumber << " | Branch: " << branch
              << " | Name: " << name << " | Total Marks: " << getTotalMarks()
              << " | Grade: " << getGrade() << std::endl;
}

char MTechStudent::getGrade() const {
    float total = getTotalMarks();
    if (total > 92) return 'A';
    if (total > 85) return 'B';
    if (total > 75) return 'C';
    return 'D';
}

// ADDED: Implementation to write MTechStudent data to a file stream
void MTechStudent::writeToFile(std::ostream& os) const {
    // '2' is the type identifier for MTechStudent
    os << "2," << rollNumber << "," << name << "," << branch;
    for (int i = 0; i < numComponents; ++i) {
        os << "," << marks[i];
    }
}


// --- PhDStudent Implementation ---

void PhDStudent::displayDetails() const {
    std::cout << "Level: PhD | Roll: " << rollNumber << " | Branch: " << branch
              << " | Name: " << name << " | Total Marks: " << getTotalMarks()
              << " | Grade: " << getGrade() << std::endl;
}

char PhDStudent::getGrade() const {
    float total = getTotalMarks();
    // PhD grading: Satisfactory or Unsatisfactory
    return (total >= 80) ? 'S' : 'U';
}

// ADDED: Implementation to write PhDStudent data to a file stream
void PhDStudent::writeToFile(std::ostream& os) const {
    // '3' is the type identifier for PhDStudent
    os << "3," << rollNumber << "," << name << "," << branch;
    for (int i = 0; i < numComponents; ++i) {
        os << "," << marks[i];
    }
}
