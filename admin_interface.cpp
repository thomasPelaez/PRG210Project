#include "admin_interface.h"
#include <iostream>
#include <iomanip>
using namespace std;

// External references to global department data
extern Department* StoreDepartments; 
extern int TotalDepartments;
extern const char* csvFile;

// Shows the admin menu and handles all admin actions
void AdminInterface::showMenu() {
    while (true) {
        // Display the main admin menu
        cout << "\nWelcome to the Admin Dashboard!" << endl;
        cout << "--------------------------------" << endl;
        cout << "1. List Departments" << endl;
        cout << "2. Add Department" << endl;
        cout << "3. Add Course to Department" << endl;
        cout << "4. Save Changes to CSV" << endl;
        cout << "5. Exit" << endl;
        // Get validated menu choice from the user
        int choice = getValidatedInput(1, 5, "Enter your choice [1, 2, 3, 4, 5]: "); 
        if (choice == 1) {
            // List all departments
            if (TotalDepartments == 0) {
                showError("No departments available. Please add a department first.");
            } else {
                cout << "\nDepartments in the system:" << endl;
                cout << "---------------------------" << endl;
                for (int i = 0; i < TotalDepartments; ++i)
                    cout << i+1 << ". " << StoreDepartments[i].getName() << endl;
            }
        } else if (choice == 2) {
            // Add a new department
            char deptName[100];
            while (true) {
                cout << "Enter department name: ";
                cin.getline(deptName, 100);
				// error handling for empty department name
                if (strlen(deptName) == 0) {
                    showError("Department name cannot be empty.");
                } else {
                    break;
                }
            }
            // Resize department array and add new department
            Department* newArr = new Department[TotalDepartments + 1];
            for (int i = 0; i < TotalDepartments; ++i) newArr[i] = StoreDepartments[i];
			newArr[TotalDepartments] = Department(deptName); // Create new department with the given name
			if (StoreDepartments) delete[] StoreDepartments; // Free old array memory if it exists
			StoreDepartments = newArr; // Assign new array to global variable
            ++TotalDepartments;
			cout << "Department '" << deptName << "' added successfully!" << endl; // Notify admin of success
        } else if (choice == 3) {
            // Add a course to a department
            if (TotalDepartments == 0) {
                showError("No departments available. Please add a department first.");
                continue;
            }
            cout << "\nSelect a department to add a course:" << endl;
            for (int i = 0; i < TotalDepartments; ++i) 
                cout << i+1 << ". " << StoreDepartments[i].getName() << endl;
            int deptIdx = getValidatedInput(0, TotalDepartments, "Enter department number [0 to go back]: "); 
            if (deptIdx == 0) continue; // Go back to admin menu
            --deptIdx; 
            string courseNumber, courseName, schedule; 
            double price;
            // Get and validate course details
            while (true) {
                cout << "Enter course number: ";
                getline(cin, courseNumber);
				// Error handling for empty course number
                if (courseNumber.empty()) {
                    showError("Course number cannot be empty.");
                } else {
                    break;
                }
            }
            while (true) {
                cout << "Enter course name: ";
                getline(cin, courseName);
				// Error handling for empty course name
                if (courseName.empty()) {
                    showError("Course name cannot be empty.");
                } else {
                    break;
                }
            }
            while (true) {
                cout << "Enter course schedule (M/W, T/R, W/F): ";
                getline(cin, schedule);
                if (schedule != "M/W" && schedule != "T/R" && schedule != "W/F") {
                    showError("Invalid schedule. Please enter M/W, T/R, or W/F.");
                } else {
                    break;
                }
            }
            while (true) {
                cout << "Enter course price: $";
                cin >> price;
                if (cin.fail() || price <= 0) {
                    cin.clear(); cin.ignore(10000, '\n');
                    showError("Invalid price. Please enter a positive number.");
                } else {
                    cin.ignore(10000, '\n');
                    break;
                }
            }
            // Add the new course to the selected department
            StoreDepartments[deptIdx].addCourse(Course(courseNumber, courseName, schedule, price)); 
            cout << "Course '" << courseName << "' (" << courseNumber << ") added to department '" << StoreDepartments[deptIdx].getName() << "' successfully!" << endl;
        } else if (choice == 4) {
            // Save all departments and courses to CSV file
            FILE* file = nullptr; 
            if (fopen_s(&file, csvFile, "w") != 0 || !file) { showError("Failed to open CSV file for saving. Please check the file path."); continue; }
            fprintf(file, "%d\n", TotalDepartments);
            for (int i = 0; i < TotalDepartments; ++i)
                StoreDepartments[i].saveToCSV(file);
            fclose(file);
            cout << "All changes have been saved to CSV successfully!" << endl;
        } else if (choice == 5) {
            // Exit admin menu and return to main menu
            cout << "\nExiting Admin Dashboard. Have a great day!" << endl;
            break;
        }
    }
    // TODO: Add feature to remove departments?
}
