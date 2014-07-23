/*
 *
 * main window header
 *
 * @author: drnol
 * @license:    Apache License 2.0\nhttp://www.apache.org/licenses/LICENSE-2.0
 * @contact:    rho@codeminds.co.kr
 *
 */

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QList>
#include <QImage>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    virtual void resizeEvent(QResizeEvent*);
    ~MainWindow();

private slots:
    void on_actionFramerate_triggered();

    void on_actionStart_triggered();

    void on_actionEnd_triggered();

    void start_capture();
    void end_capture();
    void capture();

    void tick();

    void on_actionExport_triggered();
    void mux(int count, int interval);

private:
    Ui::MainWindow *ui;
    int frame_interval;
    int capture_num;
    QTimer *timer;
    QList<QImage> *frames;
};

#endif // MAINWINDOW_H
