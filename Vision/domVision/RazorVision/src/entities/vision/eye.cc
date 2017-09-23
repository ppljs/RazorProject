#include <../include/entities/vision/eye.hh>
#include <../include/constants/captureconsts.h>
#include <../include/entities/brain/brain.hh>

#include <math.h>
#include <stdio.h>
#include <time.h>

Eye::Eye(long loopTime, int camIndex, bool displayImgs) {
    _videoInput.open(camIndex);
    _loopTime = loopTime;
    _displayImgs = displayImgs;

    _brain = NULL;

    this->setTargetInit();

    int vec2[6] = {0, 8, 114, 256, 0, 256};
    int vec1[6] = {9, 77, 145, 256, 113, 203};
    int vec3[6] = {0, 0, 0, 0, 0, 0};
    int vec4[6] = {0, 0, 0, 0, 0, 0};

    _receptors[0] = new ColorReceptor("1", vec1, displayImgs, true);
    _receptors[1] = new ColorReceptor("2", vec2, displayImgs, false);
    _receptors[2] = new ColorReceptor("3", vec3, displayImgs, false);
    _receptors[3] = new ColorReceptor("4", vec4, displayImgs, false);

    //set height and width of capture frame
    _videoInput.set(CV_CAP_PROP_FRAME_WIDTH, FRAME_WIDTH);
    _videoInput.set(CV_CAP_PROP_FRAME_HEIGHT, FRAME_HEIGHT);
}


Eye::~Eye() {
    delete _receptors[0];
    delete _receptors[1];
    delete _receptors[2];
    delete _receptors[3];
}


void Eye::see(void) {

    MyPoint targets[4];

    bool isKnown = false;

    clock_t start, end;

    while(true) {

        start = clock();

        _videoInput.read(_rawImg);        

        cv::cvtColor(_rawImg, _hsv, cv::COLOR_BGR2HSV);

        _binImg1 = _receptors[0]->reception(_hsv, targets[0].posX, targets[0].posY, targets[0].area, targets[0].isKnown, _rawImg);
        _binImg2 = _receptors[1]->reception(_hsv, targets[1].posX, targets[1].posY, targets[1].area, targets[1].isKnown, _rawImg);
        _binImg3 = _receptors[2]->reception(_hsv, targets[2].posX, targets[2].posY, targets[2].area, targets[2].isKnown, _rawImg);
        _binImg3 = _receptors[3]->reception(_hsv, targets[3].posX, targets[3].posY, targets[3].area, targets[3].isKnown, _rawImg);

//        std::cout << "x = " << targets[0].posX << " || y = " << targets[0].posY << "\n\n";
//        std::cout << "x = " << targets[1].posX << " || y = " << targets[1].posY << "\n\n";
//        std::cout << "x = " << targets[2].posX << " || y = " << targets[2].posY << "\n\n";
//        std::cout << "x = " << targets[3].posX << " || y = " << targets[3].posY << "\n\n";

        this->setTarget(targets);

        if(_displayImgs == true) {

            if(_brain != NULL) {
                _graphicalTarget = _brain->getGraphicalTarget();                
                this->drawObject(_graphicalTarget.posX, _graphicalTarget.posY, _rawImg);
            }

            cv::imshow("rawFeed", _rawImg);
            cv::imshow("binImg1", _binImg1);
            cv::imshow("binImg2", _binImg2);
            cv::imshow("binImg3", _binImg3);
            cv::waitKey(32);
        }

        end = clock();
        std::cout << "f = " << 1/(((double)(end - start))/1000000) << "\n\n";
    }

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

void Eye::setTarget(MyPoint targets[]) {
    _targetMutex.lock();
    _target[0] = targets[0];
    _target[1] = targets[1];
    _target[2] = targets[2];
    _target[3] = targets[3];
    _targetMutex.unlock();
}

void Eye::setTargetInit() {
    _targetMutex.lock();
    _target[0].isKnown = false;
    _target[1].isKnown = false;
    _target[2].isKnown = false;
    _target[3].isKnown = false;
    _targetMutex.unlock();
}

MyPoint* Eye::getTarget() {
    std::lock_guard<std::mutex> lock(_targetMutex);
    MyPoint* ps = (MyPoint*)malloc(4*sizeof(MyPoint));
    ps[0] = _target[0];
    ps[1] = _target[1];
    ps[2] = _target[2];
    ps[3] = _target[3];
    return ps;
}

void Eye::setBrain(Brain *b) {
    _brain = b;
}

