#ifndef ACTIVE_OBJECT_INC_CTHREAD_EXCETPION_H
#define ACTIVE_OBJECT_INC_CTHREAD_EXCETPION_H
#include <exception>
#include <string>

class CThreadException : public std::exception {
public:
    CThreadException(const std::string& details) : details(details) {} // Store details

    const char* what() const noexcept override {
        return details.c_str(); // Return stored details
    }

private:
    std::string details; // Store detailed error message
};

#endif 
