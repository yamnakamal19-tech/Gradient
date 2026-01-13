#ifndef USER_H
#define USER_H

#include <iostream>
#include <string>
using namespace std;

class User {
protected:
    string name;
    int id;

public:
    User(string n, int i) : name(n), id(i) {}

    virtual void displayRole() {
        cout << "User" << endl;
    }

    void displayUser() {
        cout << "User Name: " << name << endl;
        cout << "User ID  : " << id << endl;
    }

    string getName() const { return name; }
    int getId() const { return id; }
};

#endif
