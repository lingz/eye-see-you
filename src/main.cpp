#include <opencv2/objdetect/objdetect.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

#include <iostream>
#include <queue>
#include <stdio.h>
#include <math.h>

#include "constants.h"
#include "EyesFrame.h"
#include "PupilsFrame.h"

/** Constants **/

/** Function Headers */
void detectAndDisplay( cv::Mat frame );

/** Global variables */
//-- Note, either copy these two files from opencv/data/haarscascades to your current folder, or change these locations
cv::CascadeClassifier face_cascade;
std::string main_window_name = "Capture - Face detection";
std::string face_window_name = "Capture - Face";
cv::RNG rng(12345);
cv::Mat debugImage;
cv::Mat skinCrCbHist = cv::Mat::zeros(cv::Size(256, 256), CV_8UC1);

enum Mode {NORMAL, DEBUG, PLOT};
Mode mode;

/*
 * @function main
 */
int main( int argc, const char** argv ) {

  // Get the mode
  if (argc > 1)
  {
    const char *inputMode = argv[1];
    printf("%s", inputMode);
    if (strcmp(inputMode, "normal") == 0) {
      mode = NORMAL;
    } else if (strcmp(inputMode, "debug") == 0) {
      mode = DEBUG;
    } else if (strcmp(inputMode, "plot") == 0) {
      mode = PLOT;
    } else {
      mode = NORMAL;
    }
  }
  else
  {
    mode = NORMAL;
  }

  printf("Input Mode: %s\n", mode == NORMAL ? "normal" :
      mode == DEBUG ? "debug" :
      mode == PLOT ? "plot" : "none");

  cv::Mat frame;

  // Load the cascades
  if( !face_cascade.load( FACE_CASCADE_FILE ) ){ printf("--(!)Error loading face cascade, please change face_cascade_name in source code.\n"); return -1; };

  cv::namedWindow(main_window_name,CV_WINDOW_NORMAL);
  cv::moveWindow(main_window_name, 400, 100);
  cv::namedWindow(face_window_name,CV_WINDOW_NORMAL);
  cv::moveWindow(face_window_name, 10, 100);
  cv::namedWindow("Right Eye",CV_WINDOW_NORMAL);
  cv::moveWindow("Right Eye", 10, 600);
  cv::namedWindow("Left Eye",CV_WINDOW_NORMAL);
  cv::moveWindow("Left Eye", 10, 800);
  cv::namedWindow("aa",CV_WINDOW_NORMAL);
  cv::moveWindow("aa", 10, 800);
  cv::namedWindow("aaa",CV_WINDOW_NORMAL);
  cv::moveWindow("aaa", 10, 800);

  ellipse(skinCrCbHist, cv::Point(113, 155.6), cv::Size(23.4, 15.2),
          43.0, 0.0, 360.0, cv::Scalar(255, 255, 255), -1);

   // Read the video stream
  cv::VideoCapture capture( 0 );
  if( capture.isOpened() ) {
    capture.set(CV_CAP_PROP_FRAME_WIDTH, 640);
    capture.set(CV_CAP_PROP_FRAME_HEIGHT, 480);
    while( true ) {
      capture >> frame;

      // mirror it
      cv::flip(frame, frame, 1);
      frame.copyTo(debugImage);

      // Apply the classifier to the frame
      if( !frame.empty() ) {
        detectAndDisplay( frame );
      }
      else {
        printf(" --(!) No captured frame -- Break!");
        break;
      }

      imshow(main_window_name,debugImage);

      int c = cv::waitKey(10);
      if( (char)c == 'c' ) { break; }
      if( (char)c == 'f' ) {
        imwrite("frame.png",frame);
      }

    }
  }

  return 0;
}

void processFrame(cv::Mat frame_gray, cv::Rect face) {
  // functor that selects the face region inside the frame
  cv::Mat faceROI = frame_gray(face);
  cv::Mat debugFace = faceROI;

  // smoothing
  if (kSmoothFaceImage) {
    double sigma = kSmoothFaceFactor * face.width;
    GaussianBlur( faceROI, faceROI, cv::Size( 0, 0 ), sigma);
  }

  // haart detection on faces to find eyes
  EyesFrame eyes(faceROI);
  // haart detection on eyes to find pupils
  PupilFrame pupils(eyes, face, faceROI);

  if (mode == DEBUG) {
    switch (eyes.numEyes) {
      case 0:
        printf("-,-;\n");
        break;
      case 1:
        printf("%s,%s; <X: %d, Y: %d>\n",
          eyes.hasLeftEye ? "1" : "-",
          eyes.hasRightEye ? "1" : "-", 
          eyes.hasLeftEye ? pupils.leftPupilX : pupils.rightPupilX,
          eyes.hasLeftEye ? pupils.leftPupilY : pupils.rightPupilY);
        break;
      default:
        printf("1,1; <X: %d, Y: %d>; R: <X: %d, Y: %d>;\n",
          pupils.leftPupilX,
          pupils.leftPupilY,
          pupils.rightPupilX,
          pupils.rightPupilY);
        break;
    }
    if (pupils.hasLeftPupil) {
      cv::Point leftPupil(pupils.leftPupilAbsX - face.x, pupils.leftPupilAbsY - face.y);
      circle(debugFace, leftPupil, 3, 1234);
    }
    if (pupils.hasRightPupil) {
      cv::Point rightPupil(pupils.rightPupilAbsX - face.x, pupils.rightPupilAbsY - face.y);
      circle(debugFace, rightPupil, 3, 1234);
    }
  } else if (mode == PLOT) {
    switch (eyes.numEyes) {
      case 0:
        printf("0,0,0,0\n");
        break;
      case 1:
        printf("%s,%s; <X: %d, Y: %d>\n",
          eyes.hasLeftEye ? "1" : "-",
          eyes.hasRightEye ? "1" : "-", 
          eyes.hasLeftEye ? eyes.leftEye.x : eyes.rightEye.x,
          eyes.hasLeftEye ? eyes.leftEye.y : eyes.rightEye.y);
      default:
        printf("1,1; <X: %d, Y: %d>; R: <X: %d, Y: %d>;\n",
          eyes.leftEye.x,
          eyes.leftEye.y,
          eyes.rightEye.x,
          eyes.rightEye.y);
    }
  }

  imshow(face_window_name, faceROI);
}

/**
 * @function detectAndDisplay
 */
void detectAndDisplay( cv::Mat frame ) {
  std::vector<cv::Rect> faces;
  //cv::Mat frame_gray;

  //TODO: proper greyscale?
  std::vector<cv::Mat> rgbChannels(3);
  cv::split(frame, rgbChannels);
  cv::Mat frame_gray = rgbChannels[2];

  //-- Detect faces
  face_cascade.detectMultiScale( frame_gray, faces, 1.1, 2, 0|CV_HAAR_SCALE_IMAGE|CV_HAAR_FIND_BIGGEST_OBJECT, cv::Size(150, 150) );

  for( int i = 0; i < faces.size(); i++ )
  {
    rectangle(debugImage, faces[i], cv::Scalar(125, 125, 125, 125));
  }
  //-- Show what you got
  if (faces.size() > 0) {
    processFrame(frame_gray, faces[0]);
  }
}
