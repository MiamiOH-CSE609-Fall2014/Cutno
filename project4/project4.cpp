#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <stdlib.h>
#include <algorithm>
#include <time.h>
#include <stdio.h>

using namespace std;

string highScorer = "";
int highScore = 0;
vector< vector<string> > data;
string currentSentence;
string sentence;
string category;
int bank = 0;
int spinvalue = 0;

void loadFile(){
	vector<string> tempVec;
	string temp;
	ifstream file("data.txt");
	
	getline(file, highScorer);
	getline(file, temp);
	highScore = atoi(temp.c_str());	

	cout << "\nHigh scoreer is " << highScorer << " with $" << highScore << endl << endl;

	getline(file, temp);

	while(file.good()){
		getline(file, temp);
		transform(temp.begin(), temp.end(), temp.begin(), ::toupper);

		if(temp == "-"){
			data.push_back(tempVec);
			tempVec.clear();
		}
		else{
			tempVec.push_back(temp);
		}
	}
/*
	for(int i = 0; i < data.size(); i++){
		for(int j = 0; j < data[i].size(); j++){
			cout << data[i][j] << endl;
		}
		cout << endl;
	}
*/
	file.close();
}

void pickSentence(){
	int rand1 = rand() % data.size();
	int rand2 = rand() % (data[rand1].size()-1) + 1;
	sentence = data[rand1][rand2];
	category = data[rand1][0];	

//	cout << sentence << endl;
	
	currentSentence = "";
	for(string::iterator it = sentence.begin(); it < sentence.end(); it++){
		if(*it <= 'Z' && *it >= 'A'){
			currentSentence += '_';
		}
		else{
			currentSentence += *it;
		}
	}
	
//	cout << currentSentence << endl;
}

int spin(){
	int rand0 = rand() % 20 + 1;

	if(rand0 == 1)
		return -1; // bankrupt
	else if(rand0 == 2)
		return 2500;
	else
		return (rand() % 5 + 5) * 100;
}

void find(string in){
	string temp;
	int i = 0;
	string::iterator blank= currentSentence.begin();

	int count = 0;

	for(string::iterator it= sentence.begin(); it!=sentence.end(); it++){
               temp = *it;
		if(temp == in){
			*blank = *it;
			count++;
		}
		i++;
		blank++;
        }
	bank += count * spinvalue;
	cout << "\nYou uncovered " << count << " spaces!\nBank = $" << bank << endl << currentSentence << endl;
}

void guessV(){
	cout << "Enter a voul: ";
	string voul;
	cin >> voul;
	transform(voul.begin(), voul.end(), voul.begin(), ::toupper);

	if(voul.size() == 1 && (voul == "A" || voul == "E" || voul== "I" || voul== "O" || voul== "Y")){
		find(voul);
	}
	else{
		cout << "Invalid input! Your turn was skipped!" << endl;
	}
}

void guessSen(){
	cout << "Enter your guess: ";
	string sen;
	getline(cin, sen);
	getline(cin, sen);
	transform(sen.begin(), sen.end(), sen.begin(), ::toupper);

	string temp;

	if(sen == sentence){
		int count = 0;
		for(string::iterator it= currentSentence.begin(); it!=currentSentence.end(); it++){
               		temp = *it;
			if(temp == "_"){
				count++;
			}
        	}
		bank += count * spinvalue;
		cout << "\nYou uncovered " << count << " spaces!\nBank = $" << bank << endl << sentence << endl;
	}
	else{
		cout << "You guessed wrong, lost all of your winnings and the game!" << endl;
		bank = 0;
	}
	pickSentence();
}


void guessC(){
	cout << "Enter a consonant: ";
	string cons;
	cin >> cons;
	transform(cons.begin(), cons.end(), cons.begin(), ::toupper);

	string temp;

	if(cons.size() == 1 && cons != "A" && cons != "E" && cons != "I" && cons != "O" && cons != "Y"){
		find(cons);

		cout << "Do you want to try and guess the sentence? (y/n) ";
		cin >> temp;
	
		if(temp == "y" || temp == "Y"){
			guessSen();
		}
	}
	else{
		cout << "Invalid input! Your turn was skipped!" << endl;
	}
	
}

void guess(){
	string temp;
	
	cout << "Buy a voul for $250? (y/n) ";
	cin >> temp;

	if(bank >= 250 && (temp == "y" || temp == "Y")){
		bank = bank - 250;
		guessV();
	}
	else if(bank < 250 && (temp == "y" || temp == "Y")){
		cout << "You dont have money to buy a voul so guess a consonant" << endl;
		guessC();
	}
	else
		guessC();
}

string name(){
	cout << "\n\nYou beat the current high score!" << endl;
	cout << "Enter your name to let the world know: ";
	string input;
	getline(cin, input);
	getline(cin, input);
	return input;
}

void newScore(){
	ofstream newFile("temp.txt");
	if(newFile.is_open()){
		newFile<< name();
		newFile<< "\n";
		newFile<< to_string(bank);
		newFile<< "\n";

		string dataTemp;
		int i = 0;
		ifstream myfile("data.txt");
		if(myfile.is_open()){
			while(getline(myfile, dataTemp)){
				if(i > 1){
					newFile<< dataTemp;
					newFile<< "\n";
				}
				i++;		
			}
			myfile.close();
		}
		newFile.close();

	if( remove( "data.txt" ) != 0 )
    		perror( "Error deleting file" );
  	else
    		puts( "Successfully removed old high score" );

	int result;
  	char oldname[] ="temp.txt";
  	char newname[] ="data.txt";
  	result= rename( oldname , newname );
  	if ( result == 0 )
    		puts ( "Successfully added new high score" );
  	else
    		perror( "Error renaming file" );

	}
	else cout << "Unable to open file";
}

int main(){
	string quit = "N";
	int menuinput = 0;
	int multi = 0;

	srand(time(NULL));

	loadFile();
	pickSentence();
		

	do{
		cout << "\n\n\nCategory:\t" << category  << endl;
		cout << currentSentence << endl;	
		cout << "Current balance is $" << bank << endl;	


		spinvalue = spin();
		if(spinvalue != -1){
			cout <<  "You spun and landed on $" << spinvalue << "!" << endl;
			guess();
		}
		else{
			cout << "You spun a 'Bankrupt', lost all of your winnings and the game!" << endl;
			pickSentence();
			bank = 0;
		}

		cout << "\nQuit? (y/n) ";
		cin >> quit;

		if((quit == "y" || quit == "Y") && bank >= highScore){
			newScore();
		}

	}while(quit != "y");
	
	return 0;
}
