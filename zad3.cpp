#include <iostream>
#include <fstream>

using namespace std;

int obliczIloscKolumn() {
	ifstream file("ciagi.txt");
	string line;
	int i = 0;
	int retrieved;
	int max = 0;

	while(getline(file, line)) {
		if (i > 0) {
			int digitsAmount = line[0] - '0';
			if (digitsAmount > max) {
				max = digitsAmount;
			}
		}
		i++;
	}

	file.close();

	return max;
}

int countDigitsAmount() {
  ifstream iFile("ciagi.txt");
  int n;
  int i = 0;

  while(iFile >> n) {
    i++;
  }

  iFile.close();

  return i;
}

void printArray (int *arr, int n) {
  for(int i = 0; i < n; i++) {
    cout << arr[i] << " ";
  }
  cout << endl;
}

int policzDlugoscCiagu(int * ciag, int n) {
	int dlugosc = 0;

	for (int i = 0; i < n; i++) {
		if (ciag[i] != -1) {
		dlugosc++;
		}
	}

	return dlugosc;
}

int* createDynamicArray(int n) {
  int *arr = new int[n];

  for (int i = 0; i < n; i++)
  {
    arr[i] = -1;
  }

  return arr;
}

int** create2DDynamicArray(int n, int m) {
  int** array2D = new int*[n];
  for(int i = 0; i < n; ++i) {
    array2D[i] = new int[m];
  }

  for (int i = 0; i < n; i++)
  {
    for (int j = 0; j < m; j++)
    {
      array2D[i][j] = -1;
    }
  }

  return array2D;
}

int** transformArray(int **arr, int n, int m) {
	int** newArr = create2DDynamicArray(m,n);

  for (int i = 0; i < m; i++) {
		for (int j = 0; j < n; j++) {
			newArr[i][j] = arr[j][i];
		}
	}

  return newArr;
}

string zwrocNajdluzszyCiagRosnacy(int **sequences, int WIERSZE, int KOLUMNY) {
  int *najdluzszyCiag = createDynamicArray(KOLUMNY);
  int *indeksyNajdlCiagu = createDynamicArray(KOLUMNY);
	int wiersz = 0;
	int k = 0;
  int *maxCiag = createDynamicArray(KOLUMNY);
  int *maxCiagIndeksy = createDynamicArray(KOLUMNY);
	int max = 0;
	int maxWiersz = 0;

	for(int i = 0; i < WIERSZE; i++) {
		k = 0;
		for(int j = 0; j < KOLUMNY; j++) {
			if (sequences[i][j] != -1 && sequences[i][j+1] != -1) {
				if (sequences[i][j] < sequences[i][j+1]) {
					najdluzszyCiag[k] = sequences[i][j];
					najdluzszyCiag[k+1] = sequences[i][j+1];
					indeksyNajdlCiagu[k] = j;
					indeksyNajdlCiagu[k+1] = j+1;
					wiersz = i;
					k++;
				} else {
					k = 0;
				}
			}
		}

		int dlugosc_ciagu = policzDlugoscCiagu(najdluzszyCiag, KOLUMNY);
		if (dlugosc_ciagu > max) {
			max = dlugosc_ciagu;
			for (int i = 0; i < KOLUMNY; i++) {
				maxCiag[i] = najdluzszyCiag[i];
				maxCiagIndeksy[i] = indeksyNajdlCiagu[i];
				maxWiersz = wiersz;
			}
		}
	}

  // cout << "maxCiagi: "<<endl;
  // printArray(maxCiag, KOLUMNY);
  // cout << "maxCiagiIndeksy: "<<endl;
  // printArray(maxCiagIndeksy, KOLUMNY);
  // cout << "Max wiersz "<<maxWiersz<<endl;

	string najdluzszyCiagString = "";

	for (int i = 0; i < KOLUMNY && maxCiagIndeksy[i] != -1; i++) {
    najdluzszyCiagString += "(" + to_string(maxWiersz+1) + "," + to_string(maxCiagIndeksy[i]+1) +")";
    // cout << "to_string(maxCiagIndeksy[i]+1) "<< to_string(maxCiagIndeksy[i])<<endl;
	}

  delete [] najdluzszyCiag;
  delete [] indeksyNajdlCiagu;
  delete [] maxCiag;
  delete [] maxCiagIndeksy;

	return najdluzszyCiagString;
}

int main()
{
  int allDigitsCount = countDigitsAmount();
  int * allDigits = new int[allDigitsCount];

  ifstream iFile("ciagi.txt");
  int n;
  int retrieved;
  int i = 0;

  while(iFile >> retrieved) {
    allDigits[i] = retrieved;
    i++;
  }

  int WIERSZE = allDigits[0];
  int KOLUMNY = obliczIloscKolumn();

  int** sequences = new int*[WIERSZE];
  for(int i = 0; i < WIERSZE; ++i) {
    sequences[i] = new int[KOLUMNY];
  }

  for (int i = 0; i < WIERSZE; i++) {
    for (int j = 0; j < KOLUMNY; j++) {
      sequences[i][j] = -1;
    }
  }

  int elementsCount = allDigits[1];
  int beg = 1;
  int end = 5;

  int k = 0, kk = 0;
  while (end <= allDigitsCount+1) {
    kk = 0;
    for (int j = beg+1; j < end; j++) {
      kk++;
      sequences[k][kk-1] = allDigits[j];
    }
    k++;

    elementsCount = (end < allDigitsCount) ? allDigits[end] : 0;
    beg = end;
    end = beg + elementsCount + 1;
  }

  cout <<"Sequences: "<<endl;
  for (int i = 0; i < WIERSZE; i++) {
    for (int j = 0; j < KOLUMNY; j++) {
      cout << sequences[i][j] << " ";
    }
    cout << endl;
  }

  cout <<"zwrocNajdluzszyCiagRosnacy "<<zwrocNajdluzszyCiagRosnacy(sequences, WIERSZE, KOLUMNY) << endl;
  int **transformedArray = transformArray(sequences, WIERSZE, KOLUMNY);
  cout <<"zwrocNajdluzszyCiagRosnacy "<<zwrocNajdluzszyCiagRosnacy(transformedArray, KOLUMNY, WIERSZE) << endl;

  delete[] allDigits;
  for(int i = 0; i < WIERSZE; ++i) {
    delete[] sequences[i];
  }
  delete[] sequences;

  for(int i = 0; i < WIERSZE; ++i) {
    delete[] sequences[i];
  }
  delete[] sequences;

  for(int i = 0; i < KOLUMNY; ++i) {
    delete[] transformedArray[i];
  }
  delete[] sequences;

  iFile.close();
}
