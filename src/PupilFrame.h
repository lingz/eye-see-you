#include "Eyes.h"

class PupilFrame {
  public;
    int numPupils;
    bool hasLeftPupil;
    bool hasRightPupil;
    int leftPupilX;
    int leftPupilY;
    int leftPupilAbsX;
    int leftPupilAbsY;
    int rightPupilX;
    int rightPupilAbsX;
    int rightPupily;
    int rightPupilAbsY;
    PupilFrame(const Eyes &eyes);
}
