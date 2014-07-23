/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.2.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionFramerate;
    QAction *actionExport;
    QAction *actionExit;
    QAction *actionStart;
    QAction *actionEnd;
    QWidget *centralWidget;
    QMenuBar *menuBar;
    QMenu *menuWebP_Magic;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(506, 439);
        MainWindow->setWindowOpacity(1);
        actionFramerate = new QAction(MainWindow);
        actionFramerate->setObjectName(QStringLiteral("actionFramerate"));
        actionExport = new QAction(MainWindow);
        actionExport->setObjectName(QStringLiteral("actionExport"));
        actionExit = new QAction(MainWindow);
        actionExit->setObjectName(QStringLiteral("actionExit"));
        actionStart = new QAction(MainWindow);
        actionStart->setObjectName(QStringLiteral("actionStart"));
        actionEnd = new QAction(MainWindow);
        actionEnd->setObjectName(QStringLiteral("actionEnd"));
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 506, 25));
        menuWebP_Magic = new QMenu(menuBar);
        menuWebP_Magic->setObjectName(QStringLiteral("menuWebP_Magic"));
        MainWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        mainToolBar->setFloatable(false);
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        MainWindow->setStatusBar(statusBar);

        menuBar->addAction(menuWebP_Magic->menuAction());
        menuWebP_Magic->addAction(actionFramerate);
        menuWebP_Magic->addAction(actionExport);
        menuWebP_Magic->addAction(actionExit);
        mainToolBar->addAction(actionStart);
        mainToolBar->addAction(actionEnd);
        mainToolBar->addAction(actionExport);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", 0));
        actionFramerate->setText(QApplication::translate("MainWindow", "Framerate", 0));
        actionExport->setText(QApplication::translate("MainWindow", "Export", 0));
        actionExit->setText(QApplication::translate("MainWindow", "Exit", 0));
        actionStart->setText(QApplication::translate("MainWindow", "Start", 0));
#ifndef QT_NO_TOOLTIP
        actionStart->setToolTip(QApplication::translate("MainWindow", "Start Capture", 0));
#endif // QT_NO_TOOLTIP
        actionEnd->setText(QApplication::translate("MainWindow", "End", 0));
        menuWebP_Magic->setTitle(QApplication::translate("MainWindow", "WebP Magic", 0));
        mainToolBar->setWindowTitle(QString());
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
