#pragma once
#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
#include <map>
#include <fstream>
#include <sstream>

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

// Додали наступний рядок для підтримки кирилиці в консолі Windows
#ifdef _WIN32
#include <windows.h>
#endif

using namespace std;

class Vector {
private:
    vector<double> data;

public:
    Vector() {}

    Vector(vector<double> elements);

    void print() const;

    void sort(bool ascending);

    double length();

    double dotProduct(Vector other);

    bool isCollinear(Vector other);

    double angleWith(Vector other, int angleType = 1);

    Vector scalarMultiply(double scalar);

    friend ostream& operator<<(ostream& os, const Vector& vec);

    friend istream& operator>>(istream& is, Vector& vec);

    void saveToFile(const string& filename);

    static Vector loadFromFile(const string& filename);
};

extern map<string, Vector> vectors;

void createVector();

void listVectors();

void performOperation();
