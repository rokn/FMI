#include <iostream>

using namespace std;

const int EGN_SIZE = 10;
const int WEIGHTS_SIZE = 9;
int weight[]={2, 4, 8, 5, 10, 9, 7, 3, 6};

bool validateMonth(int month) {
	return (month >= 1 && month <= 12) ||
			(month >= 21 && month <= 32) ||
			(month >= 41 && month <= 52);
}

bool isLeapYear(int year) {
	return year % 4 == 0 && (year % 100 == 0 || year % 400 == 0);
}

int getRealMonth(int month) {
	if (month >= 21 && month <= 32) {
		month -= 20;
	} else if (month >= 41 && month <= 52) {
		month -= 40;
	}
	return month;
}

int getRealYear(int year, int month) {
	if (month >= 21 && month <= 32) {
		year = 1800 + year;
	} else if (month >= 41 && month <= 52) {
		year = 2000 + year;
	} else {
		year = 1900 + year;
	}
	return year;
}

int getMonthDays(int month, bool leapYear) {
	int monthDays = 0;
	switch(month) {
		case 1:
			monthDays = 31;
			break;
		case 2:
			monthDays = leapYear ? 29 : 28;
			break;
		case 3:
			monthDays = 31;
			break;
		case 4:
			monthDays = 30;
			break;
		case 5:
			monthDays = 31;
			break;
		case 6:
			monthDays = 30;
			break;
		case 7:
			monthDays = 31;
			break;
		case 8:
			monthDays = 31;
			break;
		case 9:
			monthDays = 30;
			break;
		case 10:
			monthDays = 31;
			break;
		case 11:
			monthDays = 30;
			break;
		case 12:
			monthDays = 31;
			break;
	}

	return monthDays;
}

bool validateDay(int year, int month, int day) {
	year = getRealYear(year, month);
	month = getRealMonth(month);
	int monthDays = getMonthDays(month, isLeapYear(year));
	return day >= 1 && day <= monthDays;
}

bool getEgnFromString(string egn, int* egnNumb) {
	for (int i = 0; i < EGN_SIZE; ++i) {
		if(egn[i] < '0' || egn[i] > '9') return false;
		egnNumb[i] = egn[i] - '0';
	}
	return true;
}

bool validate(string egn) {
	if (egn.size() != EGN_SIZE) return false;

	int egnNumb[EGN_SIZE];
	if(!getEgnFromString(egn, egnNumb)) {
		return false;
	}

	int year = egnNumb[0]*10 + egnNumb[1];
	int month = egnNumb[2]*10 + egnNumb[3];
	int day = egnNumb[4]*10 + egnNumb[5];
	bool valid = true;

	valid &= validateMonth(month);
	valid &= validateDay(year, month, day);

	int sum = 0;
	for (int i = 0; i < WEIGHTS_SIZE; ++i) {
		sum += egnNumb[i] * weight[i];
	}

	int control = sum % 11;
	if(control == 10) {
		control = 0;
	}

	valid &= control == egnNumb[EGN_SIZE - 1];

	return valid;
}

//9803287040

void printEgnData(string egn) {
	int egnNumb[EGN_SIZE];
	getEgnFromString(egn, egnNumb);
	bool male = egnNumb[8] % 2 == 0;
	int year = egnNumb[0]*10 + egnNumb[1];
	int month = egnNumb[2]*10 + egnNumb[3];
	int day = egnNumb[4]*10 + egnNumb[5];
	year = getRealYear(year, month);
	month = getRealMonth(month);
	cout << "This person is a " << (male ? "male":"female") << endl;
	cout << (male ? "He":"She") << " is born on " <<
	day << "." << month << "." << year << endl;
}

int main() {
	string egn;
	cin >> egn;
	cout << (validate(egn)?"EGN VALID":"EGN INVALID") << endl;
	printEgnData(egn);
	return 0;
}
