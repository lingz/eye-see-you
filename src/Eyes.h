#ifndef EYES_H
#define EYES_H

#include "opencv2/imgproc/imgproc.hpp"

struct Eyes {
  cv::Rect leftEye;
  cv::Rect rightEye;
  int numEyes;
  bool hasLeftEye;
  bool hasRightEye;
};

#endif
