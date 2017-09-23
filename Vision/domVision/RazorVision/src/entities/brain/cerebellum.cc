#include <../include/entities/brain/cerebellum.hh>
#include <../include/constants/captureconsts.h>

#include <pigpio.h>

#define MAX_POWER_ALLOWED 1.9125
#define PWM_FREQ 1000

#define PWM_RIGHT_MOTOR_FWR 5
#define PWM_RIGHT_MOTOR_BCK 6

#define PWM_LEFT_MOTOR_FWR 3
#define PWM_LEFT_MOTOR_BCK 4

Cerebellum::Cerebellum() {

    gpioSetMode(PWM_RIGHT_MOTOR_FWR, PI_OUTPUT);
    gpioSetMode(PWM_RIGHT_MOTOR_BCK, PI_OUTPUT);
    gpioSetMode(PWM_LEFT_MOTOR_FWR, PI_OUTPUT);
    gpioSetMode(PWM_LEFT_MOTOR_BCK, PI_OUTPUT);

    gpioPWM(PWM_RIGHT_MOTOR_FWR, 0);
    gpioPWM(PWM_RIGHT_MOTOR_BCK, 0);
    gpioPWM(PWM_LEFT_MOTOR_FWR, 0);
    gpioPWM(PWM_LEFT_MOTOR_BCK, 0);

}

Cerebellum::~Cerebellum() {

}

void Cerebellum::runFoward(int powerPercentage) {
    if(powerPercentage > 100) {
        powerPercentage = 100;
    } else if (powerPercentage < 0) {
        powerPercentage = 0;
    }

    gpioPWM(PWM_RIGHT_MOTOR_BCK, 0);
    gpioPWM(PWM_LEFT_MOTOR_BCK, 0);

    // duty cicle = powerPercentage * MAX_POWER_ALLOWED
    gpioPWM(PWM_RIGHT_MOTOR_FWR, powerPercentage*MAX_POWER_ALLOWED);
    gpioPWM(PWM_LEFT_MOTOR_FWR, powerPercentage*MAX_POWER_ALLOWED);

}

void Cerebellum::spin(int powerPercentage, bool turnClockWise) {
    if(powerPercentage > 100) {
        powerPercentage = 100;
    } else if (powerPercentage < 0) {
        powerPercentage = 0;
    }

    // duty cicle = powerPercentage * MAX_POWER_ALLOWED
    if(turnClockWise == true) {
        gpioPWM(PWM_RIGHT_MOTOR_FWR, 0);
        gpioPWM(PWM_LEFT_MOTOR_BCK, 0);

        gpioPWM(PWM_RIGHT_MOTOR_BCK, powerPercentage*MAX_POWER_ALLOWED);
        gpioPWM(PWM_LEFT_MOTOR_FWR, powerPercentage*MAX_POWER_ALLOWED);
    } else {
        gpioPWM(PWM_RIGHT_MOTOR_BCK, 0);
        gpioPWM(PWM_LEFT_MOTOR_FWR, 0);

        gpioPWM(PWM_RIGHT_MOTOR_FWR, powerPercentage*MAX_POWER_ALLOWED);
        gpioPWM(PWM_LEFT_MOTOR_BCK, powerPercentage*MAX_POWER_ALLOWED);
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

    this->spin(50, turnClockWise);

}
