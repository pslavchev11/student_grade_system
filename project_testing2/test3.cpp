#include <iostream>
#include <fstream>
#include <vector>
#include <set>
#include <string>
using namespace std;
 
class Student {
public:
    Student() {
        cout << "Enter the name of the student: " ;
        cin >> name;
 
        cout << "Enter the Faculty: ";
        cin >> faculty; 
 
        cout << "Enter the faculty number of the student: ";
        cin >> facultyNum;
        
 
        cout << "Enter the number of the group: ";
        cin >> groupNum;
        
    }
 
    Student(ifstream& in) {
        in >> name;
        in >> faculty;
        in >> facultyNum;
        in >> groupNum;
    }
 
    void writeToFile(ofstream& out) const {
        out << name << "\n";
        out << faculty << "\n";
        out << facultyNum << "\n";
        out << groupNum << "\n";
    }
 
    friend ostream& operator<<(ostream& os, const Student& s) {
        os << "Name: " << s.name << "\n";
        os << "Faculty: " << s.faculty << "\n";
        os << "Faculty number: " << s.facultyNum << "\n";
        os << "Group number: " << s.groupNum << "\n";
        return os;
    }
 
    int getGroupNum() const {
        return groupNum;
    }
 
private:
    string name;
    string faculty;
    int facultyNum;
    int groupNum;
};
 
class Grades : public Student {
public:
    Grades() : Student() {
        cout << "Grades for the first semester: ";
        inputGrades(semester1);
 
        cout << "Grades for the second semester: ";
        inputGrades(semester2);
    }
 
    Grades(ifstream& in) : Student(in) {
        for (int i = 0; i < 5; i++) {
            in >> semester1[i];
        }
        for (int i = 0; i < 5; i++) {
            in >> semester2[i];
        }
    }
 
    void writeToFile(ofstream& out) const {
        Student::writeToFile(out);
        for (int i = 0; i < 5; i++) {
            out << semester1[i] << " ";
        }
        out << "\n";
        for (int i = 0; i < 5; i++) {
            out << semester2[i] << " ";
        }
        out << "\n";
    }
 
    friend ostream& operator<<(ostream& os, const Grades& g) {
        os << static_cast<const Student&>(g);
        os << "Grades for the first semester: ";
        g.displayGrades(g.semester1);
        os << "\n";
 
        os << "Grades for the second semester: ";
        g.displayGrades(g.semester2);
        os << "\n";
 
        return os;
    }
 
    double averageSuccess() const {
        int allGrades[10];
        for (int i = 0; i < 5; i++) {
            allGrades[i] = semester1[i];
        }
        for (int i = 0; i < 5; i++) {
            allGrades[i + 5] = semester2[i];
        }
        return calculateAverageSem(allGrades, 10);
    }
 
private:
    void inputGrades(int grades[5]) {
        for (int i = 0; i < 5; i++) {
            cin >> grades[i];
            
        }
    }
 
    void displayGrades(const int grades[5]) const {
        for (int i = 0; i < 5; i++) {
            cout << grades[i] << " ";
        }
    }
 
    double calculateAverageSem(const int grades[], int size) const {
        double sum = 0;
        for (int i = 0; i < size; i++) {
            sum += grades[i];
        }
        return sum / size;
    }
 
    int semester1[5];
    int semester2[5];
};
 
void printAverageSuccessForGroup(const vector<Grades>& students, int groupNum, ofstream& out) {
    double sum = 0;
    int count = 0;
    for (const Grades& student : students) {
        if (student.getGroupNum() == groupNum) {
            sum += student.averageSuccess();
            count++;
        }
    }
    out << "Average success for group " << groupNum << ": " << sum / count << "\n";
}
 
void printMinMaxSuccessForGroup(const vector<Grades>& students, int groupNum, ofstream& out) {
    double minSuccess = 6.0;
    double maxSuccess = 2.0;
    for (const Grades& student : students) {
        if (student.getGroupNum() == groupNum) {
            double success = student.averageSuccess();
            minSuccess = min(minSuccess, success);
            maxSuccess = max(maxSuccess, success);
        }
    }
    out << "Min success for group " << groupNum << ": " << minSuccess << "\n";
    out << "Max success for group " << groupNum << ": " << maxSuccess << "\n";
}
 
int main() {
    vector<Grades> students;
    set<int> groups;
 
    // Добавяне на студенти към вектора
    for (int i = 0; i < 3; i++) { // Променете числото според броя на студентите
        Grades g;
        students.push_back(g);
        groups.insert(g.getGroupNum());
    }
 
    // Отпечатване на информацията за всеки студент
    for (const Grades& student : students) {
        cout << student << "\n";
    }
 
    // Запис на студентите и успеха им във файл
    ofstream out("students.txt");
    for (const Grades& student : students) {
        student.writeToFile(out);
        
    }
 
    // Отпечатване и запис на средния успех за група
    for (int groupNum : groups) {
        printAverageSuccessForGroup(students, groupNum, out);
        printMinMaxSuccessForGroup(students, groupNum, out);
    }
 
    // Четене на студентите от файл
    ifstream in("students.txt");
    while (in) {
        students.push_back(Grades(in));
    }
 
    return 0;
}