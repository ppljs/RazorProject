#include <../include/entities/vision/eye.hh>
#include <../include/entities/brain/brain.hh>
#include <thread>
//#include <pigpio.h>

#include <iostream>


void runEye(Eye* eye) {
    eye->see();
}

void runBrain(Brain* brain) {
    brain->think();
}

int main(int argc, char *argv[]) {

    int cam = 0;
    bool displayImgs = false;

    if(argc > 1) {
        cam = std::stoi(argv[1]);
    }

    if(argc > 2) {
        displayImgs = (strncmp(argv[2], "true", 4)==0)? true : false;
    }

    //gpioInitialise();

    Eye eye(10, cam, displayImgs);
    Brain brain(&eye);

    std::thread eyeThread(runEye, &eye);
    std::thread brainThread(runBrain, &brain);

    eyeThread.join();
    brainThread.join();

    return 0;
}


