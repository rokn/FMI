#include <iostream>
using namespace std;

typedef unsigned int uint;

int main() {
	uint input;
	uint result = 0;
	uint mask = 1 << (sizeof(uint) * 8 - 1);

	cin >> input;

	if(input == 0) {
		cout << 0 << endl;
		return 0;
	}

	// Find first non zero bit
	while((mask & input) == 0) {
		mask >>= 1;
	}

	while(mask > 0) {
		bool state = (mask & input) == 0;
		bool bitPlace = !state;

		while (state == ((mask & input) == 0) && mask > 0) {
			if(bitPlace) {
				result |= mask;
			}

			mask >>= 1;
			bitPlace = !bitPlace;
		}
	}

	cout << result << endl;

	return 0;
}
