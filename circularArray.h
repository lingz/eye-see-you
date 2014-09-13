#include "faceData.h"

class CircularArray {
    private:
        const static int TOTAL_FACES = 60;
        int oldestData;
        FaceData faces[TOTAL_FACES];
    
    public:
        CircularArray();
        void addData(FaceData);
        FaceData getValueAt(int);
};
