#include "Bitmap.h"
#include <iostream>

typedef unsigned int uint;

void cropImage(struct image_t& image);
uint getColor(uint combined, uint colorPosition);
uint colorAt(uint x, uint y, struct image_t& image);
void setColor(uint x, uint y, uint color, uint width, struct image_t& image);
bool isDirty(uint color, uint targetColor, uint proximity);
uint getFirstDirtyHorizontal(uint startY, uint step, struct image_t& image);
uint getFirstDirtyVertical(uint startX, uint step, struct image_t& image);
void printError(int error);

const uint STEP_FORWARD = 1;
const uint STEP_BACKWARD = -1;

const uint COLOR_MASK = 0xFF;
const uint BLUE = 0;
const uint GREEN = 1;
const uint RED = 2;
const uint MAX_DISTANCE = 0xFF * 0xFF * 3; // Distance between black and white

const size_t MAX_SIZE = 100000;

struct image_t {
	uint width;
	uint height;
	uint cropColor;
	uint cropProximity;
	uint colors[MAX_SIZE];
};

int main()
{
	struct image_t image;

	int rval;

	rval = LoadBitmap("input.bmp", image.colors, MAX_SIZE, image.width, image.height);

	if (rval != ALL_OK)
	{
		printError(rval);
		return 1;
	}

	std::cout << "Enter crop color:" << std::endl;
	std::cin >> image.cropColor;
	std::cout << "Enter color proximity:" << std::endl;
	std::cin >> image.cropProximity;

	cropImage(image);

	rval = SaveBitmap("result.bmp", image.colors, image.width, image.height);

	if (rval != ALL_OK)
	{
		printError(rval);
		return 2;
	}

	return 0;
}

void cropImage(struct image_t& image) {
	uint endX = getFirstDirtyVertical(image.width-1, STEP_BACKWARD, image);
	uint endY = 0;
	uint startX = 0;
	uint startY = 0;

	// If the image has no dirty pixels we don't need to traverse it 4 times
	if(endX > 0) {
		endY = getFirstDirtyHorizontal(image.height-1, STEP_BACKWARD, image);
		startX = getFirstDirtyVertical(0, STEP_FORWARD, image);
		startY = getFirstDirtyHorizontal(0, STEP_FORWARD, image);
	}

	uint newWidth = endX - startX + 1;
	uint newHeight = endY - startY + 1;

	for(uint y = 0; y < newHeight; ++y) {
		for(uint x = 0; x < newWidth; ++x) {
			uint color = colorAt(startX + x, startY + y, image);
			setColor(x, y, color, newWidth, image);
		}
	}
	image.width = newWidth;
	image.height = newHeight;
}

uint colorAt(uint x, uint y, struct image_t& image) {
	return image.colors[y*image.width + x];
}

void setColor(uint x, uint y, uint color, uint width, struct image_t& image) {
	image.colors[y*width + x] = color;
}

bool isDirty(uint color, uint targetColor, uint proximity) {
	uint rDiff = getColor(color, RED) - getColor(targetColor, RED);
	uint gDiff = getColor(color, GREEN) - getColor(targetColor, GREEN);
	uint bDiff = getColor(color, BLUE) - getColor(targetColor, BLUE);
	rDiff *= rDiff;
	gDiff *= gDiff;
	bDiff *= bDiff;

	uint diff = rDiff + gDiff + bDiff;
	float percentage = ((float)diff / MAX_DISTANCE) * 100;
	return percentage > proximity;
}

uint getFirstDirtyHorizontal(uint startY, uint step, struct image_t& image) {
	for(uint y = startY; y >= 0 && y < image.height; y += step) {
		for(uint x = 0; x < image.width; ++x) {
			uint currColor = colorAt(x, y, image);
			if(isDirty(currColor, image.cropColor, image.cropProximity)) {
				return y;
			}
		}
	}

	return 0;
}

uint getFirstDirtyVertical(uint startX, uint step, struct image_t& image) {
	for(uint x = startX; x >= 0 && x < image.width; x += step) {
		for(uint y = 0; y < image.height; ++y) {
			uint currColor = colorAt(x, y, image);
			if(isDirty(currColor, image.cropColor, image.cropProximity)) {
				return x;
			}
		}
	}

	return 0;
}

uint getColor(uint combined, uint colorPosition) {
	return (combined >> colorPosition) & COLOR_MASK;
}

void printError(int error) {
	std::cerr << "An error occured: ";
	switch(error){
		case ERR_CANNOT_OPEN_FILE:
			std::cerr << "File not found!" << std::endl;
			break;
		case ERR_WRONG_FILE_TYPE:
			std::cerr << "Wrong file type!" << std::endl;
			break;
		case ERR_BUFFER_TOO_SMALL:
			std::cerr << "Image too big!" << std::endl;
			break;
		case ERR_FILE_READ_ERROR:
			std::cerr << "Couldn't read file!" << std::endl;
			break;
		case ERR_CANNOT_ALLOCATE_MEMORY:
			std::cerr << "Couldn't allocate memory!" << std::endl;
			break;
		case ERR_ZERO_SIZE:
			std::cerr << "Image can't be with 0 size!" << std::endl;
			break;
		default:
			std::cerr << "Something happened. :)" << std::endl;
	}
}
