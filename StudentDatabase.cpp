#include "StudentDatabase.h"
#include "helpers.h"
#include <iostream>
#include <fstream>   // ADDED for file input/output
#include <sstream>   // ADDED for string stream parsing
#include <string>    // ADDED for std::string and related functions

// Helper functions for sorting (Quicksort)
int partition(Student** arr, int low, int high, int criterion) {
    Student* pivot = arr[high];
    int i = low - 1;
    for (int j = low; j <= high - 1; ++j) {
        bool shouldSwap = false;
        if (criterion == 0) { // Sort by Roll Number
            if (custom_strcmp(arr[j]->getRollNumber(), pivot->getRollNumber()) < 0) {
                shouldSwap = true;
            }
        } else if (criterion == 1) { // Sort by Marks Descending
            if (arr[j]->getTotalMarks() > pivot->getTotalMarks()) {
                shouldSwap = true;
            }
        }
        if (shouldSwap) {
            ++i;
            Student* temp = arr[i];
            arr[i] = arr[j];
            arr[j] = temp;
        }
    }
    Student* temp = arr[i + 1];
    arr[i + 1] = arr[high];
    arr[high] = temp;
    return (i + 1);
}

void quickSort(Student** arr, int low, int high, int criterion) {
    if (low < high) {
        int pi = partition(arr, low, high, criterion);
        quickSort(arr, low, pi - 1, criterion);
        quickSort(arr, pi + 1, high, criterion);
    }
}

// --- StudentDatabase Implementation ---

// MODIFIED: Constructor now takes filename, initializes it, and loads data
StudentDatabase::StudentDatabase(const std::string& dbFile) : capacity(10), count(0), filename(dbFile) {
    students = new Student*[capacity];
    nameTrie = new Trie();
    loadFromFile(); // Load existing data from the file on startup
}

StudentDatabase::~StudentDatabase() {
    for (int i = 0; i < count; ++i) {
        delete students[i];
    }
    delete[] students;
    delete nameTrie;
}

void StudentDatabase::resize() {
    capacity *= 2;
    Student** newStudents = new Student*[capacity];
    for (int i = 0; i < count; ++i) {
        newStudents[i] = students[i];
    }
    delete[] students;
    students = newStudents;
}

// MODIFIED: Automatically save after adding a new student
void StudentDatabase::operator+=(Student* newStudent) {
    if (count == capacity) resize();
    students[count++] = newStudent;
    nameTrie->insert(newStudent->getName(), newStudent);
    saveDatabase(); // Save the entire database after adding a new student
}

Student* StudentDatabase::operator()(const char* rollNumber) {
    for (int i = 0; i < count; ++i) {
        if (custom_strcmp(students[i]->getRollNumber(), rollNumber) == 0) {
            return students[i];
        }
    }
    return nullptr;
}

// ADDED: Implementation to save the entire database to a file
void StudentDatabase::saveDatabase() const {
    std::ofstream outFile(filename);
    if (!outFile.is_open()) {
        std::cerr << "Error: Could not open database file for writing: " << filename << std::endl;
        return;
    }
    for (int i = 0; i < count; ++i) {
        students[i]->writeToFile(outFile);
        outFile << std::endl;
    }
}

// ADDED: Implementation to load data from a file on startup
void StudentDatabase::loadFromFile() {
    std::ifstream inFile(filename);
    if (!inFile.is_open()) {
        // File doesn't exist yet, which is normal on the first run.
        return; 
    }

    std::string line;
    while (std::getline(inFile, line)) {
        if (line.empty()) continue; // Skip empty lines

        std::stringstream ss(line);
        std::string token;

        int type;
        char roll[15], name[50], branch[4];
        float marks[5];

        // Parse type
        if (!std::getline(ss, token, ',')) continue;
        try {
            type = std::stoi(token);
        } catch (...) { continue; /* Malformed line */ }

        // Parse roll, name, branch
        if (!std::getline(ss, token, ',')) continue;
        custom_strcpy(roll, token.c_str());
        if (!std::getline(ss, token, ',')) continue;
        custom_strcpy(name, token.c_str());
        if (!std::getline(ss, token, ',')) continue;
        custom_strcpy(branch, token.c_str());

        // Parse marks
        bool parse_ok = true;
        for(int i = 0; i < 5; ++i) {
            if (!std::getline(ss, token, ',')) {
                parse_ok = false;
                break;
            }
            try {
                marks[i] = std::stof(token);
            } catch (...) {
                parse_ok = false;
                break;
            }
        }
        if (!parse_ok) continue;

        Student* newStudent = nullptr;
        if (type == 1) newStudent = new BTechStudent(roll, name, branch);
        else if (type == 2) newStudent = new MTechStudent(roll, name, branch);
        else if (type == 3) newStudent = new PhDStudent(roll, name, branch);

        if (newStudent) {
            newStudent->setMarks(marks);
            // Add student without calling saveDatabase again to avoid recursion
            if (count == capacity) resize();
            students[count++] = newStudent;
            nameTrie->insert(newStudent->getName(), newStudent);
        }
    }
}

void StudentDatabase::displayAll() const {
    for (int i = 0; i < count; ++i) {
        students[i]->displayDetails();
    }
}

void StudentDatabase::sortByRollNumber() {
    quickSort(students, 0, count - 1, 0);
}

void StudentDatabase::sortByMarks() {
    quickSort(students, 0, count - 1, 1);
}

void StudentDatabase::sortByName() {
    nameTrie->displaySorted();
}
