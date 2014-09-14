#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "PupilsFrame.h"
#include "circularArray.h"

void CircularArray::addData(PupilFrame frame){
    frames[oldestData] = frame;
    oldestData++;
    if(oldestData >= TOTAL_FACES) oldestData = 0;
}

PupilFrame & CircularArray::getFrameAt(int offset){
    offset = abs(offset - 1) % TOTAL_FACES;
    int index = oldestData - offset;
    if(index < 0){
        return frames[index + TOTAL_FACES];
    }
    else{
        return frames[index];
    }
}

/*
int main () {
	CircularArray * circ = new CircularArray();
    circ->addData(PupilFrame());
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
