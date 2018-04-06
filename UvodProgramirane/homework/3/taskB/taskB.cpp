#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cstring>

#ifdef linux
#include <unistd.h>
#endif

using namespace std;

const char* chooseWord(const char** dictionary, int dictionarySize);
bool contains(const char* string, char character);
bool isWordGuessed(const char* word, const char* history);
int askForMistakes();
bool askForYesNo(const char* message);
char* askForWord();
void mainLoop(const char** dictionary, int dictionarySize);
bool isNotGameOver(int currMistakes, int maxMistakes, const char* word, const char* history);
char getAILetter(const char* history);
char getPlayerLetter(const char* history);
void printGameInfo(int currMistakes, int maxMistakes, const char* word, const char* history);

int main() {
	const int DICTIONARY_SIZE = 6;
	const char *dictionary[] = {"linux", "apple", "android", "sunglasses", "programming", "archery"};
	srand(time(NULL));
	mainLoop(dictionary, DICTIONARY_SIZE);
	return 0;
}

void mainLoop(const char** dictionary, int dictionarySize) {
	bool playing = true;
	int maxMistakes;
	int currMistakes;
	bool isAI;
	const char* word;
	char* history;
	int historyCount;
	char currLetter;

	while(playing) {
		maxMistakes = askForMistakes();
		currMistakes = 0;

		isAI = !askForYesNo("Do you want to guess");
		word = isAI ? askForWord() : chooseWord(dictionary, dictionarySize);

		history = new char[maxMistakes + strlen(word)];
		history[0] = '\0';
		historyCount = 0;

		while(isNotGameOver(currMistakes, maxMistakes, word, history)) {
			printGameInfo(currMistakes, maxMistakes, word, history);

			currLetter = isAI ? getAILetter(history) : getPlayerLetter(history);
#ifdef linux
			if(isAI) {
				sleep(2); // Sorry Windows users. Nothing personal ;)
			}
#endif
			if(isAI) {
				cout << "Computer guesses: " << currLetter << endl;
			}

			if(contains(word, currLetter)) {
				cout << "Great job '" << currLetter << "' is in the word!" << endl;
			} else {
				currMistakes++;
				cout << "Oops! '" << currLetter << "' is not in the word." << endl;
			}

			history[historyCount++] = currLetter;
			history[historyCount] = '\0';
		}

		cout << endl;

		if (currMistakes < maxMistakes) {
			cout << "Great job! You guessed the word: ";
		} else {
			cout << "You are hanged! The word was: ";
		}

		cout << word << endl << endl;

		if(isAI) {
			delete[] word;
			delete[] history;
		}


		playing = askForYesNo("Do you want to play again");
		cout << endl << endl;
	}
}

const char* chooseWord(const char** dictionary, int dictionarySize) {
	int randomWord = rand() % dictionarySize;
	return dictionary[randomWord];
}

bool contains(const char* string, char character) {
	do {
		if(*string == character) {
			return true;
		}
	} while (*(++string));

	return false;
}

bool isWordGuessed(const char* word, const char* history) {
	do {
		if(!contains(history, *word)) {
			return false;
		}
	} while (*(++word));

	return true;
}

int askForMistakes() {
	const int MAX_LEVEL = 5;
	int level;
	cout << "What level of difficulty do you want to play on (1-5): ";
	cin >> level;
	while(level <= 0 && level > 5) {
		cout << "Please select a correct level(1-5): ";
		cin >> level;
	}

	return (MAX_LEVEL - level) + 1;
}

bool askForYesNo(const char* message) {
	char answer;
	cout << message << " [y/n]: ";
	cin >> answer;
	while(tolower(answer) != 'y' && tolower(answer) != 'n') {
		cout << "Please answer with [y/n]: ";
		cin >> answer;
	}

	return tolower(answer) == 'y';
}

char* askForWord() {
	const int MAX_WORD_SIZE = 15;
	char* word = new char[MAX_WORD_SIZE];
	cout << "Input a word for the computer to guess(max "<<MAX_WORD_SIZE<<" characters): ";
	cin.ignore();
	cin.getline(word, MAX_WORD_SIZE);
	cout << word << endl;
	return word;
}

bool isNotGameOver(int currMistakes, int maxMistakes, const char* word, const char* history) {
	return currMistakes < maxMistakes && !isWordGuessed(word, history);
}

char getAILetter(const char* history) {
	char letter;
	do {
		letter = 'a' + (rand() % ('z'-'a')); // AI 101
	} while(contains(history, letter));
	return letter;
}

char getPlayerLetter(const char* history) {
	char letter;
	cout << "Choose a letter: ";
	cin >> letter;
	letter = tolower(letter);
	while(contains(history, letter) && letter < 'a' && letter > 'z') {
		cout << "Choose a letter[a-z]: ";
		cin >> letter;
		letter = tolower(letter);
	}

	return tolower(letter);
}

void printGameInfo(int currMistakes, int maxMistakes, const char* word, const char* history) {
	cout << endl << endl;
	cout << "["<<currMistakes<<"/"<<maxMistakes<<"] ";
	do {
		cout << (contains(history, *word) ? *word : '_');
	} while(*(++word));

	cout << " History: ";

	do {
		cout << *history;
		if(history[1]) {
			cout << ' ';
		}
	} while(*(++history));
	cout << endl;
}
