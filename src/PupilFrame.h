#ifndef PUPIL_FRAME_H
#define PUPIL_FRAME_H

#include "Eyes.h"

class PupilFrame {
  public:
    int numPupils;
    bool hasLeftPupil;
    bool hasRightPupil;
    int leftPupilX;
    int leftPupilY;
    int leftPupilAbsX;
    int leftPupilAbsY;
    int rightPupilX;
    int rightPupilAbsX;
    int rightPupilY;
    int rightPupilAbsY;
    PupilFrame(const Eyes &eyes, const cv::Rect &face, cv::Mat &faceROI);
};
#endif
