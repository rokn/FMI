#include <iostream>
#include <cmath>
#include <limits>
#include "UI.hpp"
using namespace std;

const double EPS = 10e-6;
const int COORDS_SIZE = 4;
const int WALLS = 4;
const int MAX_MIRRORS = 10 + WALLS;
const int INPUTS = 11;
const int MAX_INPUT_SIZE = INPUTS + MAX_MIRRORS * COORDS_SIZE;
const int INPUT_WIDTH = 0,
	  	  INPUT_HEIGHT = 1,
	  	  INPUT_TARGET_X = 2,
	  	  INPUT_TARGET_Y = 3,
	  	  INPUT_TARGET_RADIUS = 4,
	  	  INPUT_START_X = 5,
	  	  INPUT_START_Y = 6,
	  	  INPUT_DIRECTION_X = 7,
	  	  INPUT_DIRECTION_Y = 8,
	  	  INPUT_MAX_REFLECTIONS = 9,
	  	  INPUT_MIRROR_COUNT = 10,
	  	  INPUT_MIRROR_COORDS = 11;

typedef struct {
	double x;
	double y;
} Vector2;

typedef struct {
	Vector2 start;
	Vector2 end;
} Mirror;

typedef struct {
	Vector2 origin;
	Vector2 direction;
} Ray;

typedef struct {
	double A;
	double B;
	double C;
} Line;

typedef struct {
	Vector2 center;
	double radius;
} Circle;

typedef struct {
	Vector2 point;
	double rayParam;
	bool exists;
} Intersection;

typedef struct {
	Circle target;
	Ray currentRay;
	int reflectionsLeft;
	int mirrorCount;
	Mirror mirrors[MAX_MIRRORS];
} State;


void readInput(State& state);
void run(State& state);
Intersection getIntersection(const Ray& ray, const Mirror& mirror);
Intersection getIntersection(const Line& line1, const Line& line2);
Intersection getIntersection(const Ray& ray, const Circle& circle);
Line getLine(const Vector2& a, const Vector2& b);
Line getPerpendicular(const Line& toLine, const Vector2& throughPoint);
bool isEq(double a, double b);

int main() {
	State state;
	readInput(state);
	run(state);
	return 0;
}

void run(State& state) {
	int prevMirror = -1;
	while(state.reflectionsLeft) {
		Intersection intersection, current;
		Ray currentRay = state.currentRay;
		intersection.rayParam = numeric_limits<double>::infinity();
		int mirrorIndex;

		for(int i = 0; i < state.mirrorCount; ++i) {
            if(prevMirror == i) {
				continue;
			}
			current = getIntersection(currentRay, state.mirrors[i]);
			if(current.exists && current.rayParam < intersection.rayParam) {
				intersection = current;
				mirrorIndex = i;
			}
		}

		// Couldn't find why the determinant was almost always negative even when hitting the circle :/
		// current = getIntersection(currentRay, state.target);
		// if(current.exists && current.rayParam < intersection.rayParam) {
		// 	SetRaySegment(currentRay.origin.x, currentRay.origin.y,
		// 					intersection.point.x, intersection.point.y);
		// 	break;
		// }

		SetRaySegment(currentRay.origin.x, currentRay.origin.y,
						intersection.point.x, intersection.point.y);

		Mirror mirror = state.mirrors[mirrorIndex];

		Line mirrorLine = getLine(mirror.start, mirror.end);

		Line reflectionLine = getPerpendicular(mirrorLine, intersection.point);

		Line symmetryLine = getPerpendicular(reflectionLine, currentRay.origin);

		Intersection midIntersect = getIntersection(reflectionLine, symmetryLine);

		Vector2 newDirection;
		newDirection.x = 2*midIntersect.point.x - currentRay.origin.x;
		newDirection.y = 2*midIntersect.point.y - currentRay.origin.y;

		state.currentRay.origin = intersection.point;
		state.currentRay.direction = newDirection;

		state.reflectionsLeft--;
		prevMirror = mirrorIndex;
	}
}

Line getLine(const Vector2& a, const Vector2& b) {
	//Calculate coefecients
	Line line;
	line.A = a.y - b.y;
	line.B = b.x - a.x;
	line.C = a.x * b.y - a.y * b.x;
	return line;
}

Line getPerpendicular(const Line& toLine, const Vector2& throughPoint) {
	Line perpLine;
	perpLine.A = -toLine.B;
	perpLine.B = toLine.A;
	perpLine.C = -perpLine.A * throughPoint.x - perpLine.B * throughPoint.y;
	return perpLine;
}

Intersection getIntersection(const Ray& ray, const Mirror& mirror) {
	Line mirrorLine = getLine(mirror.start, mirror.end);
	Line rayLine = getLine(ray.origin, ray.direction);

	//Check for validity with mirror param and ray param
	Intersection intersection = getIntersection(mirrorLine, rayLine);
	double mirrorParam, rayParam;
	if(!isEq(mirror.start.x, mirror.end.x)) {
		mirrorParam = (mirror.start.x - intersection.point.x) /
					  (mirror.start.x - mirror.end.x);
	} else {
		mirrorParam = (mirror.start.y - intersection.point.y) /
					  (mirror.start.y - mirror.end.y);
	}
	if(!isEq(ray.origin.x, ray.direction.x)) {
		rayParam = (ray.origin.x - intersection.point.x) /
						  (ray.origin.x - ray.direction.x);
	} else {
		rayParam = (ray.origin.y - intersection.point.y) /
						  (ray.origin.y - ray.direction.y);
	}

	bool mirrorValidity = mirrorParam >= 0 && mirrorParam <= 1;
	bool rayValidity = rayParam >= 0;

	intersection.exists = mirrorValidity && rayValidity;
	intersection.rayParam = rayParam;

	return intersection;
}

Intersection getIntersection(const Ray& ray, const Circle& circle) {
	Vector2 d, f;
	double x1,x2,y1,y2,cx,cy, R;
	x1 = ray.origin.x;
	y1 = ray.origin.y;
	x2 = ray.direction.x;
	y2 = ray.direction.y;
	cx = circle.center.x;
	cy = circle.center.y;
	R = circle.radius;

	d.x = x2-x1;
	d.y = y2-y1;

	f.x = x1-cx;
	f.y = y1-cy;

	double aCoef, bCoef, cCoef;

	aCoef = d.x*d.x + d.y*d.y;
	bCoef = f.x*d.x + f.y*d.y;
	cCoef = f.x*f.x + f.y*f.y - R*R;

	double determinant = bCoef*bCoef - aCoef*cCoef;

	Intersection intersection;
	intersection.exists = determinant >= 0.0;


	if(intersection.exists) {
		double param;
		if(isEq(determinant, 0.0)) {
			param = (-bCoef) / aCoef;
		} else {
			double p1, p2;
			p1 = (-bCoef + sqrt(determinant)) / aCoef;
			p2 = (-bCoef - sqrt(determinant)) / aCoef;
			param = p1 < p2 ? p1 : p2;
		}

		intersection.rayParam = param;
		intersection.point.x = ray.origin.x + param*(ray.direction.x - ray.origin.x);
		intersection.point.y = ray.origin.y + param*(ray.direction.y - ray.origin.y);
	}

	return intersection;
}

Intersection getIntersection(const Line& line1, const Line& line2) {
	Intersection intersection;
	//Kramer rule
	double delta = line1.A*line2.B - line1.B*line2.A;
	if(isEq(delta, 0)) {
		// If the main delta is zero the ray is colinear to the mirror,
		// so no intesection
		intersection.exists = false;
		return intersection;
	}
	double delta1 = line1.B * line2.C - line1.C * line2.B;
	double delta2 = line1.C * line2.A - line2.C * line1.A;

	intersection.point.x = delta1 / delta;
	intersection.point.y = delta2 / delta;
	return intersection;
}

void readInput(State& state) {
	double input[MAX_INPUT_SIZE];
	GetInput(input);
	double width                 = input[INPUT_WIDTH];
	double height                = input[INPUT_HEIGHT];
	state.target.center.x        = input[INPUT_TARGET_X];
	state.target.center.y        = input[INPUT_TARGET_Y];
	state.target.radius          = input[INPUT_TARGET_RADIUS] = 4,
	state.currentRay.origin.x    = input[INPUT_START_X];
	state.currentRay.origin.y    = input[INPUT_START_Y];
	state.currentRay.direction.x = input[INPUT_DIRECTION_X];
	state.currentRay.direction.y = input[INPUT_DIRECTION_Y];
	state.reflectionsLeft        = input[INPUT_MAX_REFLECTIONS];
	state.mirrorCount            = input[INPUT_MIRROR_COUNT];

	int i;
	int cIndex;
	for(i = 0; i < state.mirrorCount; ++i) {
		cIndex = i * COORDS_SIZE;
		state.mirrors[i].start.x = input[INPUT_MIRROR_COORDS + cIndex  ];
		state.mirrors[i].start.y = input[INPUT_MIRROR_COORDS + cIndex+1];
		state.mirrors[i].end.x   = input[INPUT_MIRROR_COORDS + cIndex+2];
		state.mirrors[i].end.y   = input[INPUT_MIRROR_COORDS + cIndex+3];
	}

	//Top Wall
	state.mirrors[i].start.x = 0;
	state.mirrors[i].start.y = 0;
	state.mirrors[i].end.x   = width;
	state.mirrors[i].end.y   = 0;

	//Right Wall
	i++;
	state.mirrors[i].start.x = width;
	state.mirrors[i].start.y = 0;
	state.mirrors[i].end.x   = width;
	state.mirrors[i].end.y   = height;

	//Left Wall
	i++;
	state.mirrors[i].start.x = 0;
	state.mirrors[i].start.y = 0;
	state.mirrors[i].end.x   = 0;
	state.mirrors[i].end.y   = height;

	//Bottom Wall
	i++;
	state.mirrors[i].start.x = 0;
	state.mirrors[i].start.y = height;
	state.mirrors[i].end.x   = width;
	state.mirrors[i].end.y   = height;

	state.mirrorCount += WALLS;
}

bool isEq(double a, double b) {
	return abs(a - b) < EPS;
}