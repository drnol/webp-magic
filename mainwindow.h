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
    void capture(QString &path);

    void tick();

    void on_actionExport_triggered();

private:
    Ui::MainWindow *ui;
    int frame_interval;
    int capture_num;
    QTimer *timer;
};

#endif // MAINWINDOW_H
