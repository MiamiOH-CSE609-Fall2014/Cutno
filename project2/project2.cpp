#include<iostream>
#include<vector>
#include<stdexcept>
#include<string>
using namespace std;

vector<string> names;
vector<double> grades;
int vecIndex = 0;

string tempName = "";
double tempGrade = -1;

void getNamesGrades(){
	//Loop inputs
        while(true){
                try{
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
			cin.ignore();
			
                        //check if valid grade
                        if(tempGrade < 0.0 || tempGrade > 100.0){
                                throw out_of_range("Invalid grade input");
                        }

                        //save name and grade
                        names.push_back(tempName);
                        grades.push_back(tempGrade);
                        vecIndex++;
                }
                catch(out_of_range e){
                        cout << e.what() << ":\tRedo input for this student\n";
                }
		catch(exception ex){
			cout << "Unknown error with input\n";
		}
        }

}

int main (){
	cout << "Welcome to the grade curve system.\nEnter students full name followed by the grade earned.\nEnter lowercase <quit> as a name to stop taking input.\n\n";
	
	//get inputs
	getNamesGrades();
	
	for(int i = 0; i < names.size(); i++){
		cout << names[i] << "\t" << grades[i] << "\n";
	}	

	return 0;
}
