#ifndef PUPIL_FRAME_H
#define PUPIL_FRAME_H

#include "EyesFrame.h"
#include "EventState.h"

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
    EventState state;
    PupilFrame();
    PupilFrame(const EyesFrame &eyes, const cv::Rect &face, cv::Mat &faceROI);
};
#endif
