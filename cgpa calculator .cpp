#include <iostream>
#include <iomanip>
#include <string>
#include <cctype>

using namespace std;

// Function to convert letter grade to grade points
double letterToPoints(string grade) {
    // Convert to uppercase
    for (int i = 0; i < grade.length(); i++) {
        grade[i] = toupper(grade[i]);
    }
    
    if (grade == "A" || grade == "A+") return 4.0;
    if (grade == "A-") return 3.7;
    if (grade == "B+") return 3.3;
    if (grade == "B") return 3.0;
    if (grade == "B-") return 2.7;
    if (grade == "C+") return 2.3;
    if (grade == "C") return 2.0;
    if (grade == "C-") return 1.7;
    if (grade == "D+") return 1.3;
    if (grade == "D") return 1.0;
    if (grade == "F") return 0.0;
    
    return -1; // Invalid grade
}

// Function to convert percentage to grade points
double percentageToPoints(double percentage) {
    if (percentage >= 90) return 4.0;
    if (percentage >= 85) return 3.7;
    if (percentage >= 80) return 3.3;
    if (percentage >= 75) return 3.0;
    if (percentage >= 70) return 2.7;
    if (percentage >= 65) return 2.3;
    if (percentage >= 60) return 2.0;
    if (percentage >= 55) return 1.7;
    if (percentage >= 50) return 1.3;
    if (percentage >= 45) return 1.0;
    return 0.0;
}

int main() {
    int numSemesters, choice;
    double totalGradePoints = 0;
    double totalCredits = 0;
    
    // Welcome message
    cout << "\n====================================\n";
    cout << "       SIMPLE CGPA CALCULATOR       \n";
    cout << "====================================\n\n";
    
    // Get number of semesters
    cout << "How many semesters have you completed? ";
    cin >> numSemesters;
    
    // Choose input method
    cout << "\nHow do you want to enter grades?\n";
    cout << "1. Letter grades (A, B+, C-, etc.)\n";
    cout << "2. Percentage scores\n";
    cout << "Enter your choice (1 or 2): ";
    cin >> choice;
    
    // Loop through each semester
    for (int sem = 1; sem <= numSemesters; sem++) {
        int numCourses;
        double semesterPoints = 0;
        double semesterCredits = 0;
        
        cout << "\n====================================\n";
        cout << "         SEMESTER " << sem << "\n";
        cout << "====================================\n";
        
        cout << "How many courses in semester " << sem << "? ";
        cin >> numCourses;
        
        // Loop through each course in the semester
        for (int course = 1; course <= numCourses; course++) {
            string courseName;
            double credits;
            double gradePoints = 0;
            
            cout << "\nCourse " << course << ":\n";
            
            // Clear input buffer before getline
            cin.ignore();
            cout << "  Course name: ";
            getline(cin, courseName);
            
            cout << "  Credit hours: ";
            cin >> credits;
            
            // Get grade based on user's choice
            if (choice == 1) {
                string letterGrade;
                cout << "  Letter grade (A, B+, C-, etc.): ";
                cin >> letterGrade;
                gradePoints = letterToPoints(letterGrade);
                
                // Check if grade is valid
                if (gradePoints == -1) {
                    cout << "  Invalid grade! Setting to 0.0\n";
                    gradePoints = 0;
                }
            } 
            else if (choice == 2) {
                double percentage;
                cout << "  Percentage score: ";
                cin >> percentage;
                gradePoints = percentageToPoints(percentage);
            }
            
            // Calculate weighted points for this course
            double weightedPoints = gradePoints * credits;
            
            // Add to semester totals
            semesterPoints += weightedPoints;
            semesterCredits += credits;
            
            // Display course info
            cout << "  >> Grade points: " << fixed << setprecision(2) << gradePoints << "\n";
            cout << "  >> Weighted points: " << weightedPoints << "\n";
        }
        
        // Calculate semester GPA
        double semesterGPA = 0;
        if (semesterCredits > 0) {
            semesterGPA = semesterPoints / semesterCredits;
        }
        
        // Display semester summary
        cout << "\n------------------------------------\n";
        cout << "Semester " << sem << " Summary:\n";
        cout << "  Total Credits: " << semesterCredits << endl;
        cout << "  Total Points: " << semesterPoints << endl;
        cout << "  Semester GPA: " << fixed << setprecision(2) << semesterGPA << endl;
        cout << "------------------------------------\n";
        
        // Add to overall totals
        totalGradePoints += semesterPoints;
        totalCredits += semesterCredits;
    }
    
    // Calculate CGPA
    double cgpa = 0;
    if (totalCredits > 0) {
        cgpa = totalGradePoints / totalCredits;
    }
    
    // Display final results
    cout << "\n====================================\n";
    cout << "           FINAL RESULTS            \n";
    cout << "====================================\n";
    cout << "Total Credits: " << fixed << setprecision(2) << totalCredits << endl;
    cout << "Total Grade Points: " << totalGradePoints << endl;
    cout << "Your CGPA: " << cgpa << endl;
    
    // Display classification
    cout << "\nClassification: ";
    if (cgpa >= 3.8) {
        cout << "Summa Cum Laude (Highest Honors)" << endl;
    } else if (cgpa >= 3.6) {
        cout << "Magna Cum Laude (High Honors)" << endl;
    } else if (cgpa >= 3.4) {
        cout << "Cum Laude (Honors)" << endl;
    } else if (cgpa >= 3.0) {
        cout << "Upper Division" << endl;
    } else if (cgpa >= 2.0) {
        cout << "Lower Division" << endl;
    } else {
        cout << "Academic Probation" << endl;
    }
    
    cout << "\nThank you for using CGPA Calculator!\n";
    cout << "====================================\n";
    
    return 0;
}
