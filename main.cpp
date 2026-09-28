#include <iostream>
#include <string>
#include <iomanip>

using namespace std;

const int MAX_CAPACITY = 50;

struct Student {
    int id;
    string name;
};

// Function Prototypes
int findStudentById(const Student roster[], int count, int targetId, int &comparisons);
bool addStudent(Student roster[], int &count, int id, const string &name);
bool removeStudentById(Student roster[], int &count, int targetId);
bool safeGetRecord(const Student roster[], int count, int index, Student &outStudent);
void printRoster(const Student roster[], int count);

int main() {
    Student roster[MAX_CAPACITY];
    int currentCount = 0;
    int choice = 0;

    do {
        cout << "\n=========================================\n";
        cout << "       NTC CC105: STUDENT ROSTER        \n";
        cout << "               MANAGER                  \n";
        cout << "=========================================\n";
        cout << "1. Add Student Record\n";
        cout << "2. Search Student by ID\n";
        cout << "3. Remove Student by ID\n";
        cout << "4. Safe Inspect Record by Index\n";
        cout << "5. Display Full Roster\n";
        cout << "6. Exit\n";
        cout << "Enter selection [1-6]: ";
        cin >> choice;

        switch (choice) {

            case 1: {
                if (currentCount >= MAX_CAPACITY) {
                    cout << "Roster is full. Cannot add another student.\n";
                    break;
                }

                int id;
                string name;

                cout << "Enter Student ID: ";
                cin >> id;

                cin.ignore();

                cout << "Enter Student Name: ";
                getline(cin, name);

                if (addStudent(roster, currentCount, id, name)) {
                    cout << "Student added successfully.\n";
                } else {
                    cout << "Student was not added. ID may already exist or roster is full.\n";
                }

                break;
            }

            case 2: {
                if (currentCount == 0) {
                    cout << "Roster is currently empty.\n";
                    break;
                }

                int targetId;
                int comparisons = 0;

                cout << "Enter Student ID to search: ";
                cin >> targetId;

                int index = findStudentById(
                    roster,
                    currentCount,
                    targetId,
                    comparisons
                );

                if (index != -1) {
                    cout << "\nStudent found!\n";
                    cout << "Index: " << index << endl;
                    cout << "ID: " << roster[index].id << endl;
                    cout << "Name: " << roster[index].name << endl;
                } else {
                    cout << "\nStudent ID not found.\n";
                }

                cout << "Total comparisons: " << comparisons << endl;

                break;
            }

            case 3: {
                if (currentCount == 0) {
                    cout << "Roster is currently empty.\n";
                    break;
                }

                int targetId;

                cout << "Enter Student ID to remove: ";
                cin >> targetId;

                if (removeStudentById(roster, currentCount, targetId)) {
                    cout << "Student removed successfully.\n";
                } else {
                    cout << "Student ID not found.\n";
                }

                break;
            }

            case 4: {
                if (currentCount == 0) {
                    cout << "Roster is currently empty.\n";
                    break;
                }

                int index;
                Student result;

                cout << "Enter array index: ";
                cin >> index;

                if (safeGetRecord(roster, currentCount, index, result)) {
                    cout << "\nRecord found safely!\n";
                    cout << "Index: " << index << endl;
                    cout << "ID: " << result.id << endl;
                    cout << "Name: " << result.name << endl;
                } else {
                    cout << "Invalid index. Access denied.\n";
                }

                break;
            }

            case 5: {
                printRoster(roster, currentCount);
                break;
            }

            case 6:
                cout << "Exiting system. Memory cleaned successfully.\n";
                break;

            default:
                cout << "Invalid selection. Please choose 1-6.\n";
        }

    } while (choice != 6);

    return 0;
}


// =====================================================
// FUNCTION: findStudentById
// =====================================================
int findStudentById(
    const Student roster[],
    int count,
    int targetId,
    int &comparisons
) {
    comparisons = 0;

    for (int i = 0; i < count; i++) {
        comparisons++;

        if (roster[i].id == targetId) {
            return i;
        }
    }

    return -1;
}


// =====================================================
// FUNCTION: addStudent
// =====================================================
bool addStudent(
    Student roster[],
    int &count,
    int id,
    const string &name
) {
    if (count >= MAX_CAPACITY) {
        return false;
    }

    int comparisons = 0;

    if (findStudentById(roster, count, id, comparisons) != -1) {
        return false;
    }

    roster[count].id = id;
    roster[count].name = name;

    count++;

    return true;
}


// =====================================================
// FUNCTION: removeStudentById
// =====================================================
bool removeStudentById(
    Student roster[],
    int &count,
    int targetId
) {
    int comparisons = 0;

    int index = findStudentById(
        roster,
        count,
        targetId,
        comparisons
    );

    if (index == -1) {
        return false;
    }

    for (int i = index; i < count - 1; i++) {
        roster[i] = roster[i + 1];
    }

    count--;

    return true;
}


// =====================================================
// FUNCTION: safeGetRecord
// =====================================================
bool safeGetRecord(
    const Student roster[],
    int count,
    int index,
    Student &outStudent
) {
    if (index < 0 || index >= count) {
        return false;
    }

    outStudent = roster[index];

    return true;
}


// =====================================================
// FUNCTION: printRoster
// =====================================================
void printRoster(
    const Student roster[],
    int count
) {
    if (count == 0) {
        cout << "\nRoster is currently empty.\n";
        return;
    }

    cout << "\n=========================================\n";
    cout << "              STUDENT ROSTER             \n";
    cout << "=========================================\n";

    cout << left
         << setw(10) << "Index"
         << setw(15) << "Student ID"
         << "Student Name" << endl;

    cout << "-----------------------------------------\n";

    for (int i = 0; i < count; i++) {
        cout << left
             << setw(10) << i
             << setw(15) << roster[i].id
             << roster[i].name << endl;
    }

    cout << "-----------------------------------------\n";
    cout << "Total Students: " << count << endl;
}


/*
=====================================================
PERFORMANCE REFLECTION
=====================================================

11. Random Access vs. Linear Search:

safeGetRecord executes in O(1) time because the array
index directly identifies the location of the requested
record. Only one element needs to be accessed.

findStudentById uses linear search, so it may need to
check every element in the array before finding the
target or determining that it does not exist. Therefore,
its worst-case time complexity is O(n).


12. Deletion Cost:

Deleting a record from index 0 is more computationally
expensive because every element after index 0 must be
shifted one position to the left.

Deleting the record at index currentCount - 1 is cheaper
because it is the last element, so no other elements
need to be shifted.

Therefore, deleting from the beginning can take O(n),
while deleting the last element takes O(1).

=====================================================
*/
