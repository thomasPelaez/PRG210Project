// interface.h - Abstract base class for user interfaces (admin/student)
#ifndef INTERFACE_H
#define INTERFACE_H

class Interface {
public:
    // Pure virtual method to show the menu for the interface
    virtual void showMenu() = 0;
    // Virtual destructor for proper cleanup
    virtual ~Interface() {}
protected:
    // Gets validated integer input from the user within a range
    int getValidatedInput(int min, int max, const char* prompt);
    // Displays an error message to the user
    void showError(const char* msg);
};

#endif // INTERFACE_H
