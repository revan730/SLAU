#include <QApplication>
#include "mainform.h"

int main(int argc, char **argv)
{
    QApplication app(argc,argv);
    MainForm f;
    f.show();
    return app.exec();
}
