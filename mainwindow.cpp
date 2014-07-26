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
#include <QList>
#include <QListIterator>
#include <QDesktopWidget>
#include <QThread>
#include <QStatusBar>
#include <QObject>
#include <QSizeGrip>
#include <QDir>

const int TOP_MARGIN = 70;
const int BOT_MARGIN = 22;

class ExportThread:public QThread {
    MainWindow *owner;

public:
    ExportThread(MainWindow *owner) { this->owner = owner; }
    virtual void run() {
        owner->export_process();
    }
};

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    moving = false;
    timer = NULL;

    ui->setupUi(this);
    setWindowFlags(Qt::WindowStaysOnTopHint | Qt::FramelessWindowHint);

    ui->actionStart->setEnabled(true);
    ui->actionEnd->setEnabled(false);
    ui->actionExport->setEnabled(false);

    setStyleSheet("background-color: blue;");
    ui->qsBox->setStyleSheet("background-color: white;");
    ui->fpsBox->setStyleSheet("background-color: white;");
    ui->nameEdit->setStyleSheet("background-color: white;");
    ui->speedBox->setStyleSheet("background-color: white;");
    ui->label->setStyleSheet("color: white;");
    ui->label_2->setStyleSheet("color: white;");
    ui->label_3->setStyleSheet("color: white;");
    ui->label_4->setStyleSheet("color: white;");

    progressBar=new QProgressBar();
    ui->mainToolBar->addWidget(progressBar);

    ui->nameEdit->setText(QDir::homePath()+"/output");

    export_thread = new ExportThread(this);
    QObject::connect(this, SIGNAL(update_signal()), this, SLOT(update_progress()));    
    QObject::connect(this, SIGNAL(finalize_signal()), this, SLOT(export_finalize()));

    QSizeGrip *sg = new QSizeGrip(this);
    ui->statusBar->addWidget(sg, 1);
}

void MainWindow::resizeEvent(QResizeEvent*)
{
    moving = false;

    QRegion full(rect().left(),rect().top(),rect().width(),rect().height(),QRegion::Rectangle);
    QRegion internal(rect().left()+5,rect().top()+TOP_MARGIN,rect().width()-10,rect().height()-TOP_MARGIN-BOT_MARGIN,QRegion::Rectangle);
    QRegion clipped = full.xored(internal);

    ui->horizontalLayout->update();

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
        ui->actionStart->setEnabled(false);
        ui->actionEnd->setEnabled(true);

        quality = this->ui->qsBox->value();
        frame_interval = 1000/this->ui->fpsBox->value();

        timer = new QTimer(this);
        frames = new QList<QImage>();
        connect(timer, SIGNAL(timeout()), this, SLOT(tick()));
        timer->start(frame_interval);
    }
}

void MainWindow::tick()
{
    capture();
}

void MainWindow::mux(int count, int interval)
{
    QStringList args;
    QString intarg = QString("+%1+0+0").arg(QString::number(interval));
    for(int i=0; i<count; i++)
    {
        QString path = QString("./tmp-%1.webp").arg(QString::number(i));
        args.append("-frame");
        args.append(path);
        args.append(intarg);
    }

    args.append("-loop");
    args.append("0");
    args.append("-o");
    args.append(ui->nameEdit->text()+".webp");

    QProcess::execute("webpmux", args);
}

void MainWindow::export_process()
{
    // save to webp file
    QListIterator<QImage> itr(*frames);

    int i = 0;
    while(itr.hasNext())
    {
        QString path = QString("./tmp-%1.webp").arg(QString::number(i));
        qDebug() << path;
        itr.next().save(path,"webp",quality);
        i++;

        emit update_signal();
    }

    // mux
    this->mux(frames->count(), (float)frame_interval/ui->speedBox->value());

    delete frames;
    frames = NULL;

    // unlock safe prevention --
    emit finalize_signal();
    timer = NULL;
}

void MainWindow::export_finalize()
{
    ui->actionStart->setEnabled(true);
}

void MainWindow::update_progress()
{
    progressBar->setValue(progressBar->value()+1);
}

void MainWindow::end_capture()
{
    if(timer != NULL)
    {
        timer->stop();
        delete timer;

        ui->actionStart->setEnabled(false);
        ui->actionEnd->setEnabled(false);


        progressBar->setMaximum(frames->count());
        progressBar->setValue(0);
        export_thread->start();
    }
}

void MainWindow::capture()
{
    qDebug() << QString("Capture frame %1").arg(QString::number(frames->count()));

    QScreen *screen = QGuiApplication::primaryScreen();

#ifdef Q_OS_WIN32
    QPixmap snapshot = screen->grabWindow(QApplication::desktop()->winId(),
                                          this->pos().x()+5,this->pos().y()+TOP_MARGIN,
                                           rect().width()-10,rect().height()-TOP_MARGIN-BOT_MARGIN);
#endif
#ifndef Q_OS_WIN32
    QPixmap snapshot = screen->grabWindow(this->winId(),
                                           rect().left()+5,rect().top()+TOP_MARGIN,
                                           rect().width()-10,rect().height()-TOP_MARGIN-BOT_MARGIN);
#endif
    frames->append(snapshot.toImage());
}

// TODO: mux created temporal '.webp' files
void MainWindow::on_actionExport_triggered()
{

}

void MainWindow::mousePressEvent(QMouseEvent *event) {
    moving = true;
    m_nMouseClick_X_Coordinate = event->x();
    m_nMouseClick_Y_Coordinate = event->y();
}

void MainWindow::mouseMoveEvent(QMouseEvent *event) {
    if(moving)
        move(event->globalX()-m_nMouseClick_X_Coordinate,event->globalY()-m_nMouseClick_Y_Coordinate);
}

void MainWindow::on_actionLow_triggered()
{
    ui->qsBox->setValue(60);
    ui->fpsBox->setValue(16);
}

void MainWindow::on_actionBest_triggered()
{
    ui->qsBox->setValue(100);
    ui->fpsBox->setValue(60);
}

void MainWindow::on_actionHigh_triggered()
{
    ui->qsBox->setValue(90);
    ui->fpsBox->setValue(48);
}

void MainWindow::on_actionNormal_triggered()
{
    ui->qsBox->setValue(80);
    ui->fpsBox->setValue(24);
}
