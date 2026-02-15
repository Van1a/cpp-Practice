#include <iostream>
#include <iomanip> // set the decimal places 
#include <regex> // for matching pattern, using this to avoid code redundant

/*
   in requirement it required for input to be handle 'gracefully' so regex is better option
*/

using namespace std;

// validator for name and to initalize it.
string studentHandler(string text){
	regex pattern("^[a-zA-Z\244\324]+([ -][a-zA-Z\244\324]+)?$");
	string name;
	while(true){
		cout << text;
		if(getline(cin, name) && regex_match(name, pattern)) return name;
		cout << "Invalid Name! must be letters, spaces and enhypen only\n";
 	}
}

// validator for grade and initializer.
double gradeHandler(string text){
	regex pattern("^(0*(100(\\.+)?|[0-9]{1,2}(\\.\\d+)?))$");
	string grade;
	while(true){
		cout << text;
		try{
			if(getline(cin, grade) && regex_match(grade, pattern)) return stod(grade);
			
			if(stod(grade) < 0 && stod(grade) > 100){
				cout << "Invalid Grade! must be 0-100\n";
				continue; // to stop jumping on line 28
			}
			throw invalid_argument("Invalid Grade");
		}catch(invalid_argument e){
			cout << "Invalid input! Must be numeric value only\n";
		}
	}
}

// return the grade average by passing the array and the lenght of arrays.
double gradeAverage(double grade[], int l){
	double sum = 0;
	for(int i = 0; i < l; i++){
		sum += grade[i];
	}
	return sum / l;
}

// return the grade achievement
string gradeAchievement(double grade){
	if(grade >= 98) return "Highest Honor";
	if(grade >= 95) return "High Honor";
	if(grade >= 90) return "With Honor";
	return "Not Applicable";
}

int main(){
	// declaring variable to initialize later using method above.
	double writtenWork[5], performanceTask[5], quarterlyAssesment;
	string firstName, lastName;
	char option;
	
	do{
		// main function
		
		// student name initializer
		firstName = studentHandler("First Name: ");
		lastName = studentHandler("last Name: ");
		
		// grade initializer 
		cout << "----- Written Work -----\n";
		for(int i = 0; i < 5; i++){
			writtenWork[i] = gradeHandler("Written Work "+ to_string(i + 1)+ ": ");
		}
		
		cout << "----- Performance Task -----\n";
		for(int i = 0; i < 5; i++){
			performanceTask[i] = gradeHandler("performance Task "+ to_string(i + 1)+ ": ");
		}
		
		cout << "----- Quarterly Assesment -----\n";
		quarterlyAssesment = gradeHandler("Quarterly Assesment: ");
		
		cout << "----- Student Report -----\n";
		double finalGrade = gradeAverage(writtenWork, 5) * .2 + gradeAverage(performanceTask, 5) * .6 + quarterlyAssesment * .2;
		cout << fixed << setprecision(2) << "Full Name: " << firstName << " " << lastName << "\nWritten Work [20%]: " << gradeAverage(writtenWork, 5) * .2 << "\nPerformance Task [60%]: " << gradeAverage(performanceTask, 5) * .6 << "\nQuarterly Assesment [20%]: " << quarterlyAssesment * .2 << "\nFinal Grade: " << finalGrade << "\nRemarks: " << (finalGrade >= 70 ? "Passed" : "Failed") << "\nAchievement: " << gradeAchievement(finalGrade) << endl;
		
		do{ 
			// this loop is for option handling to compute another or to exit the program.
			cout << "Press C to compute another, Press E to Exit";
			cin >> option;
			option = tolower(option);
			cin.ignore(1000, '\n');
		}while(option != 'c' && option != 'e');
	}while(option == 'c');
	return 0;
}
