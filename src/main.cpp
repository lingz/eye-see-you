#include <opencv2/objdetect/objdetect.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

#include <iostream>
#include <queue>
#include <stdio.h>
#include <math.h>

#include "constants.h"
#include "findEyeCenter.h"
#include "findEyes.h"


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

/**
 * @function main
 */
int main( int argc, const char** argv ) {
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

void findEyes(cv::Mat frame_gray, cv::Rect face) {
  // functor that selects the face region inside the frame
  cv::Mat faceROI = frame_gray(face);
  cv::Mat debugFace = faceROI;

  if (kSmoothFaceImage) {
    double sigma = kSmoothFaceFactor * face.width;
    GaussianBlur( faceROI, faceROI, cv::Size( 0, 0 ), sigma);
  }

  // TODO: Change this later to use actual eye deteciton algorithm?

  //-- Find eye regions and draw them
  
  // percentage of the face that eyes cover
  //int eye_region_width = face.width * (kEyePercentWidth/100.0);
  //int eye_region_height = face.width * (kEyePercentHeight/100.0);

  // distance from top of face to the start of the eye
  //int eye_region_top = face.height * (kEyePercentTop/100.0);
  // distance from left of face to the start of the eye
  //int eye_region_side = face.width * (kEyePercentSide / 100.0);
  
  // create the rectangles around the eyes in the face
  //cv::Rect leftEyeRegion(eye_region_side,
                         //eye_region_top,eye_region_width,eye_region_height);
  //cv::Rect rightEyeRegion(face.width - eye_region_width - eye_region_side,
                          //eye_region_top,eye_region_width,eye_region_height);
                      

  Eyes eyes;
  findEyes(faceROI, eyes);

  cv::Point leftPupil;
  cv::Point rightPupil;
  if (eyes.hasLeftEye) {
    leftPupil = findEyeCenter(faceROI, eyes.leftEye, "Left Eye");
    int leftX = leftPupil.x;
    int leftY = leftPupil.y;
    leftPupil.x += eyes.leftEye.x;
    leftPupil.y += eyes.leftEye.y;
    circle(debugFace, leftPupil, 3, 1234);
  }
  if (eyes.hasRightEye) {
    rightPupil = findEyeCenter(faceROI, eyes.rightEye, "Right Eye");
    int rightX = rightPupil.x;
    int rightY = rightPupil.y;
    rightPupil.x += eyes.rightEye.x;
    rightPupil.y += eyes.rightEye.y;
    circle(debugFace, rightPupil, 3, 1234);
  }
  switch (eyes.numEyes) {
    case 0:
      printf("No eyes");
      break;
    case 1:
      printf("L: %s, R: %s: <X: %d, Y: %d>",
        eyes.hasLeftEye ? "T" : "F",
        eyes.hasRightEye ? "T" : "F", 
        eyes.hasLeftEye ? eyes.leftEye.x : eyes.rightEye.x,
        eyes.hasLeftEye ? eyes.leftEye.y : eyes.rightEye.y);
    default:
      printf("L: <X: %d, Y: %d>; R: <X: %d, Y: %d>;",
        eyes.leftEye.x,
        eyes.leftEye.y,
        eyes.rightEye.x,
        eyes.rightEye.y);
  }

  //-- Find Eye Centers
  //cv::Point leftPupil = findEyeCenter(faceROI,leftEyeRegion,"Left Eye");
  //cv::Point rightPupil = findEyeCenter(faceROI,rightEyeRegion,"Right Eye");

  // get corner regions
  //cv::Rect leftRightCornerRegion(leftEyeRegion);
  //leftRightCornerRegion.width -= leftPupil.x;
  //leftRightCornerRegion.x += leftPupil.x;
  //leftRightCornerRegion.height /= 2;
  //leftRightCornerRegion.y += leftRightCornerRegion.height / 2;
  //cv::Rect leftLeftCornerRegion(leftEyeRegion);
  //leftLeftCornerRegion.width = leftPupil.x;
  //leftLeftCornerRegion.height /= 2;
  //leftLeftCornerRegion.y += leftLeftCornerRegion.height / 2;
  //cv::Rect rightLeftCornerRegion(rightEyeRegion);
  //rightLeftCornerRegion.width = rightPupil.x;
  //rightLeftCornerRegion.height /= 2;
  //rightLeftCornerRegion.y += rightLeftCornerRegion.height / 2;
  //cv::Rect rightRightCornerRegion(rightEyeRegion);
  //rightRightCornerRegion.width -= rightPupil.x;
  //rightRightCornerRegion.x += rightPupil.x;
  //rightRightCornerRegion.height /= 2;
  //rightRightCornerRegion.y += rightRightCornerRegion.height / 2;

  //rectangle(debugFace,leftRightCornerRegion,200);
  //rectangle(debugFace,leftLeftCornerRegion,200);
  //rectangle(debugFace,rightLeftCornerRegion,200);
  //rectangle(debugFace,rightRightCornerRegion,200);

  // report the eye coordinates relative to eye centers
  //int leftX = leftPupil.x;
  //int leftY = leftPupil.y;
  //int rightX = rightPupil.x;
  //int rightY = rightPupil.y;

  //printf("L: (%d, %d); R: (%d, %d);\n", leftX, leftY, rightX, rightY);

  // change eye centers to face coordinates
  //rightPupil.x += rightEyeRegion.x;
  //rightPupil.y += rightEyeRegion.y;
  //leftPupil.x += leftEyeRegion.x;
  //leftPupil.y += leftEyeRegion.y;

  // draw eye centers
  //circle(debugFace, rightPupil, 3, 1234);
  //circle(debugFace, leftPupil, 3, 1234);


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

  //cvtColor( frame, frame_gray, CV_BGR2GRAY );
  //equalizeHist( frame_gray, frame_gray );
  //cv::pow(frame_gray, CV_64F, frame_gray);
  //-- Detect faces
  face_cascade.detectMultiScale( frame_gray, faces, 1.1, 2, 0|CV_HAAR_SCALE_IMAGE|CV_HAAR_FIND_BIGGEST_OBJECT, cv::Size(150, 150) );
  //  findSkin(debugImage);

  for( int i = 0; i < faces.size(); i++ )
  {
    rectangle(debugImage, faces[i], cv::Scalar(125, 125, 125, 125));
  }
  //-- Show what you got
  if (faces.size() > 0) {
    findEyes(frame_gray, faces[0]);
  }
}
