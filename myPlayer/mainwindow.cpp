#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <QTimer>
#include <iostream>
#include <QImageReader>
#include <QtCore/QDirIterator>

bool play_state;

bool play_1_state = false;

bool play_2_state = false;

bool if_reload=false;

bool state_slider_volume = false;

bool full_screen = false;

QTimer *timer;          //播放计时器
int maxValue = 1000;    //进度条最大值


std::vector<TheButtonInfo> getInfoIn (std::string loc) {

    std::vector<TheButtonInfo> out =  std::vector<TheButtonInfo>();
    QDir dir(QString::fromStdString(loc) );
    QDirIterator it(dir);

    while (it.hasNext()) { // for all files

        QString f = it.next();

            if (f.contains("."))

#if defined(_WIN32)
            if (f.contains(".wmv"))  { // windows
#else
            if (f.contains(".mp4") || f.contains("MOV"))  { // mac/linux
#endif

            QString thumb = f.left( f .length() - 4) +".png";
            if (QFile(thumb).exists()) { // if a png thumbnail exists
                QImageReader *imageReader = new QImageReader(thumb);
                    QImage sprite = imageReader->read(); // read the thumbnail
                    if (!sprite.isNull()) {
                        QIcon* ico = new QIcon(QPixmap::fromImage(sprite)); // voodoo to create an icon for the button
                        QUrl* url = new QUrl(QUrl::fromLocalFile( f )); // convert the file location to a generic url
                        out . push_back(TheButtonInfo( url , ico  ) ); // add to the output list
                    }
                    else
                        qDebug() << "warning: skipping video because I couldn't process thumbnail " << thumb << endl;
            }
            else
                qDebug() << "warning: skipping video because I couldn't find thumbnail " << thumb << endl;
        }
    }

    return out;
}


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    play = new QMediaPlayer();
    playList = new QMediaPlaylist();
    play->setPlaylist(playList);
    play->setVideoOutput(ui->videoOutPut);

    play_1 = new QMediaPlayer();
    playList_1 = new QMediaPlaylist();
    play_1->setPlaylist(playList_1);
    play_1->setVideoOutput(ui->videoOutPut_1);

    play_2 = new QMediaPlayer();
    playList_2 = new QMediaPlaylist();
    play_2->setPlaylist(playList_2);
    play_2->setVideoOutput(ui->videoOutPut_2);

    ui->pushButton_3->setEnabled(false);
    ui->pushButton_2->setEnabled(false);
    ui->pushButton->setEnabled(false);
    ui->slider_process->setEnabled(false);
    ui->slider_Volumn->setEnabled(false);
    videos = getInfoIn("/Users/chantchan/grade3/User Interface/coursework3/videos");
    std::cout << videos.size() << std::endl;

    ui->thebutton_1->init(&videos.at(1));
    ui->thebutton_2->init(&videos.at(2));
    ui->thebutton_3->init(&videos.at(3));

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

void MainWindow::on_thebutton_1_clicked(bool checked)
{

    if(play_1_state)
    {
        play_1->pause();
    }
    else
    {
        playList_1->addMedia(QMediaContent(*(ui->thebutton_1->info->url)));
        playList_1->next();
        play_1->play();
    }
    play_1_state = !play_1_state;

//    ui->thebutton_1->info->url
}

void MainWindow::on_thebutton_2_clicked(bool checked)
{
    if(play_2_state)
    {
        play_2->pause();
    }
    else
    {
        playList_2->addMedia(QMediaContent(*(ui->thebutton_2->info->url)));
        playList_2->next();
        play_2->play();
    }
    play_2_state = !play_2_state;
}
