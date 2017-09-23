#include <../include/entities/vision/eye.hh>
#include <../include/constants/captureconsts.h>

#include <math.h>

#define MAX_NUM_OBJECTS 50
#define MIN_OBJECT_AREA 600
#define MAX_OBJECT_AREA 1000000
#define PI              3.1415

Eye::Eye(long loopTime, int camIndex, bool displayImgs) {
    _videoInput.open(camIndex);
    _loopTime = loopTime;
    _displayImgs = displayImgs;

    this->setTarget(IMAGE_CENTER_X, IMAGE_CENTER_Y, false);

    int yvec[6] = {0, 0, 0, 0, 0, 0};
    int gvec[6] = {0, 52, 206, 256, 131, 256};
//    int yvec[6] = {0, 24, 81, 256, 115, 256};
//    int gvec[6] = {23, 65, 43, 256, 70, 256};
    int rvec[6] = {0, 0, 0, 0, 0, 0};

    _receptors[0] = new ColorReceptor("green", gvec, displayImgs);
    _receptors[1] = new ColorReceptor("yellow", yvec, displayImgs);
    _receptors[2] = new ColorReceptor("red", rvec, displayImgs);

    //set height and width of capture frame
    _videoInput.set(CV_CAP_PROP_FRAME_WIDTH, FRAME_WIDTH);
    _videoInput.set(CV_CAP_PROP_FRAME_HEIGHT, FRAME_HEIGHT);
}


Eye::~Eye() {
    delete _receptors[0];
    delete _receptors[1];
    delete _receptors[2];
}


void Eye::see(void) {

    int x = 0;
    int y = 0;
    bool isKnown = false;

    while(true) {
        _videoInput.read(_rawImg);
        cv::cvtColor(_rawImg, _hsv, cv::COLOR_BGR2HSV);

        _binImg1 = _receptors[0]->reception(_hsv);
        _binImg2 = _receptors[1]->reception(_hsv);
        _binImg3 = _receptors[2]->reception(_hsv);

        _finalBinImg = _binImg1 + _binImg2 + _binImg3;


        trackFilteredObject(x, y, isKnown, _finalBinImg, _rawImg);

        this->setTarget(x, y, isKnown);

        if(_displayImgs == true) {
            cv::imshow("rawFeed", _rawImg);
            cv::imshow("finalBinImg", _finalBinImg);
            cv::imshow("binImg1", _binImg1);
            cv::imshow("binImg2", _binImg2);
            cv::imshow("binImg3", _binImg3);
            cv::waitKey(32);
        }

       cv::waitKey(20);
    }

}

void Eye::trackFilteredObject(int& x, int& y, bool& isKnown, cv::Mat& threshold, cv::Mat& cameraFeed){


    //find contours of filtered image using openCV findContours function
    cv::findContours(threshold, _contours,_hierarchy,CV_RETR_CCOMP,CV_CHAIN_APPROX_SIMPLE );
    //use moments method to find our filtered object
    double refArea = 0;
    bool objectFound = false;


    if (_hierarchy.size() > 0) {
        cv::Moments moment;
        int numObjects = _hierarchy.size();
        //if number of objects greater than MAX_NUM_OBJECTS we have a noisy filter
        if(numObjects<MAX_NUM_OBJECTS){
            for (int index = 0; index >= 0; index = _hierarchy[index][0]) {

                moment = cv::moments((cv::Mat)_contours[index]);
                double area = moment.m00; 

//                cv::Point extLeft  = *min_element(contours[index].begin(), contours[index].end(),
//                                      [](const cv::Point& lhs, const cv::Point& rhs) {
//                                          return lhs.x < rhs.x;
//                                  });
//                cv::Point extRight = *max_element(contours[index].begin(), contours[index].end(),
//                                      [](const cv::Point& lhs, const cv::Point& rhs) {
//                                          return lhs.x < rhs.x;
//                                  });
//                cv::Point extTop   = *min_element(contours[index].begin(), contours[index].end(),
//                                      [](const cv::Point& lhs, const cv::Point& rhs) {
//                                          return lhs.y < rhs.y;
//                                  });
//                cv::Point extBot   = *max_element(contours[index].begin(), contours[index].end(),
//                                      [](const cv::Point& lhs, const cv::Point& rhs) {
//                                          return lhs.y < rhs.y;
//                                  });

//                cv::minEnclosingCircle(contours[index], center, radius);
//                std::cout << "Area = " << area << " || contourArea = " << PI*pow(radius, 2) << "\n\n";
//                if((PI*pow(radius, 2)) > 1.2*area) {
//                    continue;
//                }

                //if the area is less than 20 px by 20px then it is probably just noise
                //if the area is the same as the 3/2 of the image size, probably just a bad filter
                //we only want the object with the largest area so we safe a reference area each
                //iteration and compare it to the area in the next iteration.
                if(area>MIN_OBJECT_AREA && area<MAX_OBJECT_AREA && area>refArea){
                    x = moment.m10/area;
                    y = moment.m01/area;
                    objectFound = true;
                    refArea = area;
                }/*else {

                    objectFound = false;
                    std::cout << "RUIM - index = " << index << "\n\n";
                }*/
            }
            if(_displayImgs == true) {
                //let user know you found an object
                if(objectFound ==true){
                    cv::putText(cameraFeed,"Tracking Object",cv::Point(0,50),2,1,cv::Scalar(0,255,0),2);
                    //draw object location on screen
                    if(_displayImgs) {
                        drawObject(x,y,cameraFeed);
                    }

                }else{
                    cv::putText(cameraFeed,"TOO MUCH NOISE! ADJUST FILTER",cv::Point(0,50),1,2,cv::Scalar(0,0,255),2);
                }
            }
        }
    }

    isKnown = objectFound;
}


void Eye::drawObject(int x, int y,cv::Mat &frame){

    //use some of the openCV drawing functions to draw crosshairs
    //on your tracked image!

    //UPDATE:JUNE 18TH, 2013
    //added 'if' and 'else' statements to prevent
    //memory errors from writing off the screen (ie. (-25,-25) is not within the window!)

    cv::circle(frame,cv::Point(x,y),20,cv::Scalar(0,255,0),2);
    if(y-25>0)
    cv::line(frame,cv::Point(x,y),cv::Point(x,y-25),cv::Scalar(0,255,0),2);
    else cv::line(frame,cv::Point(x,y),cv::Point(x,0),cv::Scalar(0,255,0),2);
    if(y+25<FRAME_HEIGHT)
    cv::line(frame,cv::Point(x,y),cv::Point(x,y+25),cv::Scalar(0,255,0),2);
    else cv::line(frame,cv::Point(x,y),cv::Point(x,FRAME_HEIGHT),cv::Scalar(0,255,0),2);
    if(x-25>0)
    cv::line(frame,cv::Point(x,y),cv::Point(x-25,y),cv::Scalar(0,255,0),2);
    else cv::line(frame,cv::Point(x,y),cv::Point(0,y),cv::Scalar(0,255,0),2);
    if(x+25<FRAME_WIDTH)
    cv::line(frame,cv::Point(x,y),cv::Point(x+25,y),cv::Scalar(0,255,0),2);
    else cv::line(frame,cv::Point(x,y),cv::Point(FRAME_WIDTH,y),cv::Scalar(0,255,0),2);

    cv::putText(frame,intToString(x)+","+intToString(y),cv::Point(x,y+30),1,1,cv::Scalar(0,255,0),2);

}

std::string Eye::intToString(int number) {
    std::stringstream ss;
    ss << number;
    return ss.str();
}

void Eye::setTarget(int x, int y, bool isknown) {
    _targetMutex.lock();
    _target.posX = x;
    _target.posY = y;
    _target.isKnown = isknown;
    _targetMutex.unlock();
}

MyPoint Eye::getTarget() {
    std::lock_guard<std::mutex> lock(_targetMutex);
    return _target;
}

