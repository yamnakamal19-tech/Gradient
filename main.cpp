#include <iostream>
#include <vector>
#include <string>
#include <windows.h>

#include "User.h"
#include "Teacher.h"
#include "Student.h"
#include "PlagiarismChecker.h"
#include "ReportFileHandler.h"
#include "Colors.h"

using namespace std;

int main()
{

    Teacher t1("Sir Adnan", 1, "Object Oriented Programming");
    vector<Student> students;
    ReportFileHandler fileHandler;
    vector<string> assignments;

    int menuChoice;

    setColor(11);
    cout << "\n==============================================\n";
    cout << "                PROJECT: GRADIENT              \n";
    cout << "==============================================\n\n";
    resetColor();

    setColor(7);
    cout << "User Name: " << t1.getName() << endl;
    cout << "User ID  : " << t1.getId() << endl;
    t1.displayRole();
    resetColor();

    while (true)
    {

        setColor(14);
        cout << "\n******** MAIN MENU ********\n";
        resetColor();

        setColor(7);
        cout << "1. Add Students\n"
             << "2. Enter Assignments\n"
             << "3. Check Plagiarism\n"
             << "4. Student Query\n"
             << "5. Exit\n"
             << "----------------------------\n";
        resetColor();

        setColor(7);
        cout << "Enter choice: ";
        resetColor();

        cin >> menuChoice;
        cin.ignore();

        if (menuChoice == 1)
        {
            string stuName, idStr;
            int stuID;
            int studentNumber = 1;

            cout << "\nEnter Students one by one (type END to stop):\n";

            for (;;)
            {
                setColor(13);
                cout << "\n----- Enter Student " << studentNumber << " Name: -----\n";
                resetColor();
                getline(cin, stuName);
                if (stuName == "END")
                    break;

                setColor(13);
                cout << "----- Enter Student " << studentNumber << " ID: -----\n";
                resetColor();
                getline(cin, idStr);
                if (idStr == "END")
                    break;

                stuID = stoi(idStr);
                students.push_back(Student(stuID, stuName));

                setColor(10);
                cout << "\nStudent added successfully!\n";
                resetColor();

                studentNumber++;
            }
        }

        else if (menuChoice == 2)
        {
            assignments.clear();
            string text;

            setColor(11);
            cout << "\nEnter Assignments (Press END on a new line to stop)\n";
            resetColor();

            while (true)
            {
                setColor(13);
                cout << "\n----- Enter Assignment " << assignments.size() + 1 << " -----\n";
                resetColor();

                getline(cin, text);

                if (text == "END")
                    break;

                assignments.push_back(text);
            }

            setColor(10);
            cout << "\nAll assignments saved.\n";
            resetColor();
        }

        else if (menuChoice == 3)
        {
            ofstream("students.txt", ios::trunc).close();

            if (assignments.size() < 2)
            {
                setColor(12);
                cout << "Enter at least two assignments first.\n";
                resetColor();
                continue;
            }

            setColor(11);
            cout << "\n******** PLAGIARISM RESULTS ********\n";
            resetColor();

            for (int i = 0; i < assignments.size(); i++)
            {

                float maxSimilarity = 0;
                float finalMarks = 0;

                for (int j = i + 1; j < assignments.size(); j++)
                {
                    float similarity = PlagiarismChecker::calculateSimilarity(assignments[i], assignments[j]);
                    float marks = PlagiarismChecker::assignMarks(similarity);
                    string level = PlagiarismChecker::plagiarismLevel(similarity);

                    if (similarity > maxSimilarity)
                    {
                        maxSimilarity = similarity;
                        finalMarks = marks;
                    }

                    setColor(13);
                    cout << "\nAssignment " << i + 1 << " vs Assignment " << j + 1 << endl;
                    resetColor();

                    cout << "Similarity Percentage : ";
                    setColor(14);
                    cout << similarity << "%\n";
                    resetColor();

                    cout << "Plagiarism Level      : ";
                    setColor(14);
                    cout << level << "\n";
                    resetColor();

                    cout << "Marks Assigned        : ";
                    setColor(14);
                    cout << marks << "\n";
                    resetColor();
                }
                students[i].setResult(maxSimilarity, finalMarks);
                fileHandler.saveResult(students[i]);
            }
        }

        else if (menuChoice == 4)
        {
            int studentID;
            cout << "Enter Student ID: ";
            cin >> studentID;
            cin.ignore();

            fileHandler.queryStudent(studentID);

            float claimMarks;
            cout << "\nEnter marks you think you deserve: ";
            cin >> claimMarks;
            cin.ignore();

            fileHandler.resolveMarkComplaint(studentID, claimMarks);
        }

        else if (menuChoice == 5)
        {
            setColor(12);
            cout << "Exiting program...\n";
            resetColor();
            break;
        }

        else
        {
            setColor(12);
            cout << "Invalid choice!\n";
            resetColor();
        }
    }

    return 0;
}