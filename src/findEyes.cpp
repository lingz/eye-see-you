#include "opencv2/objdetect/objdetect.hpp"
#include "constants.h"
#include "stdio.h"

#include "findEyes.h"

cv::CascadeClassifier eye_cascade;
bool hasInitialized = false;

void initialize() {
  if (!hasInitialized) {
    eye_cascade.load(EYE_CASCADE_FILE);
    if( !eye_cascade.load( EYE_CASCADE_FILE ) ){
      printf("--(!)Error loading face cascade, please change EYE_CASCADE_FILE in the consants source code.\n");
      exit(-1);
    };
    hasInitialized = true;
  }
}

void findEyes(cv::Mat face, Eyes &eyes) {
  if (!hasInitialized) {
    initialize();
  }

  std::vector<cv::Rect> eyesVector;

  eye_cascade.detectMultiScale(face,
      eyesVector, 1.1, 2, 0|CV_HAAR_SCALE_IMAGE,
      cv::Size(30, 30));

  int numEyes = eyesVector.size();
  cv::Rect leftEye;
  cv::Rect rightEye;
  cv::Rect eye0;
  cv::Rect eye1;

  switch (numEyes) {
    case 0:
      eyes = (Eyes) {cv::Rect(), cv::Rect(), 0, false, false};
      break;
    case 1:
      // whether the eye is left or right is not trustworthy
      // just using a simple heuristic here
      eye0 = eyesVector[0];
      if (eye0.x < face.cols / 2) {
        eyes = (Eyes) {eye0, cv::Rect(), 1, true, false};
      } else {
        eyes = (Eyes) {cv::Rect(), eye0, 1, false, true};
      }
      break;
    default:
      eye0 = eyesVector[0];
      eye1 = eyesVector[1];
      if (eye0.x < eye1.x) {
        eyes = (Eyes) {eye0, eye1, 2, true, true};
      } else {
        eyes = (Eyes) {eye1, eye0, 2, true, true};
      }
      break;
  }
}
