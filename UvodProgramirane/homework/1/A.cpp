#include <iostream>

using namespace std;

typedef unsigned int uint;

int main() {
	uint n;
	int xPrev, xCurr;
	bool valid = true;
	bool low;

	cin >> n;

	if(n <= 2) {
		cout << "yes" << endl;
		return 0;
	}

	cin >> xPrev;
	cin >> xCurr;
	n -= 2;

	while(n > 0 && xPrev == xCurr) { // ignore repeating in the begining
		cin >> xCurr;
		n--;
	}

	low = xPrev <= xCurr;

	while(n-- > 0 && valid) {
		xPrev = xCurr;
		cin >> xCurr;
		valid = low ? xPrev >= xCurr : xPrev <= xCurr;
		low = !low;
	}

	cout << (valid ? "yes" : "no") << endl;

	return 0;
}
