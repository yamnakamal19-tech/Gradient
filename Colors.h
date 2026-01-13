#ifndef COLORS_H
#define COLORS_H

#include <windows.h>
#include <iostream>
using namespace std;

void setColor(int color) {
    static HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, color);
}

void resetColor() {
    setColor(7);
}

#endif
