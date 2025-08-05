#include "cart.h"
#include <iostream>
#include <iomanip>
using namespace std;

// Default constructor
Cart::Cart() : courses(nullptr), schedules(nullptr), totalCourses(0), totalCost(0.0) {}

// Destructor
Cart::~Cart() {
    clear();
}

// Adds a course to the cart, resizing arrays as needed
// NOTE: This is a bit clunky, but we can't use vectors for this project.
void Cart::addCourse(const Course& course) {
    Course* newArr = new Course[totalCourses + 1];
    string* newSched = new string[totalCourses + 1];
    for (int i = 0; i < totalCourses; ++i) {
        newArr[i] = courses[i];
        newSched[i] = schedules[i];
    }
    newArr[totalCourses] = course;
    newSched[totalCourses] = course.getSchedule();
    if (courses) delete[] courses;
    if (schedules) delete[] schedules;
    courses = newArr;
    schedules = newSched;
    totalCost += course.getPrice() * 1.13; // 13% tax, because that's the law!
    ++totalCourses;
}

// Clears the cart and frees memory
void Cart::clear() {
    if (courses) delete[] courses;
    if (schedules) delete[] schedules;
    courses = nullptr;
    schedules = nullptr;
    totalCourses = 0;
    totalCost = 0.0;
}

int Cart::getTotalCourses() const { return totalCourses; }
double Cart::getTotalCost() const { return totalCost; }
Course* Cart::getCourses() const { return courses; }

// Lists all courses in the cart
void Cart::listCourses() const {
    if (totalCourses == 0) {
        cout << "Your cart is empty. Looks like you need to shop!" << endl;
        return;
    }
    cout << "Here are the courses in your cart:" << endl;
    cout << "----------------------------------" << endl;
    for (int i = 0; i < totalCourses; ++i) {
        cout << i+1 << ". " << courses[i].getCourseNumber() << " | " << courses[i].getCourseName() << " | " << schedules[i] << " | $" << fixed << setprecision(2) << courses[i].getPrice() << endl;
    }
}

bool Cart::isEmpty() const { return totalCourses == 0; }

// TODO: Maybe add a function to remove courses from the cart?
