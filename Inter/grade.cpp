#include <iostream>
#include <string>
#include <iomanip>
using namespace std;

double inputHandler(string input){
    double grade;
    while(true){
        cout << input;
        if(cin >> grade && grade >= 0 && grade <= 100) return grade;
        cout << "Invalid Input, input must be 0-100 only.\n";
        cin.clear();
        cin.ignore(1000, '\n');
    }
}

double getAverage(double grade[], int size){
    double sum = 0;
    for(int i = 0; i < size; i++) sum += grade[i];
    return sum / size;
}

double finalOutput(double wwAvg, double petaAvg, double quarterly){
    return wwAvg * 0.2 + petaAvg * 0.6 + quarterly * 0.2;
}

string gradeAchievement(double grade){
    if(grade >= 98 && grade <= 100) return "With High Honors";
    else if(grade >= 95 && grade <= 97) return "High Honors";
    else if(grade >= 70 && grade < 95) return "Passed";
    else return "Failed";
}

bool gradeStatus(double grade){
    return grade >= 70;
}

int main(){
    char choice;
    string fName, lName;
    double writtenWork[5], performanceTask[5], quarterlyAssesment;

    do{
        cout << "Enter First Name: "; cin >> fName;
        cout << "Enter Last Name: "; cin >> lName;

        cout << "--- Written Work (1-100) ---\n";
        for(int i = 0; i < 5; i++){
            writtenWork[i] = inputHandler("Written Work " + to_string(i+1) + ": ");
        }

        cout << "--- Performance Task (1-100) ---\n";
        for(int i = 0; i < 5; i++){
            performanceTask[i] = inputHandler("Performance Task " + to_string(i+1) + ": ");
        }

        quarterlyAssesment = inputHandler("Quarterly Assessment Grade: ");

        double final = finalOutput(getAverage(writtenWork, 5), getAverage(performanceTask, 5), quarterlyAssesment);
        
        cout << fixed << setprecision(2);
        cout << "\n--- Student Report ---\n"
     << "Full Name: " << fName << " " << lName << "\n"
     << "Written Work [20%]: " << getAverage(writtenWork, 5) * 0.2 << "\n"
     << "Performance Task [60%]: " << getAverage(performanceTask, 5) * 0.6 << "\n"
     << "Quarterly Assessment [20%]: " << quarterlyAssesment * 0.2 << "\n"
     << "Final Grade: " << final << "\n"
     << "Remarks: " << (gradeStatus(final) ? "Passed" : "Failed") << "\n"
     << "Achievement: " << gradeAchievement(final) << "\n";

        do{
            cout << "\nEnter B to add another student or C to exit: ";
            cin >> choice;
            choice = tolower(choice);
        } while(choice != 'b' && choice != 'c');

    } while(choice == 'b');

    return 0;
}
