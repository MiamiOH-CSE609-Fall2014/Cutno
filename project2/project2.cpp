#include<iostream>
#include<vector>
#include<stdexcept>
#include<cstdlib>
#include<string>
#include<math.h>
using namespace std;

vector<string> names;
vector<double> grades;
vector<char> letterGrade;
int vecIndex = 0;

string tempName  = "";
double tempGrade = -1.0;
double average = 0.0;
double deviation = 0.0;

void getNamesGrades(){
	//Loop inputs
        while(true){
                try{
                        tempName = "";
			tempGrade = -1;
			//get name
                        cout << vecIndex << ")\tEnter name:\t";
                        getline(cin, tempName);
                        //do possible check for empty string here

                        //stop taking input - break loop
                        if(tempName.compare("quit") == 0 ){
                                break;
                        }

                        //get grade
                        cout << "\tEnter grade:\t";
                        cin >> tempGrade;
			if(cin.fail()){
				cin.clear();
                        	cin.ignore(80, '\n');
				throw out_of_range("A string is not a valid input");
			}
			cin.ignore();			

                        //check if valid grade
                        if(tempGrade < 0.0 || tempGrade > 100.0){
                                throw out_of_range("Grades must be between 0.0 and 100.0");
                        }

                        //save name and grade
                        names.push_back(tempName);
                        grades.push_back(tempGrade);
                        vecIndex++;
                }
                catch(out_of_range e){
                        cout << e.what() << ":\tRedo input for this student\n\n";
                }
        }

}

void doMath(){
	//clculate average grade
        for(int i = 0; i < grades.size(); i++){
                average += grades[i];
        }
        average = average/grades.size();

        //clculate standard deviation
        for(int i = 0; i < grades.size(); i++){
                deviation += pow( (grades[i] - average), 2.0);
        }
        deviation = sqrt(deviation/grades.size());
}

char findLetter(double grade){
	if(grade > average+(1.5*deviation))
		return 'A';
	else if(average+(.5*deviation) < grade && grade < average+(1.5*deviation))
		return 'B';
	else if(average+(-.5*deviation) < grade && grade < average+(.5*deviation))
		return 'C';
	else if(average+(-1.5*deviation) < grade && grade < average+(-.5*deviation))
		return 'D';
	else
		return 'F';
}

void printScale(){
	cout << "\n\n";
	cout << "Grading scale" << endl;
	if(average+(1.5*deviation) > 100)
		cout << "A above 100%" << endl;
	else
		cout << "A above " << average+(1.5*deviation) << "%" << endl;
	cout << "B " << average+(.5*deviation) << "% - " << average+(1.5*deviation) << "%" << endl;
	cout << "C " << average+(-.5*deviation) << "% - " << average+(.5*deviation) << "%" << endl;
	cout << "D " << average+(-1.5*deviation) << "% - " << average+(-.5*deviation) << "%" << endl;
	cout << "F below " << average+(-1.5*deviation) << "%\n" << endl;
}

int main (){
	cout << "Welcome to the grade curve system.\nEnter students full name followed by the grade earned.\nEnter lowercase <quit> as a name to stop taking input.\n\n";
	
	//get inputs
	getNamesGrades();
	
	//clculate average and deviation
	doMath();
	
	//print scale
	printScale();

	//find letter grade after curve
	for(int i = 0; i < grades.size(); i++){
		letterGrade.push_back(findLetter(grades[i]));
	}

	//print
	for(int i = 0; i < names.size(); i++){
		cout << names[i] << "\t" << grades[i] << "\t" << letterGrade[i] << "\n";
	}	

	return 0;
}
