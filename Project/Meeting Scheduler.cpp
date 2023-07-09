#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <sstream>

using namespace std;

enum Designation { CEO, CTO, MANAGER, SR_EMPLOYEE, EMPLOYEE };

class Interval {
public:
    int start, end;

    Interval(int start, int end) : start(start), end(end) {}

    string toString() const {
        stringstream ss;
        ss << "[" << start << ", " << end << ")";
        return ss.str();
    }
};

class Employee {
public:
    int empId;
    Designation designation;
    vector<Interval> meetings;

    Employee(int empId, Designation designation) : empId(empId), designation(designation) {}

    void addMeeting(int start, int end) {
        meetings.emplace_back(start, end);
    }

    string toString() const {
        stringstream ss;
        ss << "Employee ID: " << empId << ", Designation: " << designation << endl;
        ss << "Meetings: " << endl;
        for (const auto& meeting : meetings) {
            ss << "  " << meeting.toString() << endl;
        }
        return ss.str();
    }
};

bool compareDesignation(Employee& emp1, Employee& emp2) {
    return emp1.designation < emp2.designation;
}

void removeConflictingMeetings(vector<Employee>& employees) {
    sort(employees.begin(), employees.end(), compareDesignation);

    for (int i = 0; i < employees.size(); i++) {
        for (int j = i + 1; j < employees.size(); j++) {
            vector<Interval> newMeetings;
            for (const auto& meeting : employees[i].meetings) {
                bool conflicting = false;
                for (const auto& otherMeeting : employees[j].meetings) {
                    if (meeting.start < otherMeeting.end && meeting.end > otherMeeting.start) {
                        conflicting = true;
                        break;
                    }
                }
                if (!conflicting) {
                    newMeetings.push_back(meeting);
                }
            }
            employees[i].meetings = newMeetings;
        }
    }
}

void saveDataToFile(const vector<Employee>& employees, const string& filename) {
    ofstream file(filename);
    if (file.is_open()) {
        for (const auto& employee : employees) {
            file << employee.empId << "," << employee.designation << ",";
            for (const auto& meeting : employee.meetings) {
                file << meeting.start << "-" << meeting.end << ",";
            }
            file << endl;
        }
        file.close();
        cout << "Data saved to " << filename << endl;
    } else {
        cout << "Error: Unable to open file." << endl;
    }
}

void loadDataFromFile(vector<Employee>& employees, const string& filename) {
    ifstream file(filename);
    if (file.is_open()) {
        string line;
        while (getline(file, line)) {
            stringstream ss(line);
            string token;
            getline(ss, token, ',');
            int empId = stoi(token);

            getline(ss, token, ',');
            Designation designation = static_cast<Designation>(stoi(token));

            Employee employee(empId, designation);
            while (getline(ss, token, ',')) {
                stringstream ms(token);
                string meetingToken;
                getline(ms, meetingToken, '-');
                int start = stoi(meetingToken);
                getline(ms, meetingToken, '-');
                int end = stoi(meetingToken);
                employee.addMeeting(start, end);
            }
            employees.push_back(employee);
        }
        file.close();
        cout << "Data loaded from " << filename << endl;
    } else {
        cout << "Error: Unable to open file." << endl;
    }
}

void printSchedule(const vector<Employee>& employees) {
    for (const auto& employee : employees) {
        cout << employee.toString() << endl;
    }
}

int main() {
    vector<Employee> employees;
    string dataFile = "employees_data.txt";

    // Load data from file (if available)
    loadDataFromFile(employees, dataFile);

    int option;
    do {
        cout << "Meeting Scheduler" << endl;
        cout << "1. Add Employee" << endl;
        cout << "2. Add Meeting for Employee" << endl;
        cout << "3. Remove Conflicting Meetings" << endl;
        cout << "4. Print Schedule" << endl;
        cout << "5. Save Data to File" << endl;
        cout << "0. Exit" << endl;
        cout << "Enter option: ";
        cin >> option;

        switch (option) {
            case 1: {
                int empId;
                int designation;
                cout << "Enter Employee ID: ";
                cin >> empId;
                cout << "Enter Designation (0 - CEO, 1 - CTO, 2 - MANAGER, 3 - SR_EMPLOYEE, 4 - EMPLOYEE): ";
                cin >> designation;
                Designation empDesignation = static_cast<Designation>(designation);
                employees.emplace_back(empId, empDesignation);
                cout << "Employee added successfully." << endl;
                break;
            }
            case 2: {
                int empId;
                int start, end;
                cout << "Enter Employee ID: ";
                cin >> empId;
                bool found = false;
                for (auto& employee : employees) {
                    if (employee.empId == empId) {
                        cout << "Enter Meeting Start Time: ";
                        cin >> start;
                        cout << "Enter Meeting End Time: ";
                        cin >> end;
                        employee.addMeeting(start, end);
                        found = true;
                        cout << "Meeting added successfully." << endl;
                        break;
                    }
                }
                if (!found) {
                    cout << "Error: Employee not found." << endl;
                }
                break;
            }
            case 3: {
                removeConflictingMeetings(employees);
                cout << "Conflicting meetings removed successfully." << endl;
                break;
            }
            case 4: {
                printSchedule(employees);
                break;
            }
            case 5: {
                saveDataToFile(employees, dataFile);
                break;
            }
            case 0: {
                cout << "Exiting..." << endl;
                break;
            }
            default: {
                cout << "Invalid option. Please try again." << endl;
                break;
            }
        }
        cout << endl;
    } while (option != 0);

    return 0;
}
