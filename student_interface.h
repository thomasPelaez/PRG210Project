// student_interface.h - Defines the StudentInterface class for student user actions
#ifndef STUDENT_INTERFACE_H
#define STUDENT_INTERFACE_H

#include "interface.h"
#include "department.h"
#include "cart.h"

class StudentInterface : public Interface {
private:
    // Shopping cart for the student
    Cart cart;
public:
    // Shows the student menu and handles student actions
    void showMenu() override;
};

#endif // STUDENT_INTERFACE_H
