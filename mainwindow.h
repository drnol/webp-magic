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
#include <QThread>
#include <QProgressBar>

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
    void export_process();

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

    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);

    void update_progress();
    void export_finalize();

    void on_actionLow_triggered();

    void on_actionBest_triggered();

    void on_actionHigh_triggered();

    void on_actionNormal_triggered();

signals:
    void update_signal();
    void finalize_signal();

private:
    Ui::MainWindow *ui;
    int frame_interval;
    int quality;
    int capture_num;
    QTimer *timer;
    QList<QImage> *frames;
    int m_nMouseClick_X_Coordinate;
    int m_nMouseClick_Y_Coordinate;
    bool moving;
    QThread *export_thread;
    QProgressBar *progressBar;
};

#endif // MAINWINDOW_H
