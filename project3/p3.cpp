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

vector< vector<int> > digramFreqMatrix( map< string, int > scoreMap){
	vector< vector<int> > m;
	vector<int> temp;
	int index = 0;
	for(int i = 0; i < 16; i++){		
		temp.push_back(scoreMap[digrams[i]]);
                index++;

		if(index == 4){
                        m.push_back(temp);
                        index = 0;
                        temp.clear();
                }

//                cout << digrams[i] << " " << scoreMap[digrams[i]] << endl;
        }
	return m;
}

vector< vector<int> > parseScoringFile(string filepath){
	vector< vector<int> > scoreMat;
	vector<int> temp;
	string tempString = "";
        ifstream file(filepath);

	while(file.good()){
		temp.clear();
		getline(file, tempString);
		int current;
		int next = -1;

		do{
			current = next+1;
			next = tempString.find_first_of(',', current);
			temp.push_back(atoi(tempString.substr(current, next-current).c_str()));
		}
		while(next != string::npos);
		if(scoreMat.size() < 3)
			scoreMat.push_back(temp);
        }
	return scoreMat;
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
/*	
	for(int i = 0; i < 16; i++){
		cout << digrams[i] << " " << scoreMap[digrams[i]] << endl;
	}
*/

	vector< vector<int> > scoreMatrix = digramFreqMatrix(scoreMap);
/*	
	for(int first = 0; first < scoreMatrix.size(); first++){
		for(int second = 0; second < scoreMatrix[first].size(); second++){
			cout << scoreMatrix[first][second] << " ";
		}
		cout << endl;
	}	
*/

	cout << "Enter .csv file name: ";
	cin >> file2;
	vector< vector<int> > scoringMat = parseScoringFile(file2);

	for(int first = 0; first < scoringMat.size(); first++){
                for(int second = 0; second < scoringMat[first].size(); second++){
                        cout << scoringMat[first][second] << " ";
                }
                cout << endl;
        }


	return 0;
}
