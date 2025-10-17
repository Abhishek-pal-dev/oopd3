#ifndef STUDENT_H
#define STUDENT_H

#include "helpers.h"
#include <iostream> // ADDED for std::ostream

// Base class for all students
class Student {
protected:
    char rollNumber[15];
    char name[50]; 
    char branch[4]; 
    float marks[5];
    int numComponents;

public: 
    // student constructor 
    Student() : numComponents(5) {
        rollNumber[0] = '\0';
        name[0] = '\0';
        branch[0] = '\0';
        for (int i = 0; i < 5; ++i) marks[i] = 0;
    }

    Student(const char* roll, const char* s_name, const char* s_branch) : numComponents(5) {
        custom_strcpy(rollNumber, roll);
        custom_strcpy(name, s_name);
        custom_strcpy(branch, s_branch);
        for (int i = 0; i < 5; ++i) marks[i] = 0;
    }

    virtual ~Student() {} // Virtual destructor for proper cleanup

    const char* getRollNumber() const { return rollNumber; }
    const char* getName() const { return name; }
    const char* getBranch() const { return branch; } 

    float getTotalMarks() const {
        float total = 0;
        for (int i = 0; i < numComponents; ++i) {
            total += marks[i];
        }
        return total;
    }

    void setMarks(const float* newMarks) {
        for (int i = 0; i < numComponents; ++i) {
            marks[i] = newMarks[i];
        }
    }

    // Pure virtual functions for polymorphism
    virtual void displayDetails() const = 0;
    virtual char getGrade() const = 0;
    virtual void writeToFile(std::ostream& os) const = 0; // ADDED: Pure virtual function for file writing
};

// Derived classes
class BTechStudent : public Student {
public:
    BTechStudent(const char* roll, const char* s_name, const char* s_branch) : Student(roll, s_name, s_branch) {}
    void displayDetails() const override;
    char getGrade() const override;
    void writeToFile(std::ostream& os) const override; // ADDED: Override for file writing
};

class MTechStudent : public Student {
public:
    MTechStudent(const char* roll, const char* s_name, const char* s_branch) : Student(roll, s_name, s_branch) {}
    void displayDetails() const override;
    char getGrade() const override;
    void writeToFile(std::ostream& os) const override; // ADDED: Override for file writing
};

class PhDStudent : public Student {
public:
    PhDStudent(const char* roll, const char* s_name, const char* s_branch) : Student(roll, s_name, s_branch) {}
    void displayDetails() const override;
    char getGrade() const override;
    void writeToFile(std::ostream& os) const override; // ADDED: Override for file writing
};

#endif
