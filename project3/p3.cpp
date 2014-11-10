#include<iostream>
#include<tuple>
#include<string>
#include<vector>
#include<fstream>
#include<map>

using namespace std;
string digrams[] = {"AA", "AG", "AC", "AT", "GA", "GG", "GC", "GT", "CA", "CG", "CC", "CT", "TA", "TG", "TC", "TT"};


tuple< string, vector<string>, string> parseFastaFile(string path){
	string header = "";
	vector<string> comments;
	string sequence = "";
	string tempString = "";

	ifstream file(path);

	while(file.good()){
		getline(file, tempString);
//		cout << "++"<< tempString <<"++"<<endl;
		if(tempString.substr(0,1) == ">"){
			header = tempString;
		}
		else if(tempString.substr(0,1) == ";"){
			comments.push_back(tempString);
		}
		else{
			sequence += tempString;
		}
	}

	return make_tuple(header, comments, sequence);
}

map< string, int > digramFreqScores(string s){
	map< string, int >scores;

	for(int i = 0; i < 16; i++){
		string dnaTemp = s;
		int count = 0;

		int index = 0;
		while(true){
			index = dnaTemp.find(digrams[i]);
			if(index == string::npos){
				break;
			}else{
				dnaTemp.replace(index, 1, "X");
				count++;
			}
		}
		scores[digrams[i]] = count;
	}
	return scores;
}



int main(){
	string file1, file2;

	cout << "Enter .txt file name: ";
	cin >> file1;
	tuple<string, vector<string>, string> parsed = parseFastaFile(file1);
/*
	cout << get<0>(parsed) << endl << endl;
	for(int i = 0; i < get<1>(parsed).size(); i++){
		cout << get<1>(parsed)[i] << endl;
	}
	cout << endl << get<2>(parsed) << endl << endl;
*/

	map< string, int > scoreMap = digramFreqScores(get<2>(parsed));

	return 0;
}
