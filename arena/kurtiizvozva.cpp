#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

unsigned getMin(unsigned *arr, unsigned n) {
	unsigned min = *arr;
	for (int i = 1; i < n; ++i) {
		if(arr[i] < min) {
			min = arr[i];
		}
	}
	return min;
}

unsigned findMaxWeight(unsigned **graph, unsigned districts) {
	unsigned *maxWeights = new unsigned[districts-1];
	for (int i = 1; i < districts; ++i) {
		maxWeights[i-1] = graph[0][i];
	}

	for (int i = 1; i < districts; ++i) {
		for (int j = 1; j < districts; ++j) {
			if(i!=j) {
				maxWeights[j-1] = max(maxWeights[j-1], min(maxWeights[i-1], graph[i][j]));
			}
		}
	}

	unsigned min = getMin(maxWeights, districts-1);
	delete[] maxWeights;

	return min;
}

int main() {
	unsigned districts, paths;
	cin >> districts >> paths;
	unsigned **graph = new unsigned*[districts];
	for (int i = 0; i < districts; ++i) {
		graph[i] = new unsigned[districts];
		for (int j = 0; j < districts; ++j) {
			graph[i][j] = 0;
		}
	}

	for (int i = 0; i < paths; ++i) {
		unsigned first, second, maxWeight;
		cin >> first >> second >> maxWeight;
		first--;
		second--;
		unsigned& curr = graph[first][second];
		curr = max(curr, maxWeight);
		graph[second][first] = curr;
	}

	cout << findMaxWeight(graph, districts) << endl;

	//for (int i = 0; i < districts; ++i) {
		//for (int j = 0; j < districts; ++j) {
			//cout << graph[i][j] << " ";
		//}
		//cout << endl;
	//}
	
	for (int i = 0; i < districts; ++i) {
		delete[] graph[i];
	}
	delete[] graph;

	return 0;
}
