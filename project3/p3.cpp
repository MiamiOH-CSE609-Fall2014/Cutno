#include<iostream>
#include<tuple>
#include<string>
#include<vector>
#include<fstream>
#include<map>

using namespace std;
string digrams[] = {"AA", "AG", "AC", "AT", "GA", "GG", "GC", "GT", "CA", "CG", "CC", "CT", "TA", "TG", "TC", "TT"};
map<string, int> index;

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
		if(scoreMat.size() < 4)
			scoreMat.push_back(temp);
        }
	return scoreMat;
}

tuple<int, int> scoreSequence(string haystack, string needle, vector< vector<int> > scoring_m){
	int maxIndex = 0;
	int maxScore = 0;
	int currentScore = 0;
	string first, second;
	
	for(int i = 0; i < haystack.length() - needle.length() +1; i++){
		currentScore = 0;
		string::iterator hay = haystack.begin();
		string::iterator need;
		advance(hay, i);

		for(need = needle.begin(); need < needle.end(); need++){
			first = *need;
			second = *hay;

//cout << *need << " " << *hay << " = " << scoring_m[index[first]][index[second]] << endl;
			currentScore += scoring_m[index[first]][index[second]];
			hay++;
		}
//cout << endl;
		
		if(currentScore >= maxScore){
			maxScore = currentScore;
			maxIndex = i;
		}
	}

	return make_tuple(maxIndex, maxScore);
}

tuple< int, int, string >findHighScore(string seq, vector<string> comp, vector< vector<int> > scoringMat){
	int Maxposition = 0;
	int Maxscore = 0;
	string needle = "";	

	tuple<int, int> temp;

	for(int i = 0; i < comp.size(); i++){
		temp = scoreSequence(seq, comp[i], scoringMat);
		if(get<1>(temp) > Maxscore){
			Maxscore = get<1>(temp);
			Maxposition = get<0>(temp);
			needle = comp[i];
		}
	}

	return make_tuple(Maxposition, Maxscore, needle);
}


int main(int argc, char* argv[]){
	if(argc != 3){
		cout << "Specify 2 file names." << endl;
		return 1;
	}

	index["A"] = 0;
	index["G"] = 1;
	index["C"] = 2;
	index["T"] = 3;

	string file1, file2;
	file1 = argv[1];
	file2 = argv[2];

	tuple<string, vector<string>, string> parsed = parseFastaFile(file1);

	map< string, int > scoreMap = digramFreqScores(get<2>(parsed));

	cout << "\tDiagram Frequency Matrix\n\t   A  G  C  T\n";
	string alpha[] = {"A", "G", "C", "T"};
	int index = 0;
	for(int i = 0; i < 4; i++){
		cout << "\t" << alpha[i];
		cout << "  " << scoreMap[digrams[index]];
		cout << " " << scoreMap[digrams[index+1]];
		cout << " " << scoreMap[digrams[index+2]];
		cout << " " << scoreMap[digrams[index+3]];
		index = index + 4;
		cout << endl;
	}


	vector< vector<int> > scoreMatrix = digramFreqMatrix(scoreMap);

	vector< vector<int> > scoringMat = parseScoringFile(file2);

	cout << "\n\tScoring Matrix\n\t   A G C T" << endl;

	for(int first = 0; first < scoringMat.size(); first++){
		cout << "\t" << alpha[first] << "  ";
                for(int second = 0; second < scoringMat[first].size(); second++){
                        cout << scoringMat[first][second] << " ";
                }
                cout << endl;
        }
	cout << endl;

	tuple<int, int> score = scoreSequence("GTGTCT", "TCT", scoringMat);

	vector<string> comp;
	int scoreNumber;
	string seq;
	cout << endl;
	cout << "How many sequences would you like to score? ";
	cin >> scoreNumber;

	for(int i = 0; i < scoreNumber; i++){
		cout << "Enter sequence #" << (i+1) << " on a single line:\n";
		cin >> seq;
		comp.push_back(seq);
	}	

	cout << endl;	

	vector<string> temp;
	for(int i = 0; i < scoreNumber; i++){
		temp.clear();
		temp.push_back(comp[i]);
		tuple<int, int, string> high = findHighScore(get<2>(parsed), temp, scoringMat);
		cout << "Sequence:" << endl;
		cout << get<2>(high) << endl;
		cout << "Score: " << get<1>(high) << " at position " << get<0>(high) << endl;
		cout << endl;
	}


	return 0;
}
