#include <iostream>
#include <cstring>
using namespace std;

typedef unsigned int uint;

const uint MAX_INPUT_SIZE = 1000;

uint parse(char* str, uint size);
char* decompress(char* compressed);
uint pow(uint n, uint power);
bool isNull(char *ch);
bool isDigit(char *ch);
bool isLetter(char *ch);
uint readCompressionSize(char*& compressed);
void repeatCopy(char *destination, char *src, uint times, uint len);

int main() {
	char *input = new char[MAX_INPUT_SIZE];
	cin.getline(input, MAX_INPUT_SIZE);

	char *decompressed = decompress(input);
	cout << decompressed << endl;

	delete[] input;
	delete[] decompressed;

	return 0;
}

char* decompressInternal(char*& compressed, uint& resSize) {
	char *res;
	uint writeStart = resSize;
	if(isNull(compressed) || *compressed == ')') {
		resSize++;
		res = new char[resSize];
		res[writeStart] = '\0';
		return res;
	} else if (isDigit(compressed)) {
		uint compressionTimes = readCompressionSize(compressed);
		uint decompressedSize = 0;

		compressed++; // skip opening brace
		char *decompressedInside = decompressInternal(compressed, decompressedSize);

		resSize += (decompressedSize-1) * compressionTimes; // -1 to not include the \0-s
		compressed++; // skip closing brace

		res = decompressInternal(compressed, resSize);
		repeatCopy(res + writeStart, decompressedInside, compressionTimes, decompressedSize-1);
		delete decompressedInside;
		return res;
	} else {
		char ch = *compressed;
		resSize++;
		compressed++;
		res = decompressInternal(compressed, resSize);
		res[writeStart] = ch;
		return res;
	}
}

void repeatCopy(char *destination, char *src, uint times, uint len) {
	for(int i = 0; i < times; ++i) {
		strncpy(destination + i*len, src, len);
	}
}

uint readCompressionSize(char*& compressed) {
	char *sizeStart = compressed;

	while(isDigit(compressed)) {
		++compressed;
	}

	return parse(sizeStart, compressed - sizeStart);
}

char* decompress(char* compressed) {
	uint size = 0;
	decompressInternal(compressed, size);
}

uint parse(char* str, uint size) {
	uint res = 0;
	int i = size;

	while(i--) {
		res += (str[i] - '0') * pow(10, (size-1) - i);
	}

	return res;
}

uint pow(uint n, uint power) {
	uint res = 1;
	for (int i = 0; i < power; ++i) {
		res *= n;
	}
	return res;
}

bool isNull(char *ch) {
	return !(*ch);
}

bool isDigit(char *ch) {
	return *ch >= '0' && *ch <= '9';
}
