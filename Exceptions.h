#ifndef EXCEPTIONS_H
#define EXCEPTIONS_H

#include <iostream>

class StudentException {
public:
    virtual void displayError() const {
        std::cout << "An unspecified student error occurred." << std::endl;
    }
};

class InvalidRollNumber : public StudentException {
public:
    void displayError() const override {
        std::cout << "Error: Invalid Roll Number format. Must be like '23CS10001'." << std::endl;
    }
};

class InvalidName : public StudentException {
public:
    void displayError() const override {
        std::cout << "Error: Name contains invalid characters or format." << std::endl;
    }
};

class BufferOverflow : public StudentException {
public:
    void displayError() const override {
        std::cout << "Error: Input exceeds maximum allowed length (Buffer Overflow)." << std::endl;
    }
};

#endif // EXCEPTIONS_H