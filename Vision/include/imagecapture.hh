#ifndef IMAGECAPTURE_HH
#define IMAGECAPTURE_HH

#include <opencv2/opencv.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/videoio.hpp>


class ImageCapture {
public:
    ImageCapture();
    ~ImageCapture();

    cv::Mat getImage();
    cv::Mat getHSVImage();
    void setRunning(bool running) {_running = running;}
private:
    void readImage();
    cv::Mat _img;
    cv::VideoCapture _cap;
    bool _running;
};

#endif // IMAGECAPTURE_HH
