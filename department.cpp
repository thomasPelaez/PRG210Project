#include "department.h"
#include <cstdio>
#include <cstring>
#include <iostream> // Include iostream for console output

// Default constructor - initializes department with no courses and empty name
Department::Department() : courses(nullptr), totalCourses(0) {
    name[0] = '\0';
}

// Parameterized constructor - initializes department with given name
Department::Department(const char* deptName) : courses(nullptr), totalCourses(0) {
    strncpy_s(name, sizeof(name), deptName, _TRUNCATE);
}

// Destructor - cleans up dynamic array of courses
Department::~Department() {
    if (courses) delete[] courses;
}

// Returns the department name
const char* Department::getName() const {
    return name;
}

// Returns the number of courses in the department
int Department::getTotalCourses() const {
    return totalCourses;
}

// Returns pointer to the array of courses
Course* Department::getCourses() const {
    return courses;
}

// Adds a course to the department, resizing the array as needed
// Copies old courses, adds the new one, deletes old array
void Department::addCourse(const Course& course) {
    Course* newArr = new Course[totalCourses + 1];
    for (int i = 0; i < totalCourses; ++i) newArr[i] = courses[i];
    newArr[totalCourses] = course;
    if (courses) delete[] courses;
    courses = newArr;
    ++totalCourses;
    // NOTE: I print a message here for debugging, but you can comment it out if you want less console spam.
    std::cout << "Course '" << course.getCourseName() << "' (" << course.getCourseNumber() << ") added to department '" << name << "'." << std::endl;
}

// Sets the department name
void Department::setName(const char* deptName) {
    strncpy_s(name, sizeof(name), deptName, _TRUNCATE);
}

// Loads department data from a CSV line (courses loaded separately)
void Department::loadFromCSV(const char* csvLine, int numCourses) {
    setName(csvLine);
    // Courses should be loaded separately
}

// Saves department and its courses to a CSV file
// Writes department name and number of courses, then each course
void Department::saveToCSV(FILE* file) const {
    fprintf(file, "%s, %d\n", name, totalCourses);
    for (int i = 0; i < totalCourses; ++i) {
        const Course& c = courses[i];
        fprintf(file, "%s, %s, %s, %.2f\n", c.getCourseNumber().c_str(), c.getCourseName().c_str(), c.getSchedule().c_str(), c.getPrice());
    }
}
// TODO: Add feature to remove courses from a department?
