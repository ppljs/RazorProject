#include <../include/entities/brain/cerebellum.hh>
#include <../include/constants/captureconsts.h>

#define MAX_POWER_ALLOWED 0.75

Cerebellum::Cerebellum() {

}

Cerebellum::~Cerebellum() {

}

void Cerebellum::runFoward(int powerPercentage) {
    if(powerPercentage > 100) {
        powerPercentage = 100;
    } else if (powerPercentage < 0) {
        powerPercentage = 0;
    }

    // duty cicle = powerPercentage * MAX_POWER_ALLOWED
    //will be aplied to the 2 wheels

}

void Cerebellum::spin(int powerPercentage, bool turnClockWise) {
    if(powerPercentage > 100) {
        powerPercentage = 100;
    } else if (powerPercentage < 0) {
        powerPercentage = 0;
    }

    // duty cicle = powerPercentage * MAX_POWER_ALLOWED
    //will be aplied to the 2 wheels but simetric
}

void Cerebellum::goTo(const MyPoint &target) {
    bool turnClockWise;

    if((IMAGE_CENTER_X-target.posX) > 0) {
        //Turn right
        turnClockWise = true;

    } else {
        turnClockWise = false;
    }

    this->spin(70, turnClockWise);

}
