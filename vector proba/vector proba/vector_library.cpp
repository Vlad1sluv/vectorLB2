#include "vector_library.h"

Vector::Vector(vector<double> elements) {
    data = elements;
}

void Vector::print() const {
    cout << "(";
    for (int i = 0; i < data.size(); i++) {
        cout << data[i];
        if (i < data.size() - 1) {
            cout << ", ";
        }
    }
    cout << ")" << endl;
}

void Vector::sort(bool ascending) {
    if (ascending) {
        std::sort(data.begin(), data.end());
    }
    else {
        std::sort(data.rbegin(), data.rend());
    }
}

double Vector::length() {
    double sum = 0.0;
    for (double element : data) {
        sum += element * element;
    }
    return sqrt(sum);
}

double Vector::dotProduct(Vector other) {
    if (data.size() != other.data.size()) {
        cout << "�������: ������� ����� ���� ���������." << endl;
        return 0.0;
    }

    double result = 0.0;
    for (int i = 0; i < data.size(); i++) {
        result += data[i] * other.data[i];
    }
    return result;
}

bool Vector::isCollinear(Vector other) {
    return length() == 0 || other.length() == 0 || dotProduct(other) == (length() * other.length());
}

double Vector::angleWith(Vector other, int angleType) {
    if (angleType == 1) {
        double dot = dotProduct(other);
        double lenProduct = length() * other.length();
        if (lenProduct == 0.0) {
            return 0.0;
        }
        double cosTheta = dot / lenProduct;
        return acos(cosTheta) * 180.0 / M_PI;
    }
    else if (angleType == 2) {
        double angleWithX = atan2(data[1], data[0]) * 180.0 / M_PI;
        return angleWithX;
    }
    else if (angleType == 3) {
        double angleWithY = atan2(data[0], data[1]) * 180.0 / M_PI;
        return angleWithY;
    }
    else {
        cout << "�������� ��� ����." << endl;
        return 0.0;
    }
}

Vector Vector::scalarMultiply(double scalar) {
    Vector result(data);
    for (int i = 0; i < data.size(); i++) {
        result.data[i] *= scalar;
    }
    return result;
}

ostream& operator<<(ostream& os, const Vector& vec) {
    os << "(";
    for (int i = 0; i < vec.data.size(); i++) {
        os << vec.data[i];
        if (i < vec.data.size() - 1) {
            os << ", ";
        }
    }
    os << ")";
    return os;
}

istream& operator>>(istream& is, Vector& vec) {
    string input;
    getline(is, input);
    stringstream ss(input);
    vector<double> elements;
    while (getline(ss, input, ',')) {
        elements.push_back(atof(input.c_str()));
    }
    vec.data = elements;
    return is;
}

void Vector::saveToFile(const string& filename) {
    ofstream outFile(filename);
    if (outFile.is_open()) {
        for (int i = 0; i < data.size(); i++) {
            outFile << data[i];
            if (i < data.size() - 1) {
                outFile << ",";
            }
        }
        outFile.close();
        cout << "������ ��������� � ���� \"" << filename << "\"" << endl;
    }
    else {
        cerr << "������� �������� ����� ��� ����������!" << endl;
    }
}

Vector Vector::loadFromFile(const string& filename) {
    ifstream inFile(filename);
    if (inFile.is_open()) {
        string line;
        getline(inFile, line);
        stringstream ss(line);
        vector<double> elements;
        string input;
        while (getline(ss, input, ',')) {
            elements.push_back(atof(input.c_str()));
        }
        return Vector(elements);
    }
    else {
        cerr << "������� �������� ����� ��� ������������!" << endl;
        return Vector();
    }
}

map<string, Vector> vectors;

void createVector() {
    string name;
    cout << "������ ��'� �������: ";
    cin >> name;

    vector<double> elements;
    cout << "������ �������� �������, ������� �� ������ (���������, 1.0, 2.0, 3.0): ";
    string input;
    cin.ignore();
    getline(cin, input);

    stringstream ss(input);
    while (getline(ss, input, ',')) {
        elements.push_back(atof(input.c_str()));
    }

    vectors[name] = Vector(elements);
}

void listVectors() {
    for (const auto& pair : vectors) {
        cout << pair.first << ": ";
        pair.second.print();
    }
}

void performOperation() {
    string name1, name2, operation;
    cout << "������ ��'� ������� �������: ";
    cin >> name1;

    cout << "������ �������� (dotProduct, angleWith, length, scalarMultiply, sort, save, load): ";
    cin >> operation;

    if (operation == "dotProduct" || operation == "angleWith") {
        cout << "������ ��� ���� (1 - �� ���������, 2 - �� �������� � ���� X, 3 - �� �������� � ���� Y): ";
        int angleType;
        cin >> angleType;

        if (angleType == 1) {
            cout << "������ ��'� ������� �������: ";
            cin >> name2;

            if (vectors.find(name2) == vectors.end()) {
                cout << "������ " << name2 << " �� ����." << endl;
                return;
            }

            if (operation == "dotProduct") {
                cout << "��������� �������: " << vectors[name1].dotProduct(vectors[name2]) << endl;
            }
            else if (operation == "angleWith") {
                cout << "��� �� ���������: " << vectors[name1].angleWith(vectors[name2], angleType) << " �������" << endl;
            }
        }
        else if ((angleType == 2 || angleType == 3) && operation == "angleWith") {
            cout << "��� �� �������� � ���� ";
            if (angleType == 2) {
                cout << "X: ";
            }
            else {
                cout << "Y: ";
            }
            cout << vectors[name1].angleWith(Vector({ 1.0, 0.0 }), angleType) << " �������" << endl;
        }
        else {
            cout << "�������� ��� ����." << endl;
        }
    }
    else if (operation == "length") {
        cout << "������� �������: " << vectors[name1].length() << endl;
    }
    else if (operation == "scalarMultiply") {
        double scalar;
        cout << "������ ������: ";
        cin >> scalar;

        Vector result = vectors[name1].scalarMultiply(scalar);
        cout << "���������: ";
        result.print();
    }
    else if (operation == "sort") {
        bool ascending;
        cout << "��������� �� ����������? (1 - ���, 0 - �): ";
        cin >> ascending;

        vectors[name1].sort(ascending);
        cout << "³����������� ������: ";
        vectors[name1].print();
    }
    else if (operation == "save") {
        string filename;
        cout << "������ ��'� ����� ��� ����������: ";
        cin >> filename;
        vectors[name1].saveToFile(filename);
    }
    else if (operation == "load") {
        string filename;
        cout << "������ ��'� ����� ��� ������������: ";
        cin >> filename;
        vectors[name1] = Vector::loadFromFile(filename);
        cout << "������ ����������� � �����." << endl;
    }
    else {
        cout << "������� ��������." << endl;
    }
}
