#include <iostream>
#include <fstream>

using std::cin;
using std::cout;
using std::endl;
using std::fstream;
using std::ios;

struct Student {
	unsigned fn;
	unsigned grade;
};

struct Protokol {
	Student* students;
};

int main() {
	int n;
	cin >> n;
	Protokol prot = { new Student[n] };

	for (int i = 0; i < n; ++i) {
		cout << "Enter student " << i+1 << " fn and grade: ";
		cin >> prot.students[i].fn >> prot.students[i].grade;
	}

	fstream studentFile;
	studentFile.open("students.dat", ios::out | ios::binary);

	if(!studentFile) {
		cout << "Error opening file" << endl;
		return -1;
	}

	for (int i = 0; i < n; ++i) {
		studentFile.write((char*) (prot.students + i), sizeof(Student));
	}

	studentFile.close();

	delete[] prot.students;
}
