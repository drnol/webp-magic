/*
 *
 * A simple application which is create animated WebP from screen capture.
 *
 * @author: drnol
 * @license:    Apache License 2.0\nhttp://www.apache.org/licenses/LICENSE-2.0
 * @contact:    rho@codeminds.co.kr
 *
 */

#include "mainwindow.h"
#include <QApplication>
//#include <QtPlugin>

//Q_IMPORT_PLUGIN(qlibwebp)

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();
}
