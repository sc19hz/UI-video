/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.13.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSlider>
#include <QtWidgets/QWidget>
#include <video.h>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QPushButton *pushButton;
    QPushButton *pushButton_3;
    QPushButton *pushButton_4;
    Video *videoOutPut;
    QSlider *slider_process;
    QLabel *label;
    QSlider *slider_Volumn;
    QLabel *label_2;
    QSlider *horizontalSlider_3;
    QPushButton *pushButton_2;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(711, 634);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        pushButton = new QPushButton(centralWidget);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));
        pushButton->setGeometry(QRect(530, 560, 71, 41));
        pushButton->setMinimumSize(QSize(71, 41));
        pushButton->setMaximumSize(QSize(71, 41));
        pushButton_3 = new QPushButton(centralWidget);
        pushButton_3->setObjectName(QString::fromUtf8("pushButton_3"));
        pushButton_3->setGeometry(QRect(70, 490, 71, 41));
        pushButton_3->setMinimumSize(QSize(0, 0));
        pushButton_3->setMaximumSize(QSize(101, 41));
        pushButton_4 = new QPushButton(centralWidget);
        pushButton_4->setObjectName(QString::fromUtf8("pushButton_4"));
        pushButton_4->setGeometry(QRect(70, 560, 71, 41));
        pushButton_4->setMinimumSize(QSize(71, 41));
        pushButton_4->setMaximumSize(QSize(71, 41));
        videoOutPut = new Video(centralWidget);
        videoOutPut->setObjectName(QString::fromUtf8("videoOutPut"));
        videoOutPut->setEnabled(false);
        videoOutPut->setGeometry(QRect(78, 11, 524, 481));
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(videoOutPut->sizePolicy().hasHeightForWidth());
        videoOutPut->setSizePolicy(sizePolicy);
        slider_process = new QSlider(centralWidget);
        slider_process->setObjectName(QString::fromUtf8("slider_process"));
        slider_process->setGeometry(QRect(140, 491, 391, 31));
        slider_process->setOrientation(Qt::Horizontal);
        label = new QLabel(centralWidget);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(80, 530, 51, 21));
        slider_Volumn = new QSlider(centralWidget);
        slider_Volumn->setObjectName(QString::fromUtf8("slider_Volumn"));
        slider_Volumn->setGeometry(QRect(140, 530, 160, 22));
        slider_Volumn->setOrientation(Qt::Horizontal);
        label_2 = new QLabel(centralWidget);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(340, 530, 71, 21));
        horizontalSlider_3 = new QSlider(centralWidget);
        horizontalSlider_3->setObjectName(QString::fromUtf8("horizontalSlider_3"));
        horizontalSlider_3->setGeometry(QRect(420, 530, 160, 22));
        horizontalSlider_3->setOrientation(Qt::Horizontal);
        pushButton_2 = new QPushButton(centralWidget);
        pushButton_2->setObjectName(QString::fromUtf8("pushButton_2"));
        pushButton_2->setGeometry(QRect(530, 490, 71, 41));
        pushButton_2->setMinimumSize(QSize(71, 41));
        pushButton_2->setMaximumSize(QSize(71, 41));
        MainWindow->setCentralWidget(centralWidget);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        pushButton->setText(QCoreApplication::translate("MainWindow", "fullDisplay", nullptr));
        pushButton_3->setText(QCoreApplication::translate("MainWindow", "pause", nullptr));
        pushButton_4->setText(QCoreApplication::translate("MainWindow", "open", nullptr));
        label->setText(QCoreApplication::translate("MainWindow", "Volumn", nullptr));
        label_2->setText(QCoreApplication::translate("MainWindow", "brightness", nullptr));
        pushButton_2->setText(QCoreApplication::translate("MainWindow", "speed", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
