#include "mainsoduko_visual.h"
#include <QApplication>

MainSoduko_visual *pt_w;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainSoduko_visual w;
    pt_w = &w;
    w.show();

    return a.exec();
}
