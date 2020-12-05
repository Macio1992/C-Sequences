#include <iostream>
#include <fstream>
#include <sstream> 

using namespace std;
const int WIERSZE = 6;
const int KOLUMNY = 7;

const int sequences[WIERSZE][KOLUMNY] = {
    {2, 3, 4, -1, -1, -1, -1},
    {1, 4, 1, 1, 12, 15, 15},
    {7, 5, 6, 8, -1, -1, -1},
    {14, 2, 11, 11, 13, 17, -1},
    {6, 11, 12, 12, 24, 32, -1},
    {8, 8, 9, 57, 100, 101, 102}};

int newArr[KOLUMNY][WIERSZE];

void printOneDimensionArray(int *arr, int n) {
	for (int i = 0; i < n; i++) {
		cout << arr[i] << ", ";
	}
	cout << endl;
}

void transformArray() {
	for (int i = 0; i < KOLUMNY; i++) {
		for (int j = 0; j < WIERSZE; j++) {
			newArr[i][j] = sequences[j][i];
		}
	}
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

string zwrocNajdluzszyCiagRosnacy() {
	int najdluzszyCiag[KOLUMNY] = {-1,-1,-1,-1,-1,-1,-1};
	int indeksyNajdlCiagu[KOLUMNY] = {-1,-1,-1,-1,-1,-1,-1};
	int wiersz = 0;
	int k = 0;
	int maxCiag[KOLUMNY] = {-1,-1,-1,-1,-1,-1,-1};
	int maxCiagIndeksy[KOLUMNY] = {-1,-1,-1,-1,-1,-1,-1};
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

	string najdluzszyCiagString = "";

	for (int i = 0; i < KOLUMNY && maxCiagIndeksy[i] != -1; i++) {
		najdluzszyCiagString += "(" + to_string(maxWiersz+1) + "," + to_string(maxCiagIndeksy[i]+1) +")";
	}

	return najdluzszyCiagString;
}

string zwrocNajdluzszyCiagRosnacyKolumny() {
	int najdluzszyCiag[WIERSZE] = {-1,-1,-1,-1,-1,-1};
	int indeksyNajdlCiagu[WIERSZE] = {-1,-1,-1,-1,-1,-1};
	int wiersz = 0;
	int k = 0;
	int maxCiag[WIERSZE] = {-1,-1,-1,-1,-1,-1};
	int maxCiagIndeksy[WIERSZE] = {-1,-1,-1,-1,-1,-1};
	int max = 0;
	int maxWiersz = 0;

	for(int i = 0; i < KOLUMNY; i++) {
		k = 0;
		for(int j = 0; j < WIERSZE; j++) {
			if (newArr[i][j] != -1 && newArr[i][j+1] != -1) {
				if (newArr[i][j] < newArr[i][j+1]) {
					najdluzszyCiag[k] = newArr[i][j];
					najdluzszyCiag[k+1] = newArr[i][j+1];
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

	string najdluzszyCiagString = "";

	for (int i = 0; i < KOLUMNY && maxCiagIndeksy[i] != -1; i++) {
		najdluzszyCiagString += "(" + to_string(maxCiagIndeksy[i]+1) + "," + to_string(maxWiersz+1) +")";
	}

	return najdluzszyCiagString;
}

int policzLiczbyWWierszu(string line) {
	int digitsAmount = line[0] - '0';

	return digitsAmount;
}

int obliczIloscWierszy() {
	ifstream file("ciagi.txt");
	int i = 0;
	int n;
	int retrieved;

	while(file >> retrieved) {
		if (i < 1) {
			n = retrieved;
		}
		i++;
	}

	file.close();

	return n;
}

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



int main() {
	int ciagi;
	int i = 0;

	int wiersze = obliczIloscWierszy();
	int kolumny = obliczIloscKolumn();

	ifstream iFile("ciagi.txt");
	string line;

	int** array2D = new int*[wiersze];
	for(int i = 0; i < kolumny; ++i) {
		array2D[i] = new int[kolumny];
	}

	for (int i = 0; i < wiersze; i++) {
		for(int j = 0; j < kolumny; j++) {
			array2D[i][j] = -1;
		}
	}

	while(getline(iFile, line)) {
		// if (i > 0 && i < 2) {
			cout << "policzLiczbyWWierszu: " << policzLiczbyWWierszu(line) << endl;
			int iloscLiczbWWierszu = policzLiczbyWWierszu(line);

		// }
		i++;
	}

	cout <<"2D: "<<endl;
	for (int i = 0; i < wiersze; i++) {
		for(int j = 0; j < kolumny; j++) {
			cout << array2D[i][j] << " ";
		}
		cout << endl;
	}

	iFile.close();
}
