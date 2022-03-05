#include <string>
#include <vector>
#include <iostream>
using namespace std;

#define ulong long long

struct Student {
    string name;
    string id;
    int age;
    float gpa;
};

class Hash {
    private:
        int hashMaxValue;
        vector<Student> *studentVector;
    public:
        Hash();
        ulong hashFunction(string key);
        void insertStudent(string id, string name, int age, float gpa);
        void displayStudent(string id);
};

Hash::Hash() {
    this->hashMaxValue = 500;
    studentVector = new vector<Student>[hashMaxValue];
}

ulong Hash::hashFunction(string key) {
    register ulong hash = 5381;
    int nKeyLength = key.length();
    for (int i = 0; i < nKeyLength; ++i) hash = (hash * 33 + key[i]) % hashMaxValue;
    return hash % hashMaxValue;
}

void Hash::insertStudent(string id, string name, int age, float gpa) {
    struct Student student;
    student.id = id;
    student.name = name;
    student.age = age;
    student.gpa = gpa;

    ulong hash = Hash::hashFunction(id);
    studentVector[hash].push_back(student);
}

void Hash::displayStudent(string id) {
    bool studentFound = false;

    for (int i = 0; i < hashMaxValue; i++) {
        for (auto student : studentVector[i]) {
            if (student.id == id) {
                studentFound = true;

                cout << endl << "Student found! " << endl;
                cout << "Id: " << student.id << endl;
                cout << "Name: " << student.name << endl;
                cout << "Age: " << student.age << endl;
                cout << "GPA: " << student.gpa << endl;
            }
        }
    }

    if (!studentFound) cout << "No student found with that id." << endl;
}

int main() {
    Hash hash;

    while (true) {
        cout << "Enter 1 to enter a new student." << endl << "Enter 2 to search for an existing student." << endl << "Choice: ";
        int choice;
        cin >> choice;

        if (choice == 1) {
            cout << endl << "10 digit student id: ";
            string id;
            cin >> id;
            
            while (id.length() != 10) {
                cout << endl << "Student id must be 10 digits long. 10 digit student id: ";
                cin >> id;
            }

            cout << "Student name: ";
            string name;
            cin >> name;

            cout << "Student age: ";
            int age;
            cin >> age;

            cout << "Student GPA: ";
            float gpa;
            cin >> gpa;

            hash.insertStudent(id, name, age, gpa);
            cout << "Student successfully added." << endl;
        } else if (choice == 2) {
            cout << "10 digit student id: ";
            string id;
            cin >> id;
            hash.displayStudent(id);
        }
        cout << endl;
    }
    return 0;
}
