#include <iostream>
#include "../include/ballTrack.hh"
#include "../RxCpp/Rx/v2/src/rxcpp/rx.hpp"

using namespace cv;

int main(int argc, char** argv) {
    BallTrack bt;
//    bt.detectBall();

    auto thread = rxcpp::observe_on_event_loop();
    auto values1 = rxcpp::observable<>::range(1);
    auto s1 = values1
        .subscribe_on(thread)
        .map([](int prime) {std::this_thread::yield(); return std::make_tuple("1: ", prime);}
    );
    auto s2 = values1
        .subscribe_on(thread)
        .map([](int prime) {std::this_thread::yield(); return std::make_tuple("2: ", prime);}
    );
    s1.merge(s2)
        .take(6)
        .observe_on(thread)
        .as_blocking()
        .subscribe(
            rxcpp::util::apply_to(
                [](const char *s, int p) {/*std::cout << s << ", " << p << std::endl*/printf("%s, %d\n", s, p);}
            )
    );
    return 0;
}
