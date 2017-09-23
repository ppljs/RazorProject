#include <../include/entities/vision/colorreceptor.hh>

#define MAX_NUM_OBJECTS 30
#define MIN_OBJECT_AREA 250
#define MAX_OBJECT_AREA 500000
#define PI              3.1415

ColorReceptor::ColorReceptor(char colorName[], int cvec[], bool displayImgs, bool isRed) {

    _displayImgs = displayImgs;
    _isRed = isRed;

    _H_MIN = cvec[0];
    _H_MAX = cvec[1];
    _S_MIN = cvec[2];
    _S_MAX = cvec[3];
    _V_MIN = cvec[4];
    _V_MAX = cvec[5];
    _H_MIN_COMP = 0;
    _H_MAX_COMP = 0;

    strncpy(_colorName, colorName, 15);
    if(_displayImgs == true) {
        createTrackbars();
    }

}

void ColorReceptor::createTrackbars() {
    cv::namedWindow(_colorName,0);

    cv::createTrackbar( "H_MIN", _colorName, &_H_MIN, 256);
    cv::createTrackbar( "H_MAX", _colorName, &_H_MAX, 256);
    if(_isRed == true) {
        cv::createTrackbar( "H_MIN_COMP", _colorName, &_H_MIN_COMP, 256);
        cv::createTrackbar( "H_MAX_COMP", _colorName, &_H_MAX_COMP, 256);
    }
    cv::createTrackbar( "S_MIN", _colorName, &_S_MIN, 256);
    cv::createTrackbar( "S_MAX", _colorName, &_S_MAX, 256);
    cv::createTrackbar( "V_MIN", _colorName, &_V_MIN, 256);
    cv::createTrackbar( "V_MAX", _colorName, &_V_MAX, 256);
}

void ColorReceptor::on_trackbar( int, void* ) {
    //This function gets called whenever a
    // trackbar position is changed
}

cv::Mat ColorReceptor::reception(cv::Mat& hsv, int& x, int& y, float& tArea, bool& isKnown, cv::Mat& cameraFeed) {
    cv::inRange(hsv, cv::Scalar(_H_MIN, _S_MIN, _V_MIN), cv::Scalar(_H_MAX, _S_MAX, _V_MAX), _threshold);
    if(_isRed == true) {
        cv::inRange(hsv, cv::Scalar(_H_MIN_COMP, _S_MIN, _V_MIN), cv::Scalar(_H_MAX_COMP, _S_MAX, _V_MAX), _redThreshold);
        _threshold = _threshold + _redThreshold;
    }
    morphOps(_threshold);

    trackFilteredObject(x, y, tArea, isKnown, _threshold, cameraFeed);

    return _threshold;
}

void ColorReceptor::morphOps(cv::Mat &thresh){

    //create structuring element that will be used to "dilate" and "erode" image.
    //the element chosen here is a 3px by 3px rectangle
    cv::Mat erodeElement = cv::getStructuringElement( cv::MORPH_RECT,cv::Size(6,6));
    //dilate with larger element so make sure object is nicely visible
    cv::Mat dilateElement = cv::getStructuringElement( cv::MORPH_RECT,cv::Size(12,12));

//    cv::erode(thresh,thresh,erodeElement);
    cv::erode(thresh,thresh,erodeElement);

//    cv::dilate(thresh,thresh,dilateElement);
    cv::dilate(thresh,thresh,dilateElement);
}

void ColorReceptor::trackFilteredObject(int& x, int& y, float& tArea, bool& isKnown, cv::Mat& threshold, cv::Mat& cameraFeed){


    //find contours of filtered image using openCV findContours function
    cv::findContours(threshold, _contours,_hierarchy,CV_RETR_CCOMP,CV_CHAIN_APPROX_SIMPLE );
    //use moments method to find our filtered object
    float refArea = 0;
    float area;
    bool objectFound = false;

    if (_hierarchy.size() > 0) {
        cv::Moments moment;
        int numObjects = _hierarchy.size();
        //if number of objects greater than MAX_NUM_OBJECTS we have a noisy filter
        if(numObjects<MAX_NUM_OBJECTS){
            for (int index = 0; index >= 0; index = _hierarchy[index][0]) {

                moment = cv::moments((cv::Mat)_contours[index]);
                area = moment.m00;

//                cv::Point extLeft  = *min_element(contours[index].begin(), contours[index].end(),
//                                      [](const cv::Point& lhs, const cv::Point& rhs) {
//                                          return lhs.x < rhs.x;
//                                  });
//                cv::Point extRight = *max_element(contours[index].begin(), contours[index].end(),
//                                      [](const cv::Point& lhs, const cv::Point& rhs) {
//                                          return lhs.x < rhs.x;
//                                  });
//                cv::Point extTop   = *min_element(contours[index].begin(), contours[index].end(),
//                                      [](const cv::Point& lhs, const cv::Point& rhs) {
//                                          return lhs.y < rhs.y;
//                                  });
//                cv::Point extBot   = *max_element(contours[index].begin(), contours[index].end(),
//                                      [](const cv::Point& lhs, const cv::Point& rhs) {
//                                          return lhs.y < rhs.y;
//                                  });

//                cv::minEnclosingCircle(contours[index], center, radius);
//                std::cout << "Area = " << area << " || contourArea = " << PI*pow(radius, 2) << "\n\n";
//                if((PI*pow(radius, 2)) > 1.2*area) {
//                    continue;
//                }

                //if the area is less than 20 px by 20px then it is probably just noise
                //if the area is the same as the 3/2 of the image size, probably just a bad filter
                //we only want the object with the largest area so we safe a reference area each
                //iteration and compare it to the area in the next iteration.
                if(area>MIN_OBJECT_AREA && area<MAX_OBJECT_AREA && area>refArea){
                    x = moment.m10/area;
                    y = moment.m01/area;
                    tArea = area;
                    objectFound = true;
                    refArea = area;
                }/*else {

                    objectFound = false;
                    std::cout << "RUIM - index = " << index << "\n\n";
                }*/
            }
        }
    }

    isKnown = objectFound;
}
