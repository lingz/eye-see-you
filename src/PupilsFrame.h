#ifndef PUPIL_FRAME_H
#define PUPIL_FRAME_H

#include "EyesFrame.h"

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
    PupilFrame();
    PupilFrame(const EyesFrame &eyes, const cv::Rect &face, cv::Mat &faceROI);
};
#endif
