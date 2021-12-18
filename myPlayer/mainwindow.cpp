#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <QTimer>
#include <iostream>

bool play_state;

bool if_reload=false;

bool state_slider_volume = false;

bool full_screen = false;

QTimer *timer;          //播放计时器
int maxValue = 1000;    //进度条最大值


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    play = new QMediaPlayer();
    playList = new QMediaPlaylist();

    play->setPlaylist(playList);
    play->setVideoOutput(ui->videoOutPut);
    ui->pushButton_3->setEnabled(false);
    ui->pushButton_2->setEnabled(false);
    ui->pushButton->setEnabled(false);
    ui->slider_process->setEnabled(false);
    ui->slider_Volumn->setEnabled(false);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_4_clicked(bool checked)
{
    currentMediaFileName = QFileDialog::getOpenFileName(this, tr("Open File"), "/chantchan",
                                                    tr("Images (*.png *.xpm *.jpg), Media (*.mp4 *.*)"));

    playList->addMedia(QUrl::fromLocalFile(currentMediaFileName));
    playList->next();

    if(if_reload)
    {
        delete timer;
    }
    if_reload = true;
    play_state = true;
    ui->pushButton->setEnabled(true);
    ui->pushButton_2->setEnabled(true);
    ui->pushButton_3->setEnabled(true);
    ui->slider_process->setEnabled(true);
    ui->slider_process->setRange(0, maxValue);

    ui->slider_Volumn->setEnabled(true);
    timer = new QTimer();
    timer->setInterval(1000);
    timer->start();

    connect(timer, SIGNAL(timeout()), this, SLOT(onTimerOut()));

    ui->pushButton_3->setText("pause");
    play->play();
    qDebug() << "current choose " << currentMediaFileName;
}

void MainWindow::on_pushButton_2_clicked(bool checked)
{

}

void MainWindow::on_pushButton_3_clicked(bool checked)
{
    if(play_state)
    {
        play->pause();
        ui->pushButton_3->setText("start");
    }
    else{
        play->play();
        ui->pushButton_3->setText("pause");
    }
    play_state = !play_state;
}

void MainWindow::on_pushButton_pressed()
{
    ui->videoOutPut->setFullScreen(true);
//    if(full_screen)
//    {
//        ui->videoOutPut->setFullScreen(true);
//        ui->pushButton->setText("subscreen");
//    }
//    else
//    {
//        ui->videoOutPut->setFullScreen(false);
//        ui->pushButton->setText("fullscreen");
//    }
//    full_screen = !full_screen;
}

//void MainWindow::keyPressEvent(QKeyEvent *keyset)
//{
//    if(keyset->key()==Qt::Key_Escape)
//    {
//        std::cout << "get key escape event" << std::endl;

//        ui->videoOutPut->setFullScreen(false);
//        ui->videoOutPut->setWindowFlags(Qt::SubWindow);
//        ui->videoOutPut->showNormal();
//    }
//}
void MainWindow::onTimerOut()
{
    ui->slider_process->setValue(play->position() * maxValue / play->duration());
}

void MainWindow::slider_process_clicked()
{
    play->setPosition(ui->slider_process->value() * play->duration() / maxValue);
}


void MainWindow::slider_process_moved()
{
    timer->stop();
    play->setPosition(ui->slider_process->value() * play->duration() / maxValue);
}


void MainWindow::slider_process_released()
{
    timer->start();
}

void MainWindow::on_slider_process_sliderMoved()
{
    timer->stop();
    play->setPosition(ui->slider_process->value() * play->duration() / maxValue);
}

void MainWindow::on_slider_process_sliderReleased()
{
    timer->start();
}
