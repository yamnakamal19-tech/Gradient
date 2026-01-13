#ifndef TEACHER_H
#define TEACHER_H

#include "User.h"

class Teacher : public User
{
private:
    string subject;

public:
    Teacher(string n, int i, string sub) : User(n, i), subject(sub) {}

    void displayRole() override
    {
        cout << "Role     : Teacher\n";
        cout << "Subject  : " << subject << endl;
    }
};

#endif
