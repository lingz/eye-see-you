#ifndef CIRC_ARRAY
#define CIRC_ARRAY
#include "PupilsFrame.h"

class CircularArray {
    private:
        const static int TOTAL_FACES = 60;
        int oldestData;
        PupilFrame frames[TOTAL_FACES];
    
    public:
        CircularArray() {oldestData=0;} 
        void addData(PupilFrame);
        PupilFrame& getFrameAt(int);
};
#endif
