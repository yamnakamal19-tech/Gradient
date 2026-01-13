#ifndef REPORTFILEHANDLER_H
#define REPORTFILEHANDLER_H

#include <fstream>
#include <iostream>
#include "Student.h"
#include "PlagiarismChecker.h"

using namespace std;

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
        bool found = false, show = false;

        while (getline(file, line))
        {
            if (line.find("ID: ") == 0)
            {
                int idInFile = stoi(line.substr(4));
                if (idInFile == studentID)
                {
                    found = true;
                    show = true;
                }
                else
                {
                    show = false;
                }
            }
            if (show)
            {
                cout << line << endl;
                if (line == "---------------------------")
                    break;
            }
        }

        if (!found)
            cout << "Student not found in records.\n";
        file.close();
    }

    void resolveMarkComplaint(int studentID, float claimedMarks)
    {
        ifstream file("students.txt");
        string line;
        float storedMarks = -1;
        bool found = false;

        for (; getline(file, line);)
        {
            if (line.rfind("ID: ", 0) == 0 && stoi(line.substr(4)) == studentID)
                found = true;

            if (found && line.rfind("Marks: ", 0) == 0)
            {
                storedMarks = stof(line.substr(7));
                break;
            }
        }
        file.close();

        if (!found || storedMarks == -1)
        {
            cout << "\nNo marks record found.\n";
            return;
        }

        cout << "\nStored marks: " << storedMarks << "\n";
        if (claimedMarks > storedMarks)
            cout << "Verdict: Marks were assigned correctly. \n";
        else
            cout << "Verdict: Your marks are already fair.\n";

        cout << "Query resolved. Thank you!\n";
    }
};

#endif
