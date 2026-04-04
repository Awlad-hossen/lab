#include <iostream>
#include <iomanip>
#include <string>

using namespace std;

int main() {
    int numSemesters, choice;
    double totalPoints = 0;
    double totalCredits = 0;
    
    cout << "\n========== CGPA CALCULATOR ==========\n\n";
    
    cout << "How many semesters? ";
    cin >> numSemesters;
    
    cout << "\nEnter grades as:\n";
    cout << "1. Letter grades (A, B+, C-)\n";
    cout << "2. Percentages\n";
    cout << "Choice: ";
    cin >> choice;
    
    // Loop through each semester
    for (int s = 1; s <= numSemesters; s++) {
        int courses;
        double semPoints = 0;
        double semCredits = 0;
        
        cout << "\n--- SEMESTER " << s << " ---\n";
        cout << "Number of courses: ";
        cin >> courses;
        
        // Loop through each course
        for (int c = 1; c <= courses; c++) {
            string name;
            double credits;
            double gradeValue = 0;
            
            cout << "\nCourse " << c << ":\n";
            cout << "  Name: ";
            cin.ignore();
            getline(cin, name);
            
            cout << "  Credits: ";
            cin >> credits;
            
            // Get grade based on choice
            if (choice == 1) {
                string grade;
                cout << "  Grade (A, B+, C-, etc.): ";
                cin >> grade;
                
                // Convert letter grade to points
                if (grade == "A" || grade == "A+") gradeValue = 4.0;
                else if (grade == "A-") gradeValue = 3.7;
                else if (grade == "B+") gradeValue = 3.3;
                else if (grade == "B") gradeValue = 3.0;
                else if (grade == "B-") gradeValue = 2.7;
                else if (grade == "C+") gradeValue = 2.3;
                else if (grade == "C") gradeValue = 2.0;
                else if (grade == "C-") gradeValue = 1.7;
                else if (grade == "D+") gradeValue = 1.3;
                else if (grade == "D") gradeValue = 1.0;
                else if (grade == "F") gradeValue = 0.0;
                else {
                    cout << "  Invalid grade! Using 0.0\n";
                    gradeValue = 0.0;
                }
            } 
            else {
                double percent;
                cout << "  Percentage: ";
                cin >> percent;
                
                // Convert percentage to points
                if (percent >= 90) gradeValue = 4.0;
                else if (percent >= 85) gradeValue = 3.7;
                else if (percent >= 80) gradeValue = 3.3;
                else if (percent >= 75) gradeValue = 3.0;
                else if (percent >= 70) gradeValue = 2.7;
                else if (percent >= 65) gradeValue = 2.3;
                else if (percent >= 60) gradeValue = 2.0;
                else if (percent >= 55) gradeValue = 1.7;
                else if (percent >= 50) gradeValue = 1.3;
                else if (percent >= 45) gradeValue = 1.0;
                else gradeValue = 0.0;
            }
            
            double weighted = gradeValue * credits;
            semPoints += weighted;
            semCredits += credits;
            
            cout << "  >> Grade points: " << fixed << setprecision(2) << gradeValue << endl;
        }
        
        double semGPA = semPoints / semCredits;
        cout << "\nSemester GPA: " << fixed << setprecision(2) << semGPA << endl;
        
        totalPoints += semPoints;
        totalCredits += semCredits;
    }
    
    double cgpa = totalPoints / totalCredits;
    
    cout << "\n========== RESULTS ==========\n";
    cout << "Total Credits: " << totalCredits << endl;
    cout << "Total Points: " << totalPoints << endl;
    cout << "CGPA: " << fixed << setprecision(2) << cgpa << endl;
    
    // Show grade classification
    cout << "\nGrade: ";
    if (cgpa >= 3.8) cout << "A+ (Excellent)";
    else if (cgpa >= 3.5) cout << "A (Very Good)";
    else if (cgpa >= 3.0) cout << "B (Good)";
    else if (cgpa >= 2.5) cout << "C (Satisfactory)";
    else if (cgpa >= 2.0) cout << "D (Pass)";
    else cout << "F (Fail)";
    
    cout << "\n\nThank you!\n";
    
    return 0;
}
