#include <iostream>
#include <vector>
#include <iomanip>
#include <string>
#include <algorithm>

using namespace std;

class Course {
private:
    string name;
    double creditHours;
    double gradePoints;
    
public:
    Course(string n, double credits, double points) {
        name = n;
        creditHours = credits;
        gradePoints = points;
    }
    
    double getCreditHours() const { return creditHours; }
    double getGradePoints() const { return gradePoints; }
    string getName() const { return name; }
};

class Semester {
private:
    vector<Course> courses;
    int semesterNumber;
    
public:
    Semester(int num) : semesterNumber(num) {}
    
    void addCourse(string name, double credits, double points) {
        courses.push_back(Course(name, credits, points));
    }
    
    double getSemesterGPA() const {
        double totalPoints = 0;
        double totalCredits = 0;
        
        for (const auto& course : courses) {
            totalPoints += course.getGradePoints() * course.getCreditHours();
            totalCredits += course.getCreditHours();
        }
        
        if (totalCredits == 0) return 0;
        return totalPoints / totalCredits;
    }
    
    double getTotalCredits() const {
        double total = 0;
        for (const auto& course : courses) {
            total += course.getCreditHours();
        }
        return total;
    }
    
    double getTotalGradePoints() const {
        double total = 0;
        for (const auto& course : courses) {
            total += course.getGradePoints() * course.getCreditHours();
        }
        return total;
    }
    
    void displayCourses() const {
        cout << "\n--- Semester " << semesterNumber << " Courses ---\n";
        cout << left << setw(30) << "Course Name" 
             << setw(15) << "Credit Hours" 
             << setw(15) << "Grade Points" << endl;
        cout << string(60, '-') << endl;
        
        for (const auto& course : courses) {
            cout << left << setw(30) << course.getName()
                 << setw(15) << course.getCreditHours()
                 << setw(15) << fixed << setprecision(2) << course.getGradePoints() << endl;
        }
        cout << "\nSemester GPA: " << fixed << setprecision(2) << getSemesterGPA() << endl;
    }
};

double getGradePointsFromLetter(string grade) {
    // Convert to uppercase for case-insensitive comparison
    for (char &c : grade) c = toupper(c);
    
    if (grade == "A+" || grade == "A") return 4.00;
    if (grade == "A-") return 3.70;
    if (grade == "B+") return 3.30;
    if (grade == "B") return 3.00;
    if (grade == "B-") return 2.70;
    if (grade == "C+") return 2.30;
    if (grade == "C") return 2.00;
    if (grade == "C-") return 1.70;
    if (grade == "D+") return 1.30;
    if (grade == "D") return 1.00;
    if (grade == "F") return 0.00;
    
    return -1; // Invalid grade
}

double getGradePointsFromPercentage(double percentage) {
    if (percentage >= 90) return 4.00;
    if (percentage >= 85) return 3.70;
    if (percentage >= 80) return 3.30;
    if (percentage >= 75) return 3.00;
    if (percentage >= 70) return 2.70;
    if (percentage >= 65) return 2.30;
    if (percentage >= 60) return 2.00;
    if (percentage >= 55) return 1.70;
    if (percentage >= 50) return 1.30;
    if (percentage >= 45) return 1.00;
    return 0.00;
}

int main() {
    vector<Semester> semesters;
    int numSemesters;
    int inputChoice;
    
    cout << "=================================\n";
    cout << "   CGPA CALCULATOR\n";
    cout << "=================================\n\n";
    
    cout << "How many semesters have you completed? ";
    cin >> numSemesters;
    
    // Input validation
    if (numSemesters <= 0) {
        cout << "Invalid number of semesters!\n";
        return 1;
    }
    
    cout << "\nChoose input method:\n";
    cout << "1. Enter grades as letter grades (A, B+, C-, etc.)\n";
    cout << "2. Enter grades as percentages\n";
    cout << "Choice: ";
    cin >> inputChoice;
    
    for (int i = 0; i < numSemesters; i++) {
        int numCourses;
        cout << "\n=================================\n";
        cout << "SEMESTER " << (i + 1) << "\n";
        cout << "=================================\n";
        
        cout << "How many courses did you take in semester " << (i + 1) << "? ";
        cin >> numCourses;
        
        // Input validation
        if (numCourses <= 0) {
            cout << "Invalid number of courses! Skipping this semester.\n";
            continue;
        }
        
        Semester semester(i + 1);
        cin.ignore(); // Clear the newline character from previous input
        
        for (int j = 0; j < numCourses; j++) {
            string courseName;
            double creditHours;
            double gradePoints = 0;
            
            cout << "\nCourse " << (j + 1) << ":\n";
            cout << "  Course name: ";
            getline(cin, courseName);
            
            cout << "  Credit hours: ";
            cin >> creditHours;
            
            // Input validation for credit hours
            if (creditHours <= 0) {
                cout << "  Invalid credit hours! Setting to 0.\n";
                creditHours = 0;
            }
            
            if (inputChoice == 1) {
                string grade;
                cout << "  Letter grade (A, B+, C-, etc.): ";
                cin >> grade;
                gradePoints = getGradePointsFromLetter(grade);
                if (gradePoints == -1) {
                    cout << "  Invalid grade! Using 0.00\n";
                    gradePoints = 0;
                }
                cin.ignore(); // Clear the newline for next course name input
            } else if (inputChoice == 2) {
                double percentage;
                cout << "  Percentage score: ";
                cin >> percentage;
                gradePoints = getGradePointsFromPercentage(percentage);
                cin.ignore(); // Clear the newline for next course name input
            } else {
                cout << "  Invalid choice! Using default grade calculation.\n";
                gradePoints = 0;
                cin.ignore();
            }
            
            semester.addCourse(courseName, creditHours, gradePoints);
        }
        
        semester.displayCourses();
        semesters.push_back(semester);
    }
    
    // Calculate CGPA
    double totalGradePoints = 0;
    double totalCredits = 0;
    
    for (const auto& semester : semesters) {
        totalGradePoints += semester.getTotalGradePoints();
        totalCredits += semester.getTotalCredits();
    }
    
    double cgpa = (totalCredits > 0) ? totalGradePoints / totalCredits : 0;
    
    // Display final results
    cout << "\n=================================\n";
    cout << "           FINAL RESULTS\n";
    cout << "=================================\n";
    cout << fixed << setprecision(2);
    cout << "Total Credits Completed: " << totalCredits << endl;
    cout << "Total Grade Points Earned: " << totalGradePoints << endl;
    cout << "Your CGPA: " << cgpa << endl;
    
    // Display classification
    cout << "\nClassification: ";
    if (cgpa >= 3.80) cout << "Summa Cum Laude (Highest Honors)\n";
    else if (cgpa >= 3.60) cout << "Magna Cum Laude (High Honors)\n";
    else if (cgpa >= 3.40) cout << "Cum Laude (Honors)\n";
    else if (cgpa >= 3.00) cout << "Upper Division\n";
    else if (cgpa >= 2.00) cout << "Lower Division\n";
    else cout << "Academic Probation\n";
    
    cout << "\nThank you for using the CGPA Calculator!\n";
    
    return 0;
}
