#include <../include/utils/utils.hh>

#include <math.h>

Utils::Utils() {

}

float Utils::euclideanDistance(const MyPoint &a, const MyPoint &b){
    return sqrt(pow(a.posX - b.posX, 2) + pow(a.posY - b.posY, 2));
}

float Utils::euclideanDistance(const MyPoint& a, const float& bx, const float& by){
    return sqrt(pow(a.posX - bx, 2) + pow(a.posY - by, 2));
}

float Utils::euclideanDistance(const float& ax, const float& ay, const float& bx, const float& by){
    return sqrt(pow(ax - bx, 2) + pow(ay - by, 2));
}

