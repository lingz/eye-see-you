#include "PupilsFrame.h"
#include "EyesFrame.h"
#include "findEyeCenter.h"

#include <iostream>

PupilFrame::PupilFrame(const EyesFrame &eyes, const cv::Rect &face, cv::Mat &faceROI) {
  cv::Point leftPupil;
  cv::Point rightPupil;

  hasLeftPupil = eyes.hasLeftEye;
  hasRightPupil = eyes.hasRightEye;
  numPupils = eyes.numEyes;

  if (hasLeftPupil) {
    leftPupil = findEyeCenter(faceROI, eyes.leftEye, "Left Eye");
    leftPupilX = leftPupil.x - eyes.leftEye.width / 2;
    leftPupilAbsX = leftPupil.x + eyes.leftEye.x + face.x;
    leftPupilY = leftPupil.y - eyes.leftEye.height / 2;
    leftPupilAbsY = leftPupil.y + eyes.leftEye.y + face.y;
  }

  if (hasRightPupil) {
    rightPupil = findEyeCenter(faceROI, eyes.rightEye, "Right Eye");
    rightPupilX = rightPupil.x - eyes.rightEye.width / 2;
    rightPupilAbsX = rightPupil.x + eyes.rightEye.x + face.x;
    rightPupilY = rightPupil.y - eyes.rightEye.height / 2;
    rightPupilAbsY = rightPupil.y + eyes.rightEye.y + face.y;
  }

}
