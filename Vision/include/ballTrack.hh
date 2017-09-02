#ifndef BALL_TRACH_H
#define BALL_TRACK_H

#include <opencv2/opencv.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>


/**
 * @brief The BallTrack class
 * Useful values of HUE are:
 * Orange  0-22
 * Yellow 22- 38
 * Green 38-75
 * Blue 75-130
 * Violet 130-160
 * Red 160-179
 */


class BallTrack {
public:
    BallTrack();
    ~BallTrack();
    void setLHUE(int);
    void setHHUE(int);
    void setLSat(int);
    void setHSat(int);
    void setLVal(int);
    void setHVal(int);
    void detectBall();

    int getLHUE(int);
    int getHHUE(int);
    int getLSat(int);
    int getHSat(int);
    int getLVal(int);
    int getHVal(int);

private:
    int _lHUE;
    int _hHUE;
    int _lSat;
    int _hSat;
    int _lVal;
    int _hVal;
};

#endif // BALL_TRACK_H
