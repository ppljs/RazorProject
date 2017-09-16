#ifndef IMAGECAPTURE_HH
#define IMAGECAPTURE_HH

#include <QObject>
#include <QThread>
#include <QReadWriteLock>
#include <opencv2/opencv.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/videoio.hpp>

class ImageCaptureReader : public QObject {
    Q_OBJECT
public slots:
    void readFromCam(cv::VideoCapture &cap);

signals:
    void imageReady(const cv::Mat &img);
};


class ImageCapture : public QObject {
    Q_OBJECT
public:
    ImageCapture();
    ~ImageCapture();

    cv::Mat getImage();
    cv::Mat getHSVImage();
    void setRunning(bool running) {_running = running;}
private:
    QThread _imageReader;
    QReadWriteLock _rwlock;
    cv::Mat _img;
    cv::VideoCapture _cap;
    bool _running;

public slots:
    void handleImage(const cv::Mat &);

signals:
    void readImage(cv::VideoCapture &);
};

#endif // IMAGECAPTURE_HH
