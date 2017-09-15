#include "../include/ballTrack.hh"
#include <iostream>

using namespace cv;
using namespace std;

BallTrack::BallTrack() {
    _lHUE = 0;  // HUE -> Represents the colour [0, 179]
    _hHUE = 52;

    _lSat = 152;  // Saturation -> Amount of HUE colour mixed with white [0, 255]
    _hSat = 255;

    _lVal = 0;  // Value -> Amount of HUE colour mixed with black [0, 255]
    _hVal = 70;
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

    //Create trackbars in "Control" window
    cvCreateTrackbar("LowH", "Control", &_lHUE, 179); //Hue (0 - 179)
    cvCreateTrackbar("HighH", "Control", &_hHUE, 179);

    cvCreateTrackbar("LowS", "Control", &_lSat, 255); //Saturation (0 - 255)
    cvCreateTrackbar("HighS", "Control", &_hSat, 255);

    cvCreateTrackbar("LowV", "Control", &_lVal, 255); //Value (0 - 255)
    cvCreateTrackbar("HighV", "Control", &_hVal, 255);

    int lastX, lastY;
    lastX = lastY = -1;

    // Reading temporary image
    Mat imgTmp;
    cap.read(imgTmp);

    // Creating black image the same size as the camera's
    Mat imgLines = Mat::zeros(imgTmp.size(), CV_8UC3);

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

        Moments imgMoments = moments(imgThresholded);
        double m01 = imgMoments.m01;
        double m10 = imgMoments.m10;
        double area = imgMoments.m00;

        if(area > 100000.0 && area < 10E9) {
            int posX =  m10/area;
            int posY = m01/area;

            if(lastX >= 0 && lastY >= 0 && posX >= 0 && posY >= 0) {
                line(imgLines, Point(posX, posY), Point(lastX, lastY), Scalar(0, 0, 255), 2);
            }

            lastX = posX;
            lastY = posY;
        }

        imshow("Thresholded Image", imgThresholded); //show the thresholded image
        imgOriginal = imgOriginal + imgLines;
        imshow("Original", imgOriginal); //show the original image
    }
    
    
}
