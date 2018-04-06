#include <iostream>

using std::cin;
using std::cout;
using std::endl;

const int MAX_NAME_LEN = 20;

struct Person {
	int age;
	char firstName[MAX_NAME_LEN];
	char lastName[MAX_NAME_LEN];
};

typedef bool (*PersonPredicate)(const Person&);
typedef void (*PersonConsumer)(Person&);

void inputPerson(Person& p) {
	cout << "Enter person's first name: ";
	cin >> p.firstName;
	cout << "Enter person's last name: ";
	cin >> p.lastName;
	cout << "Enter person's age: ";
	cin >> p.age;
}

void outputPerson(Person& p) {
	cout << p.firstName << " " << p.lastName << ", " << p.age << endl;
}

void filterPersons(Person* persons, unsigned personCount, PersonPredicate predicate, PersonConsumer consumer) {
	for (int i = 0; i < personCount; ++i) {
		if((*predicate)(persons[i])) {
			(*consumer)(persons[i]);
		}
	}
}

bool isAdult(const Person& person) {
	return person.age >= 18;
}


int main() {
	unsigned personCount;
	cin >> personCount;
	Person *persons = new Person[personCount];

	for (int i = 0; i < personCount; ++i) {
		inputPerson(persons[i]);
	}

	filterPersons(persons, personCount, &isAdult, &outputPerson);

	delete[] persons;
	return 0;
}


