#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    if(argc < 2)
    {
        qDebug() << "need source folder!" << endl;
        return -1;
    }

    QDir dir(argv[1]);
    if(!dir.exists())
    {
        qDebug() << "source folder <" << argv[1] << "> does not exist!" << endl;
        return -1;
    }
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();
}
