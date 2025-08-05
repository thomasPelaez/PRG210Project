#ifndef ADMIN_INTERFACE_H
#define ADMIN_INTERFACE_H

#include "interface.h"
#include "department.h"

// Handdles all department and course admininstrations commands
class AdminInterface : public Interface {
public:
    // Shows the admin menu and handles admin actions
    void showMenu() override;
};

#endif // ADMIN_INTERFACE_H
