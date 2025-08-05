#pragma once
#ifndef COURSE_H
#define COURSE_H
#include <string>
using namespace std;

// Course.h - Defines the Course class representing a single course in the system
class Course {
private:
	// Course number (e.g., CS101)
	string courseNumber;
	// Course name (e.g., Intro to Programming)
	string courseName;
	// Schedule (e.g., M/W, T/R, W/F)
	string schedule;
	// Price of the course
	double price;

public:
	// Default constructor
	Course();
	// Parameterized constructor
	Course(const string& courseNumber, const string& courseName, const string& schedule, double price);

	// Getters for course properties
	string getCourseNumber() const;
	string getCourseName() const;
	string getSchedule() const;
	double getPrice() const;

	// Setters for course properties
	void setCourseNumber(const string& courseNumber);
	void setCourseName(const string& courseName);
	void setSchedule(const string& schedule);
	void setPrice(double price);

	// Parses a CSV line and returns a Course object
	static Course parseCSV(const string& csvLine);
	// Serializes the course to a CSV string
	string toCSV() const;
};

#endif // COURSE_H