#include <QCoreApplication>
#include <entities/vision/eye.hh>

int main(int argc, char *argv[]) {
    QCoreApplication a(argc, argv);

    Eye eye(10, 1);

    eye.see();

    return a.exec();
}
