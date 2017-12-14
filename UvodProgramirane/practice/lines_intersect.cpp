#include <iostream>
using namespace std;

double calculateDeterminant(double a, double b, double c, double d) {
	//Calculate a 2x2 determinant like this:
	// |a b|
	// |c d|   -> a*d - b*c
	return a*d - b*c;
}

int main() {
	double A1, B1, C1, // Variables for line coeffecients
		   A2, B2, C2;

	double delta, deltaX, deltaY; // Kramer deltas

	//Input
	cout << "Input line 1 coeffecients: " << endl;
	cin >> A1 >> B1 >> C1;
	cout << "Input line 2 coeffecients: " << endl;
	cin >> A2 >> B2 >> C2;

	if(A1 == A2 && B1 == B2) { // If the lines are colinear
		if (C1 == C2) { // If the lines are the same
			cout << "Same lines." << endl;
		} else { // If just the last coef. is different the lines are parallel
			cout << "Parallel lines." << endl;
		}

		// If the lines are the same or parallel 
		// there is no need to check for intersection so we quit the program.
		return 0;
	}

	//Calculate intersection with Kramer determinants

	//Caluclate the common determinant:
	//|A1 B1|
	//|A2 B2|
	delta = calculateDeterminant(A1, B1, A2, B2);

	//Caluclate the determinant with X coeffecients:
	//|A1 -C1|
	//|A2 -C2|
	deltaX = calculateDeterminant(A1, -C1, A2, -C2);

	//Caluclate the determinant with Y coeffecients:
	//|-C1 B1|
	//|-C2 B2|
	deltaY = calculateDeterminant(-C1, B1, -C2, B2);

	//The x intersect is caluclated like:
	double xIntersection = deltaY/delta;

	//The y intersect is caluclated like:
	double yIntersection = deltaX/delta;

	cout << "The lines intersect at: (" << xIntersection << ", " << yIntersection << ")." << endl;
	return 0;
}
