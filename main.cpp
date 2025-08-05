#include "course.h"
#include "department.h"
#include "admin_interface.h"
#include "student_interface.h"
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

Department* StoreDepartments = nullptr;
int TotalDepartments = 0;
const char* csvFile = "courses.csv";

void loadCSV() {
    ifstream file(csvFile);
    if (!file.is_open()) return;
    string line;
    if (!getline(file, line)) return;
    TotalDepartments = stoi(line);
    StoreDepartments = new Department[TotalDepartments];
    for (int i = 0; i < TotalDepartments; ++i) {
        if (!getline(file, line)) break;
        size_t comma = line.find(',');
        string deptName = line.substr(0, comma);
        int numCourses = stoi(line.substr(comma+1));
        StoreDepartments[i].setName(deptName.c_str());
        for (int j = 0; j < numCourses; ++j) {
            if (!getline(file, line)) break;
            StoreDepartments[i].addCourse(Course::parseCSV(line));
        }
    }
    file.close();
}

int main() {
    loadCSV();
	Interface* ui = nullptr; // Pointer to the current interface (Student or Admin)
    while (true) {
        cout << "1. Student\n2. Admin\n3. Exit\nEnter your choice [1, 2, 3]: ";
        int choice; cin >> choice;
        if (cin.fail() || choice < 1 || choice > 3) {
            cin.clear(); cin.ignore(10000, '\n');
            continue;
        }
        cin.ignore(10000, '\n');
        if (choice == 1) { ui = new StudentInterface(); ui->showMenu(); delete ui; }
        else if (choice == 2) { ui = new AdminInterface(); ui->showMenu(); delete ui; }
        else break;
    }
    if (StoreDepartments) delete[] StoreDepartments;
    return 0;
}
