#include "cybergod.hpp"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    CyberGod w;
    w.show();

    return a.exec();
}
