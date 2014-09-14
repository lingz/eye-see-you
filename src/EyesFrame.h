#ifndef EYES_H
#define EYES_H

#include "opencv2/imgproc/imgproc.hpp"

class EyesFrame {
  public:
    cv::Rect leftEye;
    cv::Rect rightEye;
    int numEyes;
    bool hasLeftEye;
    bool hasRightEye;
    EyesFrame(cv::Mat &face);
  private:
    static void initialize();
};

#endif
