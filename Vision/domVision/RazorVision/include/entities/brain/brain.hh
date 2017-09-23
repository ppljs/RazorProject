#ifndef BRAIN_H
#define BRAIN_H

#include <../entities/vision/eye.hh>
#include <../entities/brain/cerebellum.hh>
#include <../utils/mypoint.h>
#include <mutex>

class Brain {

    public:
        Brain(Eye* eye);
        ~Brain();
        void think();

        MyPoint getGraphicalTarget();

    private:
        Eye* _eye;
        Cerebellum _cerebellum;

        MyPoint* _target;

        MyPoint _graphicalTarget;
        std::mutex _graphicalTargetMutex;

        void setGraphicalTarget(MyPoint& point);

};



#endif //BRAIN_H
