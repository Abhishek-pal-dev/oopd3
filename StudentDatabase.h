#ifndef STUDENTDATABASE_H
#define STUDENTDATABASE_H

#include "Student.h"
#include "Trie.h"
#include <string> // ADDED for std::string

class StudentDatabase {
private:
    Student** students;
    int capacity;
    int count;
    Trie* nameTrie;
    std::string filename; // ADDED: To store the database filename

    void resize();
    void loadFromFile(); // ADDED: Private method to load data on startup

public:
    // MODIFIED: Constructor now takes a filename to load/save data
    StudentDatabase(const std::string& dbFile); 
    ~StudentDatabase();

    void operator+=(Student* newStudent);
    Student* operator()(const char* rollNumber);

    void saveDatabase() const; // ADDED: Public method to save all data to the file

    void displayAll() const;
    void sortByName();
    void sortByRollNumber();
    void sortByMarks();
};

#endif // STUDENTDATABASE_H
