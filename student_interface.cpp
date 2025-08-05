// student_interface.cpp - Implements the student menu and all student actions
#include "student_interface.h"
#include <iostream>
#include <iomanip>
using namespace std;

// External references to global department data
extern Department* StoreDepartments;
extern int TotalDepartments;

// NOTE: This menu is a bit nested, but it works for now. Could refactor later.
// Shows the student menu and handles all student actions
// This function is the main loop for the student interface
void StudentInterface::showMenu() {
    while (true) {
        // Display the main student menu
        cout << "\nWelcome to the Student Portal!" << endl;
        cout << "--------------------------------" << endl;
        cout << "1. Show Cart" << endl;
        cout << "2. Browse Departments" << endl;
        cout << "3. Exit" << endl;
        // Get validated menu choice from the user
        int choice = getValidatedInput(1, 3, "Enter your choice [1, 2, 3]: ");
        if (choice == 1) {
            // Show cart menu (nested loop)
            while (true) {
                cout << "\nYour Shopping Cart:" << endl;
                cout << "--------------------" << endl;
                cout << "1. List Courses" << endl;
                cout << "2. Checkout" << endl;
                cout << "3. Return to Main Menu" << endl;
                int cartChoice = getValidatedInput(1, 3, "Enter your choice [1, 2, 3]: ");
                if (cartChoice == 1) {
                    // List all courses currently in the cart
                    if (cart.isEmpty()) {
                        showError("Your cart is empty. Looks like you need to shop!");
                    } else {
                        cout << fixed << setprecision(2);
                        cart.listCourses();
                        cout << "Total (including 13% tax): $" << cart.getTotalCost() << endl;
                    }
                } else if (cartChoice == 2) {
                    // Checkout: if cart is not empty, thank user and clear cart
                    if (!cart.isEmpty()) {
                        cout << fixed << setprecision(2);
                        cout << "Thank you for your purchase!" << endl;
                        cout << "You have bought " << cart.getTotalCourses() << " course(s) for a total of $" << cart.getTotalCost() << "." << endl;
                        cart.clear();
                        break; // Return to student menu after checkout
                    } else {
                        showError("No courses in the cart.");
                    }
                } else if (cartChoice == 3) {
                    // Return to student menu
                    break;
                }
            }
        } else if (choice == 2) {
            // Browse departments and courses (nested loop)
            while (true) {
                // List all departments
                cout << "\nDepartments Available:" << endl;
                cout << "----------------------" << endl;
                for (int i = 0; i < TotalDepartments; ++i)
                    cout << i+1 << ". " << StoreDepartments[i].getName() << endl;
                // Show options for browsing
                cout << "\nOptions:" << endl;
                cout << "1. List Courses of a Department" << endl;
                cout << "2. Go Back to Main Menu" << endl;
                cout << endl;
                int browseChoice = getValidatedInput(1, 2, "Enter your choice [1, 2]: ");
                if (browseChoice == 1) {
                    // List courses in selected department
                    cout << endl;
                    int deptIdx = getValidatedInput(0, TotalDepartments, "Enter department number [0 to go back]: ");
                    if (deptIdx == 0) continue; // Go back to department list
                    --deptIdx;
                    cout << "\nCourses in " << StoreDepartments[deptIdx].getName() << ":" << endl;
                    cout << "----------------------------------------" << endl;
                    Course* courses = StoreDepartments[deptIdx].getCourses();
                    int totalCourses = StoreDepartments[deptIdx].getTotalCourses();
                    // List all courses in the selected department
                    if (totalCourses == 0) {
                        showError("No courses available in this department.");
                    } else {
						cout << fixed << setprecision(2); // Set precision for price display
                        for (int i = 0; i < totalCourses; ++i)
                            cout << i+1 << ". " << courses[i].getCourseNumber() << ", " << courses[i].getCourseName() << ", " << courses[i].getSchedule() << ", $" << courses[i].getPrice() << endl;
                    }
                    cout << endl;
                    // Options for adding a course to cart or going back
                    while (true) {
                        cout << "Options:" << endl;
                        cout << "1. Add a Course to Cart" << endl;
                        cout << "2. Go Back to Browse Departments Menu" << endl;
                        cout << endl;
                        int courseChoice = getValidatedInput(1, 2, "Enter your choice [1, 2]: ");
                        if (courseChoice == 1) {
                            // Add selected course to cart
                            cout << endl;
                            int courseIdx = getValidatedInput(0, totalCourses, "Enter course number to buy [0 to go back]: ");
                            if (courseIdx == 0) break; // Go back to course list
                            --courseIdx;
                            cart.addCourse(courses[courseIdx]);
                            cout << "\nCourse added to cart: " << courses[courseIdx].getCourseName() << " (" << courses[courseIdx].getCourseNumber() << ")" << endl;
                        } else if (courseChoice == 2) {
                            // Return to department courses menu
                            break;
                        }
                    }
                } else if (browseChoice == 2) {
                    // Return to student menu
                    break;
                }
            }
        } else if (choice == 3) {
            // Exit student menu and return to main menu
            cout << "\nThank you for using the Student Portal. Goodbye!" << endl;
            break;
        }
    }
    // TODO: Add feature to let students remove courses from their cart?
}
