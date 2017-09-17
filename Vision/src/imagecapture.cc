#include <include/imagecapture.hh>


void ImageCaptureReader::readFromCam(cv::VideoCapture &cap) {
    cv::Mat img;

    if(!cap.isOpened()) {
        std::cout << "Camera not opened\n";
        return;
    }

    while(cap.isOpened()) {
        if(!cap.read(img)) {
            std::cout << "Image coudn't be read\n";
            return;
        }
        cv::imshow("In thread", img);
        emit imageReady(img);
    }
}


ImageCapture::ImageCapture() {
    _cap.open(0);
    ImageCaptureReader *reader = new ImageCaptureReader();
    reader->moveToThread(&_imageReader);
    connect(&_imageReader, &QThread::finished, reader, &QObject::deleteLater);
    connect(this, &ImageCapture::readImage, reader, &ImageCaptureReader::readFromCam);
    connect(reader, &ImageCaptureReader::imageReady, this, &ImageCapture::handleImage);
    _imageReader.start(QThread::HighPriority);
}

ImageCapture::~ImageCapture() {
    _imageReader.quit();
    _imageReader.wait();
}

cv::Mat ImageCapture::getImage() {
    cv::Mat img;
    _rwlock.lockForRead();
    // TODO: Verify how long this takes, since it's a deep copy
    // TODO: Also check if cloning is really necessary
    img = _img.clone();
    _rwlock.unlock();

    if(img.empty()) {
        std::cout << "Image empty\n";
    }
    return img;
}

cv::Mat ImageCapture::getHSVImage() {
    cv::Mat img;
    _rwlock.lockForRead();
    // TODO: Verify how long this takes, since it's a deep copy
    // TODO: Also check if cloning is really necessary
    // (may be, because of subsequent uses for colour detection)
    img = _img.clone();
    _rwlock.unlock();

    if(img.empty()) {
        std::cout << "Image empty\n";
    }
    cv::Mat imgHSV;
    cv::cvtColor(img, imgHSV, cv::COLOR_BGR2HSV);
    return imgHSV;
}

void ImageCapture::handleImage(const cv::Mat &img) {
    _rwlock.lockForWrite();
    _img = img.clone();
    _rwlock.unlock();
}
