#include<iostream>
#include<tuple>
#include<string>
#include<vector>
#include<fstream>

using namespace std;

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
	return 0;
}
