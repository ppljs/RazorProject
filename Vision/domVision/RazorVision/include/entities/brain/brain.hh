#ifndef BRAIN_H
#define BRAIN_H

#include <../entities/vision/eye.hh>
#include <../entities/brain/cerebellum.hh>
#include <../utils/mypoint.h>

class Brain {

    public:
        Brain(Eye* eye);
        ~Brain();
        void think();

    private:
        Eye* _eye;
        Cerebellum _cerebellum;

        MyPoint _target;

};



#endif //BRAIN_H
