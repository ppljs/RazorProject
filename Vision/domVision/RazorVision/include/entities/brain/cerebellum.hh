#ifndef CEREBELLUM_H
#define CEREBELLUM_H

#include <../utils/mypoint.h>

class Cerebellum {

    public:
        Cerebellum();
        ~Cerebellum();

        void runFoward(int powerPercentage);
        void spin(int powerPercentage, bool turnClockWise = false);
        void goTo(const MyPoint& target);

    private:

};

#endif //CEREBELLUM_H
