#include "mainwindow.h"
#include "dialog.h"
#include "loading.h"
#include "log.h"

#include <QApplication>
#include <string>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    Dialog d;
    Loading l;
    //Log log;

    //log.show();

    //l.show();
    //d.show();
    w.show();
    return a.exec();
}
