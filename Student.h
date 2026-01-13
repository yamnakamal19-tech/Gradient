#ifndef STUDENT_H
#define STUDENT_H

#include "User.h"

class Student : public User
{
private:
string assignment;
    float similarity;
    float marks;

public:
    Student(int i, string n) : User(n, i), similarity(0), marks(0) {}

    void setAssignment(const string& a) { assignment = a; }
string getAssignment() const { return assignment; }

    void setResult(float s, float m)
    {
        similarity = s;
        marks = m;
    }

    float getSimilarity() const { return similarity; }
    float getMarks() const { return marks; }
};

#endif
