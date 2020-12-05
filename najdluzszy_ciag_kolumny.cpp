#include <iostream>

using namespace std;
const int WIERSZE = 6;
const int KOLUMNY = 7;

const int sequences[WIERSZE][KOLUMNY] = {
    {2,3,4,-1,-1,-1,-1},
    {1,4,1,1,12,15,15},
    {7,5,6,8,-1,-1,-1},
    {14,2,11,11,13,17,-1},
    {6,11,12,12,24,32,-1},
    {8,8,9,57,100,101,102}
};

void printOneDimensionArray(int *arr, int n) {
  for (int i = 0; i < n; i++) {
    cout << arr[i] << ", ";
  }
  cout << endl;
}

int main() {
	
	for (int i = 0; i < KOLUMNY; i++){
		int k = 0;
		if (j == 0) {
			for(int j = 0; j < WIERSZE; j++) {
				cout <<sequences[i][j] << ", "<<sequences[i+1][j] << endl;
				k++;
			}
		}
		printOneDimensionArray(arr, WIERSZE);
	}
}
