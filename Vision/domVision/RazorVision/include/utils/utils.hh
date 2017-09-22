#ifndef UTILS_H
#define UTILS_H

#include <../utils/mypoint.h>

class Utils {

public:
    Utils();
    ~Utils();

    static float euclideanDistance(const MyPoint& a, const MyPoint& b);
    static float euclideanDistance(const MyPoint& a, const float& bx, const float& by);
    static float euclideanDistance(const float& ax, const float& ay, const float& bx, const float& by);

};




#endif //UTILS_H
