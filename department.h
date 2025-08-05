// department.h - Defines the Department class representing a department containing courses
#ifndef DEPARTMENT_H
#define DEPARTMENT_H

#include "course.h"
#include <cstring>

class Department {
private:
    // Name of the department
    char name[100];
    // Dynamic array of courses in the department
    Course* courses;
    // Number of courses in the department
    int totalCourses;
public:
    // Default constructor
    Department();
    // Parameterized constructor
    Department(const char* deptName);
    // Destructor to clean up dynamic memory
    ~Department();
    // Returns the department name
    const char* getName() const;
    // Returns the number of courses in the department
    int getTotalCourses() const;
    // Returns pointer to the array of courses
    Course* getCourses() const;
    // Adds a course to the department
    void addCourse(const Course& course);
    // Sets the department name
    void setName(const char* deptName);
    // Loads department data from a CSV line
    void loadFromCSV(const char* csvLine, int numCourses);
    // Saves department and its courses to a CSV file
    void saveToCSV(FILE* file) const;
};

#endif // DEPARTMENT_H
