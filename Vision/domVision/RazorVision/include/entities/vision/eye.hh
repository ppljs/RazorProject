#ifndef EYE_H
#define EYE_H

#include <QtCore>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/videoio.hpp>

#include <iostream>
#include <string>
#include <sstream>

#include <entities/vision/colorreceptor.hh>

class Eye : public QObject {
Q_OBJECT

public:
    Eye(long loopTime, int camIndex);
    ~Eye();

public slots:
    void see();

private:
    int _loopTime;

    cv::VideoCapture _videoInput;
    cv::Mat _rawImg;
    cv::Mat _hsv;
    cv::Mat _finalBinImg;
    cv::Mat _binImg1;
    cv::Mat _binImg2;
    cv::Mat _binImg3;

    ColorReceptor *_receptors[3];


    void trackFilteredObject(int &x, int &y, cv::Mat threshold, cv::Mat &cameraFeed);
    void drawObject(int x, int y,cv::Mat &frame);
    std::string intToString(int number);

};

#endif // EYE_H
