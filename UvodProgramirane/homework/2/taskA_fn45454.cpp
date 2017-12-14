#include <iostream>
using namespace std;

const int MAX_N = 10;

int getSum(int* start, int step, int n);
bool isMagicSquare(int* arr, int n);

int main() {
	unsigned int n, i;
	int arr[MAX_N*MAX_N];

	cin >> n;

	for (i = 0; i < n*n; ++i) {
		cin >> arr[i];
	}

	cout << (isMagicSquare(arr, n) ? "True" : "False") << endl;
	return 0;
}

bool isMagicSquare(int* arr, int n) {
	int sum = getSum(arr, 1, n);
	bool isMagic = true;

	for (int i = 0; i < n && isMagic; ++i) {
		isMagic &= (sum == getSum(arr + (i*n), 1, n));//Horizontal
		isMagic &= (sum == getSum(arr + i, n, n));//Vertical
	}

	isMagic &= (sum == getSum(arr, n+1, n));//Main diagonal
	isMagic &= (sum == getSum(arr + (n-1), n-1, n));//Secondary diagonal

	return isMagic;
}

int getSum(int* arr, int step, int n) {
	int sum = 0,i;
	for (i = 0; i < n; ++i) {
		sum += arr[step*i];
	}
	return sum;
}
