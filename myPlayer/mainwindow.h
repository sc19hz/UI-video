#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFileDialog>
#include <QMediaPlaylist>
#include <QMediaPlayer>
#include "video.h"
#include "the_button.h"

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

    void on_thebutton_1_clicked(bool checked);

    void on_thebutton_2_clicked(bool checked);

    void on_thebutton_3_clicked(bool checked);

private:
    Ui::MainWindow *ui;
    QString currentMediaFileName;
    QMediaPlayer *play;
    QMediaPlaylist *playList;

    QMediaPlayer *play_1;
    QMediaPlaylist *playList_1;
    QMediaPlayer *play_2;
    QMediaPlaylist *playList_2;
    std::vector<TheButtonInfo> videos;
};

#endif // MAINWINDOW_H
