#ifndef WINTOMEO_H
#define WINTOMEO_H

#include <exception>

#include <QWidget>
#include <QVideoWidget>
#include <QMediaPlayer>
#include <QFile>
#include <QImage>
#include <QImageReader>
#include <QIcon>
#include <QPixmap>
#include <QVBoxLayout>
#include <QKeyEvent>
#include <QMessageBox>
#include <QTextBrowser>

#include "BaseLayout.h"
#include "StyleHelper.h"
#include "SpButton.h"

class WinTomeo: public QWidget
{
    Q_OBJECT

public:
    QLabel* videoTitle;
    QMediaPlayer* mediaDecoder;
    QVideoWidget* playerWin;
    SpButton* But_pause;
    QLabel* sliderFront;
    QLabel* sliderBack;
    QLabel* volumeFront;
    QLabel* volumeBack;
    QLabel* brightFront;
    QLabel* brightBack;
    BaseLayout* lay;

    QString srcDir;

    qint64 dur;

    WinTomeo(const QString& srcDir): srcDir(srcDir), dur(1)
    {
		// Set attributes
        this->setWindowTitle("Tomeo");
        this->setStyleSheet(BACKGROUD_COLOR("#ffffff"));
        this->setFixedWidth(1280);
        this->setFixedHeight(800);

#ifndef _WIN32
                this->setFocusPolicy(Qt::StrongFocus);
#endif

        // Base layout
        this->lay = new BaseLayout();
        this->setLayout(this->lay);

        /* Video title label */
        {
            this->videoTitle = new QLabel();
            this->videoTitle->setObjectName("VIDEO_NAME");
            this->videoTitle->setStyleSheet(
                NO_BORDER()
                FONT("Arial")
                FONT_SIZE("40px")
                BACKGROUD_COLOR("rgba(0,0,0,0)")
            );
            this->lay->addWidget(this->videoTitle);
        }

        /* Warning tags */
        {
            QLabel* Tag_bodyDamage = new QLabel("BODY DAMAGE");
            Tag_bodyDamage->setObjectName("WARNING");
            Tag_bodyDamage->setStyleSheet(
                NO_BORDER()
                BOLD()
                FONT("Arial")
                BORDER_RADIUS("15px")
                BACKGROUD_COLOR("#f33333")
                COLOR("#ffffff")
            );
            Tag_bodyDamage->setAlignment(Qt::AlignCenter);
            this->lay->addWidget(Tag_bodyDamage);

            QLabel* Tag_adultsOnly = new QLabel("ADULTS ONLY");
            Tag_adultsOnly->setObjectName("WARNING");
            Tag_adultsOnly->setStyleSheet(
                NO_BORDER()
                BOLD()
                FONT("Arial")
                BORDER_RADIUS("15px")
                BACKGROUD_COLOR("#ffcc55")
                COLOR("#ffffff")
            );
            Tag_adultsOnly->setAlignment(Qt::AlignCenter);
            this->lay->addWidget(Tag_adultsOnly);

            QLabel* Tag_noImitate = new QLabel("NO IMITATE");
            Tag_noImitate->setObjectName("WARNING");
            Tag_noImitate->setStyleSheet(
                NO_BORDER()
                BOLD()
                FONT("Arial")
                BORDER_RADIUS("15px")
                BACKGROUD_COLOR("#dd55dd")
                COLOR("#ffffff")
            );
            Tag_noImitate->setAlignment(Qt::AlignCenter);
            this->lay->addWidget(Tag_noImitate);
        }

        QString backStyle =
            BORDER_WIDTH("1px")
            BORDER_COLOR("#999999")
            BORDER_RADIUS("5px")
            BORDER_STYLE("solid")
            BACKGROUD_COLOR("#dddddd");
        /* Video slider */
        {
            this->sliderBack = new QLabel();
            this->sliderBack->setObjectName("SLIDER_BACK");
            this->sliderBack->setStyleSheet(backStyle);
            this->sliderBack->installEventFilter(this);
            this->lay->addWidget(this->sliderBack);

            this->sliderFront = new QLabel();
            this->sliderFront->setObjectName("SLIDER_FRONT");
            this->sliderFront->setStyleSheet(
                BORDER_WIDTH("1px")
                BORDER_COLOR("#2277cc")
                BORDER_RADIUS("5px")
                BORDER_STYLE("solid")
                BACKGROUD_COLOR("#33aaff")
            );
            this->sliderFront->installEventFilter(this);
            this->lay->addWidget(this->sliderFront);
        }

        /* Volume slider */
        {
            this->volumeBack = new QLabel();
            this->volumeBack->setObjectName("VOLUME_BACK");
            this->volumeBack->setStyleSheet(backStyle);
            this->volumeBack->installEventFilter(this);
            this->lay->addWidget(this->volumeBack);

            this->volumeFront = new QLabel();
            this->volumeFront->setObjectName("VOLUME_FRONT");
            this->volumeFront->setStyleSheet(
                BORDER_WIDTH("1px")
                BORDER_COLOR("#11aa33")
                BORDER_RADIUS("5px")
                BORDER_STYLE("solid")
                BACKGROUD_COLOR("#22ee55")
            );
            this->volumeFront->installEventFilter(this);
            this->lay->addWidget(this->volumeFront);
        }

        /* Brightness slider */
        {
            this->brightBack = new QLabel();
            this->brightBack->setObjectName("BRIGHT_BACK");
            this->brightBack->setStyleSheet(backStyle);
            this->brightBack->installEventFilter(this);
            this->lay->addWidget(this->brightBack);

            this->brightFront = new QLabel();
            this->brightFront->setObjectName("BRIGHT_FRONT");
            this->brightFront->setStyleSheet(
                BORDER_WIDTH("1px")
                BORDER_COLOR("#ddaa22")
                BORDER_RADIUS("5px")
                BORDER_STYLE("solid")
                BACKGROUD_COLOR("#ffee55")
            );
            this->brightFront->installEventFilter(this);
            this->lay->addWidget(this->brightFront);
        }

        /* Video widget */
        {
            this->mediaDecoder = new QMediaPlayer();
            this->mediaDecoder->
            connect(
                this->mediaDecoder,
                SIGNAL(stateChanged(QMediaPlayer::State)),
                this,
                SLOT(SLT_pausePlayer(QMediaPlayer::State))
            );
            connect(
                this->mediaDecoder,
                SIGNAL(mediaChanged(const QMediaContent&)),
                this,
                SLOT(SLT_updateMedia(const QMediaContent&))
            );
            connect(
                this->mediaDecoder,
                SIGNAL(durationChanged(qint64)),
                this,
                SLOT(SLT_updateDur(qint64))
            );
            connect(
                this->mediaDecoder,
                SIGNAL(positionChanged(qint64)),
                this,
                SLOT(SLT_updateSlider(qint64))
            );
            this->mediaDecoder->setNotifyInterval(25);

            this->mediaDecoder->setVideoOutput(this->playerWin = new QVideoWidget());
            this->playerWin->setStyleSheet(BACKGROUD_COLOR("#000000"));
            this->playerWin->installEventFilter(this);
            this->lay->addWidget(playerWin);

            this->mediaDecoder->setMedia(
                QUrl::fromLocalFile(
                    srcDir +
#ifdef _WIN32
                    "/a.wmv"
#else
                    "/a.MOV"
#endif
                )
            );
            this->mediaDecoder->play();
            this->mediaDecoder->pause();
            this->mediaDecoder->setVolume(50);
        }

        /* Video control buttons */
        {
            // Pause button
            this->But_pause = new SpButton(
                srcDir + "/play.png",
                srcDir + "/pause.png"
            );
            this->But_pause->setObjectName("PAUSE");
            QString style =
                BORDER_WIDTH("1px")
                BORDER_COLOR("#aaaaaa")
                BORDER_RADIUS("5px")
                BORDER_STYLE("solid")
                BACKGROUD_COLOR("#dddddd");
            this->But_pause->setStyleSheet(style);
            this->lay->addWidget(this->But_pause);
            connect(this->But_pause, SIGNAL(SIG_onClick(bool, const QString&)), this, SLOT(SLT_pauseClicked(bool)));

            // Fullscreen button
            SpButton* But_fullscreen = new SpButton(srcDir + "/fullscreen.png");
            But_fullscreen->setObjectName("FULLSCREEN");
            But_fullscreen->setStyleSheet(style);
            this->lay->addWidget(But_fullscreen);
            connect(But_fullscreen, SIGNAL(SIG_onClick(bool, const QString&)), this, SLOT(SLT_showFullscreen(bool)));

            // Volume button
            SpButton* But_volume = new SpButton(srcDir + "/volume.png");
            But_volume->setObjectName("VOLUME");
            But_volume->setStyleSheet(style);
            this->lay->addWidget(But_volume);

            // Brightness button
            SpButton* But_brightness = new SpButton(srcDir + "/brightness.png");
            But_brightness->setObjectName("BRIGHT");
            But_brightness->setStyleSheet(style);
            this->lay->addWidget(But_brightness);

            // Camera mode button
            SpButton* But_switch = new SpButton(srcDir + "/mult.png", srcDir + "/single.png");
            But_switch->setObjectName("SWITCH");
            But_switch->setStyleSheet(style);
            this->lay->addWidget(But_switch);
            connect(
                But_switch,
                SIGNAL(SIG_onClick(bool, const QString&)),
                this,
                SLOT(SLT_switchMode(bool))
            );

            // Accelerate button
            SpButton* But_acc = new SpButton(srcDir + "/acc.png", srcDir + "/norm.png");
            But_acc->setObjectName("ACC");
            But_acc->setStyleSheet(style);
            this->lay->addWidget(But_acc);
            connect(
                But_acc,
                SIGNAL(SIG_onClick(bool, const QString&)),
                this,
                SLOT(SLT_toggleAcc(bool))
            );

            // Download button
            SpButton* But_download = new SpButton(srcDir + "/download.png");
            But_download->setObjectName("DOWNLOAD");
            this->lay->addWidget(But_download);
        }

        /* User icons */
        {
            QLabel* user = new QLabel();
            user->setObjectName("USER");
            QString style = BORDER_RADIUS("25px") BACKGROUD_COLOR("#dddddd");
            user->setStyleSheet(style);
            user->setPixmap(QPixmap(srcDir + "/user.png"));
            user->setScaledContents(true);
            this->lay->addWidget(user);

            user = new QLabel("M");
            user->setObjectName("USER_MARK");
            QString style2 =
                COLOR("#ffffff")
                FONT_SIZE("14px")
                FONT("Arial")
                BACKGROUD_COLOR("#f33333")
                BORDER_RADIUS("10px");
            user->setStyleSheet(style2);
            user->setAlignment(Qt::AlignCenter);
            this->lay->addWidget(user);

            user = new QLabel();
            user->setObjectName("USER");
            user->setStyleSheet(style);
            user->setPixmap(QPixmap(srcDir + "/user.png"));
            user->setScaledContents(true);
            this->lay->addWidget(user);

            user = new QLabel("S");
            user->setObjectName("USER_MARK");
            user->setStyleSheet(style2);
            user->setAlignment(Qt::AlignCenter);
            this->lay->addWidget(user);

            user = new QLabel();
            user->setObjectName("USER");
            user->setStyleSheet(style);
            user->setPixmap(QPixmap(srcDir + "/user.png"));
            user->setScaledContents(true);
            this->lay->addWidget(user);

            user = new QLabel("S");
            user->setObjectName("USER_MARK");
            user->setStyleSheet(style2);
            user->setAlignment(Qt::AlignCenter);
            this->lay->addWidget(user);
        }

        /* Intro */
        {
            QLabel* brief = new QLabel("Brief Introduction");
            brief->setObjectName("BRIEF");
            brief->setStyleSheet(
                BOLD()
                FONT_SIZE("20px")
                FONT("Arial")
            );
            this->lay->addWidget(brief);

            QTextBrowser* intro = new QTextBrowser();
            intro->insertPlainText("asdga vmcyg yuqiern uoxngu lhdfshj qnxg xjgau zjgan gfdhe");
            intro->setStyleSheet(
                FONT("Arial")
                NO_BORDER()
                //BACKGROUD_COLOR("#eeeeee")
                //BORDER_RADIUS("5px")
            );
            this->lay->addWidget(intro);
        }

        /* Map */
        {
            QLabel* map = new QLabel();
            map->setObjectName("MAP");
            map->setPixmap(srcDir + "/map.png");
            //map->setScaledContents(true);
            //map->setStyleSheet(BACKGROUD_COLOR("#eeeeee"));
            map->setAlignment(Qt::AlignCenter);
            this->lay->addWidget(map);
        }

        /* Parts */
        {
            SpButton* p = new SpButton(srcDir + "/a.png");
            p->setObjectName("P1");
            connect(
                p,
                SIGNAL(SIG_onClick(bool, const QString&)),
                this,
                SLOT(SLT_switchMedia(bool, const QString&))
            );
            this->lay->addWidget(p);

            QLabel* p1 = new QLabel("P1");
            p1->setObjectName("M_P1");
            QString style = BOLD() FONT("Arial") BACKGROUD_COLOR("#888888") COLOR("#ffffff");
            p1->setStyleSheet(style);
            p1->setAlignment(Qt::AlignCenter);
            this->lay->addWidget(p1);

            p = new SpButton(srcDir + "/b.png");
            p->setObjectName("P2");
            connect(
                p,
                SIGNAL(SIG_onClick(bool, const QString&)),
                this,
                SLOT(SLT_switchMedia(bool, const QString&))
            );
            this->lay->addWidget(p);

            p1 = new QLabel("P2");
            p1->setObjectName("M_P2");
            p1->setStyleSheet(style);
            p1->setAlignment(Qt::AlignCenter);
            this->lay->addWidget(p1);

            p = new SpButton(srcDir + "/c.png");
            p->setObjectName("P3");
            connect(
                p,
                SIGNAL(SIG_onClick(bool, const QString&)),
                this,
                SLOT(SLT_switchMedia(bool, const QString&))
            );
            this->lay->addWidget(p);

            p1 = new QLabel("P3");
            p1->setObjectName("M_P3");
            p1->setStyleSheet(style);
            p1->setAlignment(Qt::AlignCenter);
            this->lay->addWidget(p1);
        }

        /* Recommend */
        {
            SpButton* r = new SpButton(srcDir + "/d.png");
            r->setObjectName("R1");
            connect(
                r,
                SIGNAL(SIG_onClick(bool, const QString&)),
                this,
                SLOT(SLT_switchMedia(bool, const QString&))
            );
            this->lay->addWidget(r);

            QLabel* r1 = new QLabel("Recommend video 1");
            r1->setObjectName("T_R1");
            QString style = FONT("Arial") FONT_SIZE("20px");
            r1->setStyleSheet(style);
            this->lay->addWidget(r1);

            r = new SpButton(srcDir + "/e.png");
            r->setObjectName("R2");
            connect(
                r,
                SIGNAL(SIG_onClick(bool, const QString&)),
                this,
                SLOT(SLT_switchMedia(bool, const QString&))
            );
            this->lay->addWidget(r);

            r1 = new QLabel("Titled video 2");
            r1->setObjectName("T_R2");
            r1->setStyleSheet(style);
            this->lay->addWidget(r1);

            r = new SpButton(srcDir + "/f.png");
            r->setObjectName("R3");
            connect(
                r,
                SIGNAL(SIG_onClick(bool, const QString&)),
                this,
                SLOT(SLT_switchMedia(bool, const QString&))
            );
            this->lay->addWidget(r);

            r1 = new QLabel("Video of index 3");
            r1->setObjectName("T_R3");
            r1->setStyleSheet(style);
            this->lay->addWidget(r1);
        }

        /* Extra camera */
        {
            QLabel* c = new QLabel;
            c->setObjectName("C1");
            c->setStyleSheet(BACKGROUD_COLOR("#000000"));
            this->lay->addWidget(c);

            SpButton* cp = new SpButton(srcDir + "/play.png");
            cp->setObjectName("P_C1");
            cp->setStyleSheet(BORDER_RADIUS("30px"));
            this->lay->addWidget(cp);

            c = new QLabel;
            c->setObjectName("C2");
            c->setStyleSheet(BACKGROUD_COLOR("#000000"));
            this->lay->addWidget(c);

            cp = new SpButton(srcDir + "/play.png");
            cp->setObjectName("P_C2");
            cp->setStyleSheet(BORDER_RADIUS("30px"));
            this->lay->addWidget(cp);
        }
    }

    ~WinTomeo() { }

    void keyPressEvent(QKeyEvent *evt) override
    {
        switch(evt->key())
        {
        case Qt::Key_Space:
            this->But_pause->togglePause();
        default: break;
        }
    }

    bool eventFilter(QObject* o, QEvent* e) override
    {
        if(o == this->playerWin)
        {
            if(e->type() != QEvent::KeyPress) return false;

            switch((static_cast<QKeyEvent*>(e))->key())
            {
            case Qt::Key_Escape:
                this->playerWin->setWindowFlags(Qt::SubWindow);
                this->playerWin->showNormal();
                break;
            case Qt::Key_Space:
                this->But_pause->togglePause();
                break;
            }
        }
        else if(o == this->sliderBack || o == this->sliderFront)
        {
            QEvent::Type eType = e->type();
            if(
                eType == QEvent::MouseButtonRelease
                || eType == QEvent::MouseMove
                || eType == QEvent::MouseButtonPress
            ) {
                int x = (static_cast<QMouseEvent*>(e))->x();
                int maxX = this->sliderBack->width();
                x = x > 10 ? x > maxX ? maxX : x : 10;

                this->sliderFront->setGeometry(
                    this->sliderFront->x(),
                    this->sliderFront->y(),
                    x,
                    R
                );

                if(eType == QEvent::MouseButtonRelease)
                    this->mediaDecoder->setPosition(
                        this->dur * (x - 10) / (this->sliderBack->width() - 10.0)
                    );
            }
            //evt->x();
        }
        else if(o == this->volumeBack || o == this->volumeFront)
        {
            QEvent::Type eType = e->type();
            if(
                eType == QEvent::MouseButtonRelease
                || eType == QEvent::MouseMove
                || eType == QEvent::MouseButtonPress
            ) {
                int x = (static_cast<QMouseEvent*>(e))->x();
                int maxX = this->volumeBack->width();
                x = x > 10 ? x > maxX ? maxX : x : 10;

                this->volumeFront->setGeometry(
                    this->volumeFront->x(),
                    this->volumeFront->y(),
                    x,
                    R
                );

                int volume = 100 * (x - 10) / (this->volumeBack  ->width() - 10.0);
                this->mediaDecoder->setVolume(volume);

                if(eType == QEvent::MouseButtonRelease && volume > 75)
                {
                    QMessageBox::warning(
                        nullptr,
                        "Warning!",
                        "Volume larger than 75% may damage your hearing",
                        QMessageBox::Ok
                    );
                }
            }
        }
        else if(o == this->brightBack || o == this->brightFront)
        {
            QEvent::Type eType = e->type();
            if(
                eType == QEvent::MouseButtonRelease
                || eType == QEvent::MouseMove
                || eType == QEvent::MouseButtonPress
            ) {
                int x = (static_cast<QMouseEvent*>(e))->x();
                int maxX = this->brightBack->width();
                x = x > 10 ? x > maxX ? maxX : x : 10;

                this->brightFront->setGeometry(
                    this->brightFront->x(),
                    this->brightFront->y(),
                    x,
                    R
                );
            }
        }

        return false;
    }

public slots:
    void SLT_pauseClicked(bool paused)
    {
        if(paused) this->mediaDecoder->play();
        else this->mediaDecoder->pause();
    }

    void SLT_showFullscreen(bool)
    {
        this->playerWin->setWindowFlags(Qt::Window);
        this->playerWin->showFullScreen();
    }

    void SLT_pausePlayer(QMediaPlayer::State newState)
    {
        if(
            newState == QMediaPlayer::State::StoppedState
            && this->But_pause->state
        ) this->But_pause->togglePause();
    }

    void SLT_updateMedia(const QMediaContent& media)
    {
        // Update title
        this->videoTitle->setText(media.canonicalUrl().fileName());

        // Reset progress slider
        this->dur = 1;
        this->sliderFront->setGeometry(
            this->sliderFront->x(),
            this->sliderFront->y(),
            10,
            R
        );
    }

    void SLT_updateDur(qint64 dur) {
        this->dur = dur;
    }

    void SLT_updateSlider(qint64 pos)
    {
        this->sliderFront->setGeometry(
            this->sliderFront->x(),
            this->sliderFront->y(),
            10 + (this->lay->sliderWidth - 10) * pos / this->dur,
            R
        );
    }

    void SLT_switchMedia(bool, const QString& name)
    {
        QString fName("/");
#ifdef _WIN32
        if(name == "P1") fName += "a.wmv";
        else if(name == "P2") fName += "b.wmv";
        else if(name == "P3") fName += "c.wmv";
        else if(name == "R1") fName += "d.wmv";
        else if(name == "R2") fName += "e.wmv";
        else if(name == "R3") fName += "f.wmv";
#else
        if(name == "P1") fName += "a.MOV";
        else if(name == "P2") fName += "b.MOV";
        else if(name == "P3") fName += "c.MOV";
        else if(name == "R1") fName += "d.mp4";
        else if(name == "R2") fName += "e.mp4";
        else if(name == "R3") fName += "f.mp4";
#endif
        if(fName.length() > 1)
            this->mediaDecoder->setMedia(QUrl::fromLocalFile(this->srcDir + fName));
    }

    void SLT_switchMode(bool state) {
        this->lay->mode = !state;
    }

    void SLT_toggleAcc(bool state) {
        this->mediaDecoder->setPlaybackRate(state ? 1.5 : 1.0);
    }
};

#endif // WINTOMEO_H
