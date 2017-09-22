#include <../include/entities/brain/cerebellum.hh>
#include <../include/constants/captureconsts.h>

#include <pigpio.h>

#define MAX_POWER_ALLOWED 7500
#define PWM_FREQ 1000

#define PWM_RIGHT_MOTOR_FWR 12
#define PWM_RIGHT_MOTOR_BCK 18

#define PWM_LEFT_MOTOR_FWR 13
#define PWM_LEFT_MOTOR_BCK 19

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
    gpioHardwarePWM(PWM_RIGHT_MOTOR_FWR, PWM_FREQ, powerPercentage*MAX_POWER_ALLOWED);
    gpioHardwarePWM(PWM_LEFT_MOTOR_FWR, PWM_FREQ, powerPercentage*MAX_POWER_ALLOWED);

}

void Cerebellum::spin(int powerPercentage, bool turnClockWise) {
    if(powerPercentage > 100) {
        powerPercentage = 100;
    } else if (powerPercentage < 0) {
        powerPercentage = 0;
    }

    // duty cicle = powerPercentage * MAX_POWER_ALLOWED
    if(turnClockWise == true) {
        gpioHardwarePWM(PWM_RIGHT_MOTOR_BCK, PWM_FREQ, powerPercentage*MAX_POWER_ALLOWED);
        gpioHardwarePWM(PWM_LEFT_MOTOR_FWR, PWM_FREQ, powerPercentage*MAX_POWER_ALLOWED);
    } else {
        gpioHardwarePWM(PWM_RIGHT_MOTOR_FWR, PWM_FREQ, powerPercentage*MAX_POWER_ALLOWED);
        gpioHardwarePWM(PWM_LEFT_MOTOR_BCK, PWM_FREQ, powerPercentage*MAX_POWER_ALLOWED);
    }
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
