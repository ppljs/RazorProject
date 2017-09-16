#include <include/imagecapture.hh>

ImageCapture::ImageCapture() {
    _cap.open(0);
}

ImageCapture::~ImageCapture() {

}

cv::Mat ImageCapture::getImage() {
    if(_img.empty()) {
        std::cout << "Image empty\n";
    }
    return _img;
}

cv::Mat ImageCapture::getHSVImage() {
    if(_img.empty()) {
        std::cout << "Image empty\n";
    }

}

void ImageCapture::readImage() {
    while(_cap.isOpened() && _running) {
        if(!_cap.read(_img)) {
            std::cout << "Cannot read frame from stream!\n";
            this->setRunning(false);
        }
    }
}
