# C++ OOP Plagiarism Checker & Grading System

## 📌 Project Description
This project is a console-based plagiarism checker and grading system developed in **C++** using **Object-Oriented Programming (OOP)** principles.  
It allows a teacher to manage students, enter assignments, check plagiarism between assignments, assign marks based on similarity, and handle student queries.

---

## 🧩 Features
- User hierarchy using inheritance (`User`, `Teacher`, `Student`)
- Plagiarism detection using word-matching technique
- Automatic grading based on similarity percentage
- File handling to store and retrieve student results
- Menu-driven console interface
- Colored console output (Windows)

---

## 🛠️ Technologies Used
- C++
- Object-Oriented Programming (OOP)
- STL (`vector`, `string`)
- File Handling (`fstream`)
- Windows Console API

---

## ▶️ How to Run
1. Open the project in **VS Code**
2. Compile using a C++ compiler by writing `g++ main.cpp -o gradient`
3. Run the executable.

## Code

#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <windows.h>

using namespace std;

/* ===================== COLORS ===================== */

inline void setColor(int color)
{
    static HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, color);
}

inline void resetColor()
{
    setColor(7);
}

/* ===================== USER ===================== */

class User
{
protected:
    string name;
    int id;

public:
    User(string n, int i) : name(n), id(i) {}

    virtual void displayRole()
    {
        cout << "Role     : User\n";
    }

    string getName() const { return name; }
    int getId() const { return id; }
};

/* ===================== TEACHER ===================== */

class Teacher : public User
{
    string subject;

public:
    Teacher(string n, int i, string sub)
        : User(n, i), subject(sub) {}

    void displayRole() override
    {
        cout << "Role     : Teacher\n";
        cout << "Subject  : " << subject << endl;
    }
};

/* ===================== STUDENT ===================== */

class Student : public User
{
    string assignment;
    float similarity;
    float marks;

public:
    Student(int i, string n)
        : User(n, i), similarity(0), marks(0) {}

    void setAssignment(const string &a) { assignment = a; }
    string getAssignment() const { return assignment; }

    void setResult(float s, float m)
    {
        similarity = s;
        marks = m;
    }

    float getSimilarity() const { return similarity; }
    float getMarks() const { return marks; }
};

/* ===================== PLAGIARISM CHECKER ===================== */

class PlagiarismChecker
{
public:
    static float calculateSimilarity(const string &text1, const string &text2)
    {
        string w1, w2;
        int match = 0, total = 0;

        stringstream s1(text1);
        while (s1 >> w1)
        {
            total++;
            stringstream s2(text2);
            while (s2 >> w2)
            {
                if (w1 == w2)
                {
                    match++;
                    break;
                }
            }
        }

        if (total == 0)
            return 0;

        return (match * 100.0f) / total;
    }

    static float assignMarks(float similarity)
    {
        return (similarity == 100.0f) ? 0 : ((similarity > 60) ? 50 : 80);
    }

    static string plagiarismLevel(float similarity)
    {
        if (similarity > 60)
            return "High Plagiarism";
        else if (similarity > 30)
            return "Medium Plagiarism";
        else
            return "Low Plagiarism";
    }
};

/* ===================== REPORT FILE HANDLER ===================== */

class ReportFileHandler
{
public:
    void saveResult(Student &s)
    {
        ofstream file("students.txt", ios::app);
        file << "ID: " << s.getId() << endl;
        file << "Name: " << s.getName() << endl;
        file << "Similarity: " << s.getSimilarity() << "%\n";
        file << "Marks: " << s.getMarks() << endl;
        file << "---------------------------\n";
        file.close();
    }

    void queryStudent(int studentID)
    {
        ifstream file("students.txt");
        string line;
        bool show = false;

        while (getline(file, line))
        {
            if (line.find("ID: ") == 0)
            {
                int idInFile = stoi(line.substr(4));
                show = (idInFile == studentID);
            }

            if (show)
            {
                cout << line << endl;
                if (line == "---------------------------")
                    break;
            }
        }
        file.close();
    }

    void resolveMarkComplaint(int studentID, float claimedMarks)
    {
        ifstream file("students.txt");
        string line;
        float storedMarks = -1;
        bool found = false;

        while (getline(file, line))
        {
            if (line.rfind("ID: ", 0) == 0 &&
                stoi(line.substr(4)) == studentID)
                found = true;

            if (found && line.rfind("Marks: ", 0) == 0)
            {
                storedMarks = stof(line.substr(7));
                break;
            }
        }
        file.close();

        setColor(11);
        if (!found)
            cout << "Student record not found.\n";
        else if (claimedMarks > storedMarks)
            cout << "Verdict: Marks were assigned correctly.\n";
        else
            cout << "Verdict: Your marks are already fair.\n";

        cout << "Query resolved. Thank you!\n";
        resetColor();
    }
};

/* ===================== MAIN ===================== */

int main()
{
    Teacher t1("Sir Adnan", 1, "Object Oriented Programming");
    vector<Student> students;
    vector<string> assignments;
    ReportFileHandler fileHandler;

    int menuChoice;

    setColor(11);
    cout << "\n==============================================\n";
    cout << "                PROJECT: GRADIENT              \n";
    cout << "==============================================\n\n";
    resetColor();

    cout << "User Name: " << t1.getName() << endl;
    cout << "User ID  : " << t1.getId() << endl;
    t1.displayRole();

    while (true)
    {
        setColor(14);
        cout << "\n******** MAIN MENU ********\n";
        resetColor();

        cout << "1. Add Students\n"
             << "2. Enter Assignments\n"
             << "3. Check Plagiarism\n"
             << "4. Student Query\n"
             << "5. Exit\n"
             << "----------------------------\n";

        cout << "Enter choice: ";
        cin >> menuChoice;
        cin.ignore();

        if (menuChoice == 1)
        {
            string name, idStr;
            int id;

            cout << "Enter students (END to stop)\n";
            while (true)
            {
                getline(cin, name);
                if (name == "END")
                    break;
                getline(cin, idStr);
                id = stoi(idStr);
                students.push_back(Student(id, name));
            }
        }
        else if (menuChoice == 2)
        {
            assignments.clear();
            string text;
            cout << "Enter assignments (END to stop)\n";
            while (true)
            {
                getline(cin, text);
                if (text == "END")
                    break;
                assignments.push_back(text);
            }
        }
        else if (menuChoice == 3)
        {
            ofstream("students.txt", ios::trunc).close();

            for (int i = 0; i < assignments.size(); i++)
            {
                float maxSimilarity = 0;
                float finalMarks = 0;

                for (int j = i + 1; j < assignments.size(); j++)
                {
                    float sim = PlagiarismChecker::calculateSimilarity(assignments[i], assignments[j]);
                    float marks = PlagiarismChecker::assignMarks(sim);

                    if (sim > maxSimilarity)
                    {
                        maxSimilarity = sim;
                        finalMarks = marks;
                    }
                }

                students[i].setResult(maxSimilarity, finalMarks);
                fileHandler.saveResult(students[i]);
            }
        }
        else if (menuChoice == 4)
        {
            int id;
            float claim;
            cout << "Enter Student ID: ";
            cin >> id;
            cout << "Enter claimed marks: ";
            cin >> claim;
            fileHandler.queryStudent(id);
            fileHandler.resolveMarkComplaint(id, claim);
        }
        else if (menuChoice == 5)
        {
            break;
        }
    }

    return 0;
}


   ## 👤 Author
**Yamna Kamal**
