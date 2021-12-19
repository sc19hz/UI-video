#ifndef CLASSEDBUTTON_H
#define CLASSEDBUTTON_H

#include <QLabel>
#include <QUrl>
#include <QTimer>

class SpButton: public QLabel
{
    Q_OBJECT

public:
    bool state = false;
    QString icon1;
    QString icon2;

    SpButton(
        const QString& icon1,
        const QString& icon2
    ): icon1(icon1), icon2(icon2)
    {
        this->setPixmap(QPixmap(icon1));
        this->setScaledContents(true);
    }

    SpButton(
        const QString& icon
    ): SpButton(icon, icon) { }

    ~SpButton() { }

    void mouseReleaseEvent(QMouseEvent*) override {
        this->togglePause();
    }

    void togglePause()
    {
        // Switch icon on click
        this->setPixmap(
            QPixmap(
                    (this->state = !this->state)
                    ? this->icon2
                    : this->icon1
            )
        );
        emit SIG_onClick(this->state, this->objectName());
    }

signals:
    void SIG_onClick(bool state, const QString& name);
};

#endif // CLASSEDBUTTON_H
