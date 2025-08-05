// cart.h - Defines the Cart class representing a student's shopping cart for courses
#ifndef CART_H
#define CART_H

#include "course.h"
using namespace std;

class Cart {
private:
    // Dynamic array of courses in the cart
    Course* courses;
    // Dynamic array of schedules for each course
    string* schedules;
    // Number of courses in the cart
    int totalCourses;
    // Total cost of all courses in the cart
    double totalCost;
public:
    // Default constructor
    Cart();
    // Destructor to clean up dynamic memory
    ~Cart();
    // Adds a course to the cart
    void addCourse(const Course& course);
    // Clears the cart and frees memory
    void clear();
    // Returns the number of courses in the cart
    int getTotalCourses() const;
    // Returns the total cost of the cart
    double getTotalCost() const;
    // Returns pointer to the array of courses
    Course* getCourses() const;
    // Lists all courses in the cart
    void listCourses() const;
    // Checks if the cart is empty
    bool isEmpty() const;
};

#endif // CART_H
