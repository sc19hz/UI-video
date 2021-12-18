#ifndef VIDEO_H
#define VIDEO_H

#include <QWidget>
#include <QVideoWidget>
#include <QKeyEvent>
#include <iostream>

class Video : public QVideoWidget
{
    Q_OBJECT
public:
    explicit Video(QWidget *parent = nullptr);

signals:

public slots:

    //overwrite Keyboard

    void keyPressEvent(QKeyEvent *event)
    {
        std::cout << "video key event " << std::endl;
        if(event->key() == Qt::Key_Escape)
        {
            this->setFullScreen(false);

        }
    }
};

#endif // VIDEO_H
