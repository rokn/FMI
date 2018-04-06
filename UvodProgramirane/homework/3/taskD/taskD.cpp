#include <iostream>
using namespace std;

char** initMatrix(int m, int n);
void deleteMatrix(char** matrix, int n);
bool checkCrossword(const char** crossword, int rows, int cols, const char** dictionary, int dictSize);

const int MAX_WORD_SIZE = 40;

int main() {
	int dictSize;
	cin >> dictSize;
	char** dictionary = initMatrix(dictSize, MAX_WORD_SIZE);

	for (int i = 0; i < dictSize; ++i) {
		cin >> dictionary[i];
	}

	int rows, cols;
	cin >> rows >> cols;
	char **crossword = initMatrix(rows, cols+1);

	cin.ignore();
	for (int i = 0; i < rows; ++i) {
		cin.getline(crossword[i], cols+1);
	}

	bool isCrossword = checkCrossword(crossword, rows, cols, dictionary, dictSize);


	deleteMatrix(dictionary, dictSize);
	deleteMatrix(crossword, rows);
	return 0;
}

char** initMatrix(int m, int n) {
	char** dictionary = new char*[m];
	
	for (int i = 0; i < n; ++i) {
		dictionary[i] = new char[n];
	}

	return dictionary;
}

void deleteMatrix(char** matrix, int n) {
	for (int i = 0; i < n; ++i) {
		delete[] matrix[i];
	}

	delete[] matrix;
}

bool isletter(char ch) {
	return ch >= 'a' && ch <= 'z';
}

bool checkCrossword(const char** crossword, int rows, int cols, const char** dictionary, int dictSize) {
	for (int i = 0; i < rows-1; ++i) {
		for (int j = 0; j < cols; ++j) {
			bool isValid = true;
		}
	}

	for (int j = 0; j < cols-1; ++j) {
		for (int i = 0; i < rows; ++i) {
			
		}
	}
}
