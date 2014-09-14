#include "opencv2/objdetect/objdetect.hpp"
#include "constants.h"
#include "stdio.h"

#include "EyesFrame.h"

cv::CascadeClassifier eye_cascade;
bool hasInitialized = false;

void EyesFrame::initialize() {
  if (!hasInitialized) {
    eye_cascade.load(EYE_CASCADE_FILE);
    if( !eye_cascade.load( EYE_CASCADE_FILE ) ){
      printf("--(!)Error loading face cascade, please change EYE_CASCADE_FILE in the consants source code.\n");
      exit(-1);
    };
    hasInitialized = true;
  }
}

EyesFrame::EyesFrame(cv::Mat &face) {
  if (!hasInitialized) {
    initialize();
  }

  std::vector<cv::Rect> eyesVector;

  eye_cascade.detectMultiScale(face,
      eyesVector, 1.1, 2, 0|CV_HAAR_SCALE_IMAGE,
      cv::Size(30, 30));

  numEyes = eyesVector.size();

  cv::Rect eye0;
  cv::Rect eye1;

  switch (numEyes) {
    case 0:
      hasLeftEye = false;
      hasRightEye = false;
      break;
    case 1:
      // whether the eye is left or right is not trustworthy
      // just using a simple heuristic here
      eye0 = eyesVector[0];
      if (eye0.x + (eye0.width / 2) < face.cols / 2) {
        hasLeftEye = true;
        hasRightEye = false;
        leftEye = eye0;
      } else {
        hasLeftEye = false;
        hasRightEye = true;
        rightEye = eye0;
      }
      break;
    default:
      hasLeftEye = true;
      hasRightEye = true;
      eye0 = eyesVector[0];
      eye1 = eyesVector[1];

      if (eye0.x < eye1.x) {
        leftEye = eye0;
        rightEye = eye1;
      } else {
        leftEye = eye1;
        rightEye = eye0;
      }
      break;
  }
}
