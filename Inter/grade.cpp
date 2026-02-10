#include <iostream>
#include <iomanip>
#include <regex>
using namespace std;

string studentHandler(string prompt){
  regex pattern("[a-zA-Z -]+");
  string n;
  while(true){
    cout << prompt;
    if(getline(cin, n) && regex_match(n, pattern)){
       return n;
    } else {
      cout << "Invalid Input must be Enhypen, space only\n";
      cin.clear();
    }
  }
}


double gradeHandler(string prompt){
    regex pattern("^(100|[1-9]?[0-9])$");
    string grade;
    while(true){
        cout << prompt;
        cin >> grade;
        
        try{
            if(regex_match(grade, pattern)) return stod(grade);
            if(stod(grade ) < 0 || stod(grade) > 100){
                cout << "invalid grade enter a value from 0 to 100\n";
                cin.clear();
                cin.ignore(1000, '\n');
                continue;
            }
            throw invalid_argument("Invalid");
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
  if(grade >= 98 && grade <= 100) return "Highest Honor";
  if(grade >= 95 && grade <= 97) return "High Honors";
  if(grade >= 90 && grade <= 95) return "With Honors";
  return "Not Applicable";
}

double getAverage(double grade[], int l){
  double sum = 0;
  for(int i = 0; i < l; i++){
    sum += grade[i];
  }
  return sum / l;
}

int main(){
  system("clear");
  char option;
  double writtenWork[5], performanceTask[5], quarterlyAssesment;
  string firstName, lastName;
  
  do{
    firstName = studentHandler("First Name: ");
    lastName = studentHandler("Last Name: ");
    
    cout << "----- Written Work ------\n";
    for(int g = 0; g < 5; g++){
      writtenWork[g] = gradeHandler("Written Work: " + to_string(g+1) + ": ");
    }
    
    cout << "----- Performance Task ------\n";
    for(int g = 0; g < 5; g++){
      performanceTask[g] = gradeHandler("Performance Task: " + to_string(g + 1) + ": ");
    }
    
    cout << "----- Performance Task ------\n";
    quarterlyAssesment = gradeHandler("Quarterly Assesment: ");
    
    cout << "----- Student Report ------\n";
    double finalGrade = getAverage(writtenWork, 5) * .2 + getAverage(performanceTask, 5) * .6 + quarterlyAssesment * .2;
    
    cout << fixed << setprecision(2) << "Student Name: " << firstName << " " << lastName << "\nWritten Work [20%]: " << getAverage(writtenWork, 5) * .2 << "\nPerformance Task [60%]: " << getAverage(performanceTask, 5) * .6 << "\nQuarterly Assesment [20%]: " << quarterlyAssesment * .2 << "\nFinal Grade: " << finalGrade << "\nRemarks: " << (gradeStatus(finalGrade) ? "Passed" : "Failed") << "\nAchievement: " << gradeAchievement(finalGrade) << endl;
    
    do{
      cout << "Press E to Exit & Press C to Continue\n";
      cin >> option;
      option = tolower(option);
    } while(option != 'e' && option != 'C');
  } while(option == 'c');
  return 0;
}
