#include <../include/entities/brain/brain.hh>
#include <../include/constants/captureconsts.h>
#include <../include/utils/utils.hh>

#include <iostream>

// When the target is inside the cicle there is no correction in trajectory
// a high value means a smaller precision but less subtle changes on direction
#define TARGET_AIM_RADIUS 40

Brain::Brain(Eye *eye) {
    _eye = eye;
}

Brain::~Brain() {

}

void Brain::think() {



    while(true) {

        _target = _eye->getTarget();

        if(_target.isKnown == true) {

            if(abs(_target.posX-IMAGE_CENTER_X) > TARGET_AIM_RADIUS) {
                _cerebellum.goTo(_target);
                std::cout << "GO_TO \n\n";
            } else {
                _cerebellum.runFoward(100);
                std::cout << "RUN_FOWARD \n\n";
            }

        } else {
            _cerebellum.spin(60);
            std::cout << "SPIN \n\n";
        }

    }
}