#ifndef COLORRECEPTOR_H
#define COLORRECEPTOR_H

#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>

class ColorReceptor {

public:
    ColorReceptor(char colorName[], int cvec[], bool displayImgs, bool isRed);
    cv::Mat reception(cv::Mat& hsv, int& x, int& y, float &tArea, bool& isKnown, cv::Mat& cameraFeed);

private:
    bool _displayImgs;
    bool _isRed;

    // Internal variables
    int _H_MIN;
    int _H_MAX;
    int _H_MIN_COMP;
    int _H_MAX_COMP;
    int _S_MIN;
    int _S_MAX;
    int _V_MIN;
    int _V_MAX;
    //these two vectors needed for output of findContours
    std::vector< std::vector<cv::Point> > _contours;
    std::vector<cv::Vec4i> _hierarchy;

    char _colorName[15];

    cv::Mat _threshold;
    cv::Mat _redThreshold;

    // Functions
    void createTrackbars();
    void on_trackbar( int, void* );
    void morphOps(cv::Mat &thresh);
    void trackFilteredObject(int& x, int& y, float& tArea, bool& isKnown, cv::Mat& threshold, cv::Mat& cameraFeed);

};

#endif // COLORRECEPTOR_H
