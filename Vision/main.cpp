#include <QCoreApplication>
#include <include/imagecapture.hh>
#include <opencv2/opencv.hpp>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    ImageCapture ic;
    while(cv::waitKey(30) != 27) {
        imshow("Original", ic.getImage()); //show the original image
//        imshow("HSV", ic.getHSVImage()); //show the original image
    }

    return a.exec();
}
