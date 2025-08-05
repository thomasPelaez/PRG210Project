#include "course.h"
#include <string>
#include <iostream>

using namespace std;

// Default constructor - initializes course properties to default values
Course::Course() : courseNumber(""), courseName(""), schedule(""), price(0.0) {}

// Parameterized constructor - initializes course with given values
Course::Course(const string& courseNumber, const string& courseName, const string& schedule, double price)
	: courseNumber(courseNumber), courseName(courseName), schedule(schedule), price(price) {
}

string Course::getCourseNumber() const { return courseNumber; }
string Course::getCourseName() const { return courseName; }
string Course::getSchedule() const { return schedule; }
double Course::getPrice() const { return price; }
void Course::setCourseNumber(const string& cn) { courseNumber = cn; }
void Course::setCourseName(const string& n) { courseName = n; }
void Course::setSchedule(const string& s) { schedule = s; }
void Course::setPrice(double p) { price = p; }

// Parses a CSV line and returns a Course object
// Splits the line into fields, trims spaces, and converts price
Course Course::parseCSV(const string& csvLine) {
    string fields[4];
    size_t start = 0, end = 0;
    int fieldIdx = 0;
    // NOTE: This parsing is pretty basic, but works for our format.
    // Split the CSV line by commas into fields
    while (fieldIdx < 3) {
        end = csvLine.find(',', start);
        if (end == string::npos) break;
        fields[fieldIdx++] = csvLine.substr(start, end - start);
        start = end + 1;
    }
    // Last field (price)
    fields[3] = csvLine.substr(start);
    // Remove leading/trailing spaces from each field
    for (int i = 0; i < 4; ++i) {
        size_t first = fields[i].find_first_not_of(' ');
        size_t last = fields[i].find_last_not_of(' ');
        if (first != string::npos && last != string::npos)
            fields[i] = fields[i].substr(first, last - first + 1);
    }
    double price = 0.0;
    try {
        // Convert the price field to a double
        price = stod(fields[3]);
    } catch (...) {
        price = 0.0;
        std::cout << "[!] Warning: Invalid price found in CSV. Defaulting to $0.00." << std::endl;
    }
    // Return a Course object constructed from the fields
    return Course(fields[0], fields[1], fields[2], price);
}

// Serializes the course to a CSV string
string Course::toCSV() const {
    // NOTE: This could be improved to handle commas in fields, but for now it's fine.
    return courseNumber + ", " + courseName + ", " + schedule + ", " + to_string(price);
}
// TODO: Add a function to pretty-print course info?