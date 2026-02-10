#include <iostream>
#include <regex>
#include <iomanip>
using namespace std;

string studentHandler(string prompt){                
    regex pattern("[a-zA-Z -]+"); 
    string n;
    while(true){
        cout << prompt;
        if(getline(cin, n) && regex_match(n, pattern)) {
            return n;
        } else {
           cout << "Invalid name. Please use letters, spaces, or hyphens.\n";
        }
    }
}

double gradehandler(string prompt){
    regex pattern("^(100|[1-9][0-9]?)$"); 
    string grade;
    while(true){
        cout << prompt;
        cin >> grade;
        
        try{
            if(regex_match(grade, pattern)){
                return stod(grade);
            }
            
            if(stod(grade ) < 0 || stod(grade) > 100){
                cout << "invalid grade enter a value from 0 to 100\n";
                cin.clear();
                cin.ignore(1000, '\n');
            }
        }catch(invalid_argument e){
            cout << "invalid input please enter a numeric value\n";
            cin.clear();
            cin.ignore(1000, '\n');
        }
    }
}

bool gradeStatus(double grade){
    return grade >= 70;
}

string gradeAchievement(double grade){
    if(grade >= 98 && grade <= 100) return "Highest Honors";
    if(grade >= 95 && grade <= 97) return "High Honors";
    if(grade >= 90 && grade <= 94) return "With Honors";
    return "Not Applicable";
}

double getAverage(double grade[], int l){
    double sum = 0;
    for(int i = 0; i < l; i++){
        sum += grade[i];
    }
    return sum / l;
}

int main() {
    char option;
    string fNAme, lName;
    double writtenWork[5], performanceTask[5], quarterlyAssesment;
    
    do{
        fNAme = studentHandler("First Name: ");
        lName = studentHandler("Last Name: ");
        
        cout << "----- Written Work -----\n";
        for(int i = 0; i < 5; i++){
            writtenWork[i] = gradehandler("Written Work " + to_string(i + 1) + ": ");
        }
        
        cout << "----- Performance Task -----\n";
        for(int i = 0; i < 5; i++){
            performanceTask[i] = gradehandler("Performance Task " + to_string(i + 1) + ": ");
        }
        
        cout << "----- Quarterly Assesment -----\n";
        quarterlyAssesment = gradehandler("Quarterly Assesment: ");
        
        double finalGrade = getAverage(writtenWork, 5) * .2 + getAverage(performanceTask, 5) * .6 + quarterlyAssesment * .2;
        
        cout << "----- Student Report -----\n";
        cout << fixed << setprecision(2) << "Full Name: " << fNAme << " " << lName << "\nWritten Works [20%]: " << getAverage(writtenWork, 5) * .2 << "\nPerformance Task [60%]: " << getAverage(performanceTask, 5) * .6 << "\nQuarterly Assesment [20%]: " << quarterlyAssesment * .2 << "\nFinal Grade: " << finalGrade << "\nRemarks: " << (gradeStatus(finalGrade) ? "Passed" : "Failed" )<< "\nAchievement " << gradeAchievement(finalGrade) << endl;
    
        do{
            cout << "press C to add another student, press B to exit";
            cin >> option;
            option = tolower(option);
        } while(option != 'b' && option != 'c');
        
    } while(option == 'b');
    return 0;
}
