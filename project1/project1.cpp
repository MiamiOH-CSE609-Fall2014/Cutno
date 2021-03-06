#include<iostream>
using namespace std;

//Matrix sizes
int m1row, m1col, m2row, m2col;

int main(){
	// Row & Col input
	//cout << "Enter the number of ROWs for matrix 1: ";
	cin >> m1row;
	//cout << "Enter the number of COLs for matrix 1: ";
	cin >> m1col;
	//cout << "Enter the number of ROWs for matrix 2: ";
	cin >> m2row;

	// Proper sizes check
	if(m1col != m2row){
		cout << "Cols of matrix 1 must match Rows of matrix 2. Try again.\n";
		return 1;
	}
	
	// Row & Col input cont.
	//cout << "Enter the number of COLs for matrix 2: ";
	cin >> m2col;

	if(m1col < 1 | m1row < 1 | m2col < 1 | m2row < 1){
		cout << "dimentions should be at least 1\n";
		return 1;
	}

	// Init. matrix 1 & 2
	int M1 [m1col][m1row];
	int M2 [m2col][m2row];
	int M3 [m2col][m1row];
	for(int i = 0; i < m2col; i++){
		for(int j = 0; j < m1row; j++){
			M3[i][j] = 0;
		}
	}

	// Fill matrix 1
	//cout << "Enter values for matrix 1 (one at a time)\n";
	for(int y = 0; y < m1row; y++){
		for(int x = 0; x < m1col; x++){
			cin >> M1[x][y];
		}
	}
	
	// Fill matrix 2
	//cout << "\nEnter values for matrix 2 (one at a time)\n";
        for(int y = 0; y < m2row; y++){
                for(int x = 0; x < m2col; x++){
                        cin >> M2[x][y];
                }
        }

	// Math
	for(int i = 0; i < m1row; i++){
		for(int j = 0; j < m1col; j++){
			for(int k = 0; k < m2col; k++){
				M3[k][i] += M1[j][i] * M2[k][j];
			}
		}
	}

	// Print responses
	//cout << "\n--Output--\n";

	// Print matrix 1
	for(int y = 0; y < m1row; y++){
		for(int x = 0; x < m1col; x++){
                        cout <<  M1[x][y];
			if(x < m1col-1) cout << " ";
                }
		cout << "\n";
	}	

	cout << "\n";
	// Print matrix 2
	for(int y = 0; y < m2row; y++){
                for(int x = 0; x < m2col; x++){
                        cout <<  M2[x][y];
			if(x < m2col-1) cout << " ";
                }
                cout << "\n";
        }
	
	cout << "\n";
	// Print matrix 3
	for(int y = 0; y < m1row; y++){
               for(int x = 0; x < m2col; x++){
                       cout <<  M3[x][y];
			if(x < m2col-1) cout << " ";
               }
               cout << "\n";
        }

	
	return 0;
}
