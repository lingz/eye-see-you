class CircularArray {
	int l;
};

#include <iostream>
#include <stdio.h>
#include <stdlib.h>

void CircularArray::initializeArray (int l) {
	currentPosition = -1;
	effectiveSize = 0;
	x1 = (double*) malloc(l*sizeof(double);
	x2 = (double*) malloc(l*sizeof(double);
	y1 = (double*) malloc(l*sizeof(double);
	y2 = (double*) malloc(l*sizeof(double);
}

void CircularArray::destroyArray () {
	if(x1 != NULL)
		free(x1);
	if(x2 != NULL)
		free(x2);
	if(y1 != NULL)
		free(y1);
	if(y2 != NULL)
		free(y2);
}

void CircularArray::addPoints(double x1Add, double y1Add, double x2Add, double y2Add) {
	currentPosition++;

	if(effectiveSize < length) {
		effectiveSize++;
	}

	if(currentPosition >= length) {
			currentPosition = 0;
	}

	x1[currentPosition] = x1Add;
	y1[currentPosition] = y1Add;
	x2[currentPosition] = x2Add;
	y2[currentPosition] = y2Add;		
}

void CircularArray::getValuesAt(int timeBeforeSpot, void (*function)(const double, const double, const double, const double)) {
	if(currentPosition == -1)
		return;

	int positionWanted = currentPosition - timeBeforeSpot;

	if(positionWanted < 0 && effectiveSize != length) {
		return;
	}

	if(positionWanted < 0 && effectiveSize == length) {
		positionWanted += length;
	} else if (positionWanted >= length) {
		positionWanted -= length;
	}

	function(x1[positionWanted], y1[positionWanted], x2[positionWanted], y2[positionWanted]);

}

void printPoints(const double x1, const double y1, const double x2, const double y2) {
	printf("%f %f %f %f \n", x1, y1, x2, y2);
}

int main () {
	CircularArray circ (10);
	circ.addPoints(10, 10, 10, 10);
	circ.addPoints(1, 10, 10, 10);
	circ.addPoints(10, 10, 10, 10);
	circ.addPoints(10, 1, 10, 10);
	circ.addPoints(10, 10, 10, 10);
	circ.addPoints(10, 10, 10, 10);
	circ.addPoints(10, 10, 10, 10);
	circ.addPoints(10, 10, 10, 10);
	circ.addPoints(10, 10, 10, 10);
	circ.addPoints(10, 10, 10, 10);
	circ.addPoints(10, 10, 10, 10);
	circ.addPoints(10, 10, 10, 10);
	circ.addPoints(10, 10, 10, 10);
	circ.addPoints(10, 10, 10, 10);
	circ.addPoints(10, 10, 10, 10);
	circ.addPoints(10, 10, 10, 10);
	circ.addPoints(10, 10, 10, 10);
	circ.addPoints(9, 9, 9, 9);
	circ.getValuesAt(0, printPoints);
	circ.getValuesAt(9, printPoints);
	return 0;
}
