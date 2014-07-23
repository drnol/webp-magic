/*
 *
 * main window body
 *
 * @author: drnol
 * @license:    Apache License 2.0\nhttp://www.apache.org/licenses/LICENSE-2.0
 * @contact:    rho@codeminds.co.kr
 *
 */

#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QtGui>
#include <QToolButton>
#include <QScreen>
#include <QPixmap>


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    timer = NULL;
    frame_interval = 1000/24; // default: 24fps

    ui->setupUi(this);
}

void MainWindow::resizeEvent(QResizeEvent*)
{
    QRegion full(rect().left(),rect().top(),rect().width(),rect().height(),QRegion::Rectangle);
    QRegion internal(rect().left()+5,rect().top()+30,rect().width()-10,rect().height()-35,QRegion::Rectangle);
    QRegion clipped = full.xored(internal);

    setMask(clipped);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionFramerate_triggered()
{

}

void MainWindow::on_actionStart_triggered()
{
    this->start_capture();
}

void MainWindow::on_actionEnd_triggered()
{
    this->end_capture();
}

void MainWindow::start_capture()
{
    if(timer == NULL)
    {
        capture_num=0;
        timer = new QTimer(this);
        connect(timer, SIGNAL(timeout()), this, SLOT(tick()));
        timer->start(frame_interval);
    }
}

void MainWindow::tick()
{
    QString path = QString("./tmp-%1.png").arg(QString::number(this->capture_num));
    capture(path);
    capture_num++;
}

void MainWindow::end_capture()
{

    if(timer != NULL)
    {
        timer->stop();
        delete timer;
        timer = NULL;
    }
}

// TODO: change save format from '.png' to '.webp'
void MainWindow::capture(QString &path)
{
    qDebug() << path;
    QImageWriter imgWriter(path,"png");
    QImage PngImage;

    QScreen *screen = QGuiApplication::primaryScreen();
    QPixmap snapshot = screen->grabWindow(this->winId(),
                                           rect().left()+5,rect().top()+30,
                                           rect().width()-10,rect().height()-35);
    PngImage = snapshot.toImage();
    imgWriter.write(PngImage);
}

// TODO: mux created temporal '.webp' files
void MainWindow::on_actionExport_triggered()
{

}
