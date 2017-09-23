#ifndef EYE_H
#define EYE_H

#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/videoio.hpp>

#include <iostream>
#include <string>
#include <sstream>
#include <mutex>

#include <../include/entities/vision/colorreceptor.hh>
#include <../include/utils/mypoint.h>

class Brain;

class Eye {

public:
    Eye(long loopTime, int camIndex, bool displayImgs);
    ~Eye();

    // Vision loop
    void see(void);

    // Getters
    MyPoint* getTarget();

    void setBrain(Brain* b);

private:
    Brain* _brain;
    MyPoint _graphicalTarget;

    // Control variables
    int _loopTime;
    bool _displayImgs;

    // Image processing objects
    cv::VideoCapture _videoInput;
    cv::Mat _rawImg;
    cv::Mat _hsv;
    cv::Mat _finalBinImg;
    cv::Mat _binImg1;
    cv::Mat _binImg2;
    cv::Mat _binImg3;    

    // Individual color catcher objects
    ColorReceptor *_receptors[4];

    // Target matrix position
    MyPoint _target[4];

    // Mutex for accessing the target (Eye writes and Brain reads)
    std::mutex _targetMutex;

    // Internal Functions (most for image processing)
    void trackFilteredObject(int& x, int& y, bool &isKnown, cv::Mat& threshold, cv::Mat& cameraFeed);
    void drawObject(int x, int y,cv::Mat &frame);
    std::string intToString(int number);

    // Internal setter (To avoid setting the _target without mutex_lock)
    void setTarget(MyPoint targets[]);

    void setTargetInit();

};

#endif // EYE_H
