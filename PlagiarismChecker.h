#ifndef PLAGIARISMCHECKER_H
#define PLAGIARISMCHECKER_H

#include <string>
#include <sstream>
using namespace std;

class PlagiarismChecker {
public:
    static float calculateSimilarity(const string& text1, const string& text2) {
        string w1, w2;
        int match = 0, total = 0;

        stringstream s1(text1);
        while (s1 >> w1) {
            total++;
            stringstream s2(text2);
            while (s2 >> w2) {
                if (w1 == w2) {
                    match++;
                    break;
                }
            }
        }

        if (total == 0) return 0;
        return (match * 100.0f) / total;
    }

    static float assignMarks(float similarity) {
        return (similarity == 100.0f) ? 0 : ((similarity > 60) ? 50 : 80);
    }

    static string plagiarismLevel(float similarity) {
        if (similarity > 60)
            return "High Plagiarism";
        else if (similarity > 30)
            return "Medium Plagiarism";
        else
            return "Low Plagiarism";
    }
};

#endif
