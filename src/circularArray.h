#include "PupilFrame.h"

class CircularArray {
    private:
        const static int TOTAL_FACES = 60;
        int oldestData;
        PupilFrame frame[TOTAL_FACES];
    
    public:
        CircularArray() {oldestData=0;};
        void addData(PupilFrame);
        PupilFrame getFrameAt(int);
};
