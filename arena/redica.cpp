#include <iostream>

using namespace std;

void increaseRes(long long count, long long& res) {
	if(count > 1) {
		res += ((count)*(count-1)) / 2;
	}
}

int main() {
	long n;
	cin >> n;
	long long res = n;
	long long prev, curr;
	long long count = 1;
	cin >> prev;

	for (int i = 1; i < n; ++i) {
		cin >> curr;
		if(curr == prev) {
			count++;
		} else {
			increaseRes(count, res);
			count = 1;
		}
		prev = curr;
	}

	increaseRes(count, res);

	cout << res << endl;
	return 0;
}
