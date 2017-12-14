#include <iostream>
using namespace std;

const int MAX_SIZE = 500;

int main() {
	int arr[MAX_SIZE];
	int n;
	long currMaxProd, currProd;

	cin >> n;

	for(int i = 0; i < n; i++) {
		cin >> arr[i];
	}

	// For clarity we will assume n >= 3

	//We must have some starting value for the maximum
	//so we take the first three elements product
	//otherwise we would need to set it to something really low
	currMaxProd = arr[0] * arr[1] * arr[2];

	// Traverse the array starting from the second element(index 1)
	// because we already have the first three elements product
	// ending at n-2 because we will want to "peek" two elements
	// forward from the current so we need to end the loop when we
	// don't have enough elements in front to peek
	for (int i = 1; i < n-2; ++i) {
		//Here we do the peeking and we multiply
		//the currrent element with the next and the next
		//You can look at this as a window over the array through
		//which we are looking:
		//[(3,2,4),5,2] <- starting postition
		//[3,(2,4,5),2] <- first enter of loop
		//[3,2,(4,5,2)] <- end of loop
		currProd = arr[i] * arr[i+1] * arr[i+2];
		
		//Checking if the product of the current 3 elements we inspect
		//is bigger than the current max
		if(currProd > currMaxProd) {
			currMaxProd = currProd;
		}
	}

	cout << "Max Prod: " << currMaxProd << endl;

	return 0;
}
