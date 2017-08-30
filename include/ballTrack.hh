#ifndef BALL_TRACH_H
#define BALL_TRACK_H

#include <opencv2/opencv.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>

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
