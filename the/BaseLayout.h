#ifndef BASELAYOUT_H
#define BASELAYOUT_H

#include <QLayout>
#include <QFontMetrics>
#include <QVideoWidget>
#include <QTextBrowser>

#include "SpButton.h"

#define R 30

class BaseLayout: public QLayout
{
public:
    QList<QLayoutItem*> items;
    qint64 sliderWidth = 1;
    bool mode;

    BaseLayout(): mode(true) { }

    ~BaseLayout() { }

    void setGeometry(const QRect& r) override
    {
        static bool first = true;

        const int wb = 24;
        const int gap = 6;
        const int w = r.width();
        const int UR = 50;

        const int videoWidth = 0.5 * w;
        const int videoHeight = 0.5 * w * 9 / 16;

        const int pWidth = (w - videoWidth - 4 * gap) / 2 * 0.75;
        const int pHeight = pWidth * 9 / 16;

        const int rWidth = (w - videoWidth - 4 * gap) / 2;
        const int rHeight = rWidth * 9 / 16;

        const int cWidth = 0.4 * w;
        const int cHeight = cWidth * 9 / 16;

        int warningCount = 0;
        int warningStart = 0;
        int userCount = 0;

        // Set geometry one by one
        for(auto i : this->items)
        {
            auto widget = i->widget();

            // Check if it is the control buttons
            SpButton* but = dynamic_cast<SpButton*>(widget);
            if(but)
            {
#define B(a, x, y, w, h) if(but->objectName()==a){but->setGeometry(x,y,w,h);continue;}
                B("PAUSE", gap + wb, 2 * gap + 60 + videoHeight, R, R);
                B("FULLSCREEN",
                    gap + videoWidth - R + wb,
                    2 * gap + 60 + videoHeight,
                    R,
                    R
                );
                B("VOLUME",
                    gap + wb,
                    3 * gap + 60 + R + videoHeight,
                    R,
                    R
                );
                B("BRIGHT",
                    3 * gap + R + (videoWidth - 3 * gap - 2 * R) / 2 + wb,
                    3 * gap + 60 + R + videoHeight,
                    R,
                    R
                );
                B("SWITCH",
                    videoWidth - 2 * R + wb,
                    2 * gap + 60 + videoHeight,
                    R,
                    R
                );
                B("ACC",
                    videoWidth - 3 * R - gap + wb,
                    2 * gap + 60 + videoHeight,
                    R,
                    R
                );
                B("DOWNLOAD",
                    gap + videoWidth - UR + (UR - R) / 2 + wb,
                    4 * gap + 60 + (UR - R) / 2 + 2 * R + videoHeight,
                    R,
                    R
                );
                B("P1" && this->mode,
                    2 * gap + videoWidth + 10 + wb,
                    gap + 60,
                    pWidth,
                    pHeight
                );
                B("P2" && this->mode,
                    2 * gap + videoWidth + 10 + wb,
                    2 * gap + 60 + pHeight,
                    pWidth,
                    pHeight
                );
                B("P3" && this->mode,
                    2 * gap + videoWidth + 10 + wb,
                    3 * gap + 60 + 2 * pHeight,
                    pWidth,
                    pHeight
                );
                B("R1" && this->mode,
                    w - gap - rWidth - wb,
                    60 + gap,
                    rWidth,
                    rHeight
                );
                B("R2" && this->mode,
                    w - gap - rWidth - wb,
                    60 + gap + (rHeight + 2 * gap + 30),
                    rWidth,
                    rHeight
                );
                B("R3" && this->mode,
                    w - gap - rWidth - wb,
                    60 + gap + (rHeight + 2 * gap + 30) * 2,
                    rWidth,
                    rHeight
                );
                B("P_C1" && !this->mode,
                    w - (w - videoWidth - 2 * wb) / 2 - 30,
                    60 + gap + cHeight / 2 - 30,
                    60,
                    60
                );
                B("P_C2" && !this->mode,
                    w - (w - videoWidth - 2 * wb) / 2 - 30,
                    60 + 2 * gap + 3 * cHeight / 2 - 30,
                    60,
                    60
                );

                but->setGeometry(-1, -1, 1, 1);
                continue;
#undef B
            }

            // Check if it is a label
            QLabel* label = dynamic_cast<QLabel*>(widget);
            if(label)
            {
#define B(a, x, y, w, h) if(label->objectName()==a){label->setGeometry(x,y,w,h);continue;}
                if(label->objectName() == "VIDEO_NAME")
                {
                    int maxWidth = 0.75 * w;
                    label->setGeometry(gap + wb, gap, maxWidth, 60);
                    QFontMetrics fm(label->font());
                    warningStart = 3 * gap + fm.width(label->text());
                    warningStart = maxWidth < warningStart ? maxWidth : warningStart;
                    continue;
                }
                B("WARNING",
                    warningStart + warningCount++ * (100 + gap) + wb,
                    gap + 15,
                    100,
                    30
                );
                // Video slider
                B("SLIDER_BACK",
                    2 * gap + R + wb,
                    2 * gap + 60 + videoHeight,
                    this->sliderWidth = videoWidth - 4 * (gap + R),
                    R
                );
                B("SLIDER_FRONT",
                    2 * gap + R + wb,
                    2 * gap + 60 + videoHeight,
                    label->width(),
                    30
                );
                B("VOLUME_BACK",
                    2 * gap + R + wb,
                    3 * gap + 60 + R + videoHeight,
                    (videoWidth - 3 * gap - 2 * R) / 2,
                    R
                );
                B("VOLUME_FRONT",
                    2 * gap + R + wb,
                    3 * gap + 60 + R + videoHeight,
                    first ? (videoWidth - 3 * gap - 2 * R) / 4 : label->width(),
                    R
                );
                B("BRIGHT_BACK",
                    4 * gap + 2 * R + (videoWidth - 3 * gap - 2 * R) / 2 + wb,
                    3 * gap + 60 + R + videoHeight,
                    (videoWidth - 3 * gap - 2 * R) / 2,
                    R
                );
                B("BRIGHT_FRONT",
                    4 * gap + 2 * R + (videoWidth - 3 * gap - 2 * R) / 2 + wb,
                    3 * gap + 60 + R + videoHeight,
                    (videoWidth - 3 * gap - 2 * R) / 2 * 0.8,
                    R
                );
                B("USER",
                    userCount * (gap + UR + 10) + gap + wb,
                    4 * gap + 60 + 2 * R + videoHeight,
                    UR,
                    UR
                );
                B("USER_MARK",
                    userCount++ * (gap + UR + 10) + gap + UR - 20 + wb,
                    4 * gap + 60 + 2 * R + videoHeight + UR - 20,
                    20,
                    20
                );
                B("BRIEF",
                    gap + wb,
                    4 * gap + 60 + 2 * R + videoHeight + UR + 10,
                    0.4 * videoWidth,
                    40
                );
                B("MAP",
                    2 * gap + 0.4 * videoWidth + wb,
                    4 * gap + 60 + 2 * R + videoHeight + UR + 10,
                    0.6 * videoWidth - gap,
                    180 + 40 + gap
                );
                B("M_P1" && this->mode,
                    2 * gap + videoWidth + pWidth - 20 + wb,
                    gap + 60 + pHeight - 20,
                    30,
                    20
                );
                B("M_P2" && this->mode,
                    2 * gap + videoWidth + pWidth - 20 + wb,
                    2 * gap + 60 + 2 * pHeight - 20,
                    30,
                    20
                );
                B("M_P3" && this->mode,
                    2 * gap + videoWidth + pWidth - 20 + wb,
                    3 * gap + 60 + 3 * pHeight - 20,
                    30,
                    20
                );
                B("T_R1" && this->mode,
                    w - gap - rWidth - wb,
                    gap + 60 + rHeight,
                    rWidth,
                    30
                );
                B("T_R2" && this->mode,
                    w - gap - rWidth - wb,
                    gap + 60 + rHeight + (rHeight + 30 + 2 * gap),
                    rWidth,
                    30
                );
                B("T_R3" && this->mode,
                    w - gap - rWidth - wb,
                    gap + 60 + rHeight + (rHeight + 30 + 2 * gap) * 2,
                    rWidth,
                    30
                );
                B("C1" && !this->mode,
                    w - cWidth - (w - videoWidth - cWidth - 2 * wb) / 2,
                    60 + gap,
                    cWidth,
                    cHeight
                );
                B("C2" && !this->mode,
                    w - cWidth - (w - videoWidth - cWidth - 2 * wb) / 2,
                    60 + 2 * gap + cHeight,
                    cWidth,
                    cHeight
                );

                label->setGeometry(-1, -1, 1, 1);
                continue;
            }

            // Check if it is the intro text
            QTextBrowser* intro = dynamic_cast<QTextBrowser*>(widget);
            if(intro)
            {
                intro->setGeometry(
                    gap + wb,
                    4 * gap + 60 + 2 * R + videoHeight + UR + 50,
                    0.4 * videoWidth,
                    150
                );
                continue;
            }

            // Check if it is the media player
            QVideoWidget* video = dynamic_cast<QVideoWidget*>(widget);
            if(video)
            {
                video->setGeometry(gap + wb, gap + 60, videoWidth, videoHeight);
                continue;
            }

            // Unarranged widget, hide it
            widget->setGeometry(-1, -1, 0, 0);
        }

        first = false;
    }

    QSize sizeHint() const override { return QSize(1280, 900); }

    void addItem(QLayoutItem* item) override { this->items.append(item); }

    QLayoutItem* itemAt(int i) const override { return this->items.value(i); }

    QLayoutItem* takeAt(int i) override { return this->items.takeAt(i); }

    int count() const override { return this->items.size(); }
};

#endif // BASELAYOUT_H
