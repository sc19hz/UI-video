#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFileDialog>
#include <QMediaPlaylist>
#include <QMediaPlayer>
#include "video.h"


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_pushButton_4_clicked(bool checked); // open video file

    void on_pushButton_2_clicked(bool checked); // start play media

    void on_pushButton_3_clicked(bool checked); // pause video

    void on_pushButton_pressed(); // full screen

    void onTimerOut();

    void slider_process_clicked();

    void slider_process_moved();

    void slider_process_released();

    void on_slider_process_sliderMoved();

    void on_slider_process_sliderReleased();

//    void keyPressEvent(QKeyEvent *keyset);

private:
    Ui::MainWindow *ui;
    QString currentMediaFileName;
    QMediaPlayer *play;
    QMediaPlaylist *playList;
};

#endif // MAINWINDOW_H
