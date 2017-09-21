#ifndef COLORRECEPTOR_H
#define COLORRECEPTOR_H

#include <QtCore>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>

class ColorReceptor {

public:
    ColorReceptor(char colorName[], int cvec[]);

signals:

public slots:
    cv::Mat reception(cv::Mat hsv);

private:
    // Internal variables
    int _H_MIN;
    int _H_MAX;
    int _S_MIN;
    int _S_MAX;
    int _V_MIN;
    int _V_MAX;

    char _colorName[15];

    cv::Mat _threshold;

    // Functions
    void createTrackbars();
    void on_trackbar( int, void* );
    void morphOps(cv::Mat &thresh);

};

#endif // COLORRECEPTOR_H
