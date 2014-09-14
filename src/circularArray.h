#ifndef CIRC_ARRAY
#define CIRC_ARRAY
#include "PupilsFrame.h"

class CircularArray {
    private:
        const static int TOTAL_FACES = 180;
        int oldestData;
        PupilsFrame frames[TOTAL_FACES];
    
    public:
        CircularArray() {oldestData=0;} 
        void addData(PupilsFrame);
        PupilsFrame& getFrameAt(int);
};
#endif
