#include "interface.h"
#include <iostream>

// NOTE: This function is used everywhere for input validation. Could be improved with regex for more complex input.
int Interface::getValidatedInput(int min, int max, const char* prompt) { 
    int choice; 
    while (true) {
        std::cout << prompt;
        std::cin >> choice;
        if (std::cin.fail() || choice < min || choice > max) {
            std::cin.clear();
            std::cin.ignore(10000, '\n');
            showError("Oops! That wasn't a valid option. Please try again.");
        } else {
            std::cin.ignore(10000, '\n');
            return choice;
        }
    }
}

// NOTE: I like to prefix errors with [!] so they stand out in the console.
void Interface::showError(const char* msg) {
    std::cout << "[!] " << msg << std::endl;
}
// TODO: Add more input validation for strings if time permits.
