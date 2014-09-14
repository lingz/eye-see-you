#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "faceData.h"
#include "circularArray.h"

class FaceData;

void CircularArray::addData(FaceData fd){
    faces[oldestData] = fd;
    oldestData++;
    if(oldestData >= TOTAL_FACES) oldestData = 0;
}

FaceData CircularArray::getValueAt(int offset){
    offset = abs(offset - 1) % TOTAL_FACES;
    int index = oldestData - offset;
    if(index < 0){
        return faces[index + TOTAL_FACES];
    }
    else{
        return faces[index];
    }
}
/*
int main () {
	CircularArray * circ = new CircularArray();
    	circ->addData(FaceData(10, 10, 10, 10));
	circ->addData(FaceData(10, 10, 10, 10));
	circ->addData(FaceData(1, 10, 10, 10));
	circ->addData(FaceData(10, 10, 10, 10));
	circ->addData(FaceData(10, 1, 10, 10));
	circ->addData(FaceData(10, 10, 10, 10));
	circ->addData(FaceData(10, 10, 10, 10));
	circ->addData(FaceData(10, 10, 10, 10));
	circ->addData(FaceData(10, 10, 10, 10));
	circ->addData(FaceData(10, 10, 10, 10));
	circ->addData(FaceData(10, 10, 10, 10));
	circ->addData(FaceData(10, 10, 10, 10));
	circ->addData(FaceData(10, 10, 10, 10));
	circ->addData(FaceData(10, 10, 10, 10));
	circ->addData(FaceData(10, 10, 10, 10));
	circ->addData(FaceData(10, 10, 10, 10));
	circ->addData(FaceData(10, 10, 10, 10));
	circ->addData(FaceData(10, 10, 10, 10));
	circ->addData(FaceData(9, 9, 9, 9));
    	FaceData fd = circ->getValueAt(0);
    	printf("lx is %f", fd.getlX());
	return 0;
}
*/
