#include <QApplication>
#include "mainform.h"

int main(int argc, char **argv)//Главная исполняемая функция
{
    QApplication app(argc,argv);//Инициализация Qt
    MainForm f;//Инициализация окна программы
    f.show();//Отображение окна программы
    return app.exec();
}
