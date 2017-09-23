#include <../include/entities/brain/brain.hh>
#include <../include/constants/captureconsts.h>
#include <../include/utils/utils.hh>

#include <iostream>
#include <unistd.h>

// When the target is inside the cicle there is no correction in trajectory
// a high value means a smaller precision but less subtle changes on direction
#define TARGET_AIM_RADIUS 120
#define LOW_VALUE 0

Brain::Brain(Eye *eye) {
    _eye = eye;
}

Brain::~Brain() {

}

void Brain::think() {

    int targetMaxArea;
    int targetIndex;

    while(true) {

        targetIndex = 0;
        targetMaxArea = LOW_VALUE;
        _target = _eye->getTarget();

        for(int i = 0; i < 4; i++) {
            if(_target[i].isKnown == false) {
                continue;
            }
            if(targetMaxArea < _target[i].area) {
                targetMaxArea = _target[i].area;
                targetIndex = i;
            }
        }

        this->setGraphicalTarget(_target[targetIndex]);

        if(_target[targetIndex].isKnown == true) {

            if(abs(_target[targetIndex].posX-IMAGE_CENTER_X) > TARGET_AIM_RADIUS) {
                _cerebellum.goTo(_target[targetIndex]);
//                std::cout << "GO_TO \n\n";
            } else {
                _cerebellum.runFoward(30);
//                std::cout << "RUN_FOWARD \n\n";
            }
        } else {
            _cerebellum.spin(30);
//            std::cout << "SPIN \n\n";
        }

        delete _target;

        usleep(40000);
    }
}

void Brain::setGraphicalTarget(MyPoint &point) {
    _graphicalTargetMutex.lock();
    _graphicalTarget = point;
    _graphicalTargetMutex.unlock();
}

MyPoint Brain::getGraphicalTarget() {
    std::lock_guard<std::mutex> lock(_graphicalTargetMutex);
    return _graphicalTarget;
}
