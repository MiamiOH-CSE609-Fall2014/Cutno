#include<iostream>
using namespace std;

//Matrix sizes
int m1row, m1col, m2row, m2col;
string m1 = "", m2 = "", m3 = "";

int main(){
	// Row & Col input
	cout << "Enter the number of ROWs for matrix 1: ";
	cin >> m1row;
	cout << "Enter the number of COLs for matrix 1: ";
	cin >> m1col;
	cout << "Enter the number of ROWs for matrix 2: ";
	cin >> m2row;

	// Proper sizes check
	if(m1col != m2row){
		cout << "Cols of matrix 1 must match Rows of matrix 2. Try again.\n";
		return 1;
	}
	
	// Row & Col input cont.
	cout << "Enter the number of COLs for matrix 2: ";
	cin >> m2col;

	// Init. matrix 1 & 2
	int M1 [m1col][m1row];
	int M2 [m2col][m2row];

	// Fill matrix 1
	cout << "Enter values for matrix 1 (one at a time)\n";
	for(int y = 0; y < m1row; y++){
		for(int x = 0; x < m1col; x++){
			cin >> M1[x][y];
		}
	}
	
	// Fill matrix 2
	cout << "\nEnter values for matrix 2 (one at a time)\n";
        for(int y = 0; y < m2row; y++){
                for(int x = 0; x < m2col; x++){
                        cin >> M2[x][y];
                }
        }



	// Print responses
	cout << "\n--Output--\n";

	// Print matrix 1
	for(int y = 0; y < m1row; y++){
		for(int x = 0; x < m1col; x++){
                        cout <<  M1[x][y] << " ";
                }
		cout << "\n";
	}	

	cout << "\n";
	// Print matrix 2
	for(int y = 0; y < m2row; y++){
                for(int x = 0; x < m2col; x++){
                        cout <<  M2[x][y] << " ";
                }
                cout << "\n";
        }
	
	return 0;
}
