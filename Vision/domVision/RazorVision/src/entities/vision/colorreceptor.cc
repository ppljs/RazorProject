#include <../include/entities/vision/colorreceptor.hh>

ColorReceptor::ColorReceptor(char colorName[], int cvec[], bool displayImgs) {

    _displayImgs = displayImgs;

    _H_MIN = cvec[0];
    _H_MAX = cvec[1];
    _S_MIN = cvec[2];
    _S_MAX = cvec[3];
    _V_MIN = cvec[4];
    _V_MAX = cvec[5];

    strncpy(_colorName, colorName, 15);
    if(displayImgs == true) {
        createTrackbars();
    }

}

void ColorReceptor::createTrackbars() {
    cv::namedWindow(_colorName,0);

    cv::createTrackbar( "H_MIN", _colorName, &_H_MIN, 256);
    cv::createTrackbar( "H_MAX", _colorName, &_H_MAX, 256);
    cv::createTrackbar( "S_MIN", _colorName, &_S_MIN, 256);
    cv::createTrackbar( "S_MAX", _colorName, &_S_MAX, 256);
    cv::createTrackbar( "V_MIN", _colorName, &_V_MIN, 256);
    cv::createTrackbar( "V_MAX", _colorName, &_V_MAX, 256);
}

void ColorReceptor::on_trackbar( int, void* ) {
    //This function gets called whenever a
    // trackbar position is changed
}


cv::Mat ColorReceptor::reception(cv::Mat hsv) {
    cv::inRange(hsv, cv::Scalar(_H_MIN, _S_MIN, _V_MIN), cv::Scalar(_H_MAX, _S_MAX, _V_MAX), _threshold);
    morphOps(_threshold);

    return _threshold;
}

void ColorReceptor::morphOps(cv::Mat &thresh){

    //create structuring element that will be used to "dilate" and "erode" image.
    //the element chosen here is a 3px by 3px rectangle
    cv::Mat erodeElement = cv::getStructuringElement( cv::MORPH_RECT,cv::Size(8,8));
    //dilate with larger element so make sure object is nicely visible
    cv::Mat dilateElement = cv::getStructuringElement( cv::MORPH_RECT,cv::Size(10,10));

    cv::erode(thresh,thresh,erodeElement);
    cv::erode(thresh,thresh,erodeElement);

    cv::dilate(thresh,thresh,dilateElement);
    cv::dilate(thresh,thresh,dilateElement);
}
