#include "../include/ballTrack.hh"
#include <iostream>

using namespace cv;
using namespace std;

BallTrack::BallTrack() {

}

BallTrack::~BallTrack() {

}

void BallTrack::detectBall() {
    VideoCapture cap(0); //capture the video from web cam

    if (!cap.isOpened()) {  // if not success, exit program
         cout << "Cannot open the web cam" << endl;
         return;
    }

    namedWindow("Control", CV_WINDOW_AUTOSIZE); //create a window called "Control"

    _lHUE = 0;  // HUE -> Represents the colour [0, 179]
    _hHUE = 179;

    _lSat = 0;  // Saturation -> Amount of HUE colour mixed with white [0, 255]
    _hSat = 255;

    _lVal = 0;  // Value -> Amount of HUE colour mixed with black [0, 255]
    _hVal = 255;

    //Create trackbars in "Control" window
    cvCreateTrackbar("LowH", "Control", &_lHUE, 179); //Hue (0 - 179)
    cvCreateTrackbar("HighH", "Control", &_hHUE, 179);

    cvCreateTrackbar("LowS", "Control", &_lSat, 255); //Saturation (0 - 255)
    cvCreateTrackbar("HighS", "Control", &_hSat, 255);

    cvCreateTrackbar("LowV", "Control", &_lVal, 255); //Value (0 - 255)
    cvCreateTrackbar("HighV", "Control", &_hVal, 255);

    while (waitKey(30) != 27) {
        Mat imgOriginal;

        bool bSuccess = cap.read(imgOriginal); // read a new frame from video

        if (!bSuccess) { //if not success, break loop
             cout << "Cannot read a frame from video stream" << endl;
             break;
        }

        Mat imgHSV;

        cvtColor(imgOriginal, imgHSV, COLOR_BGR2HSV); //Convert the captured frame from BGR to HSV

        Mat imgThresholded;

        inRange(imgHSV, Scalar(_lHUE, _lSat, _lVal), Scalar(_hHUE, _hSat, _hVal), imgThresholded); //Threshold the image

        //morphological opening (remove small objects from the foreground)
        erode(imgThresholded, imgThresholded, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)) );
        dilate( imgThresholded, imgThresholded, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)) );

        //morphological closing (fill small holes in the foreground)
        dilate( imgThresholded, imgThresholded, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)) );
        erode(imgThresholded, imgThresholded, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)) );

        imshow("Thresholded Image", imgThresholded); //show the thresholded image
        imshow("Original", imgOriginal); //show the original image
    }
}
