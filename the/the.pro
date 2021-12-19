QT += core gui widgets multimedia multimediawidgets

CONFIG += c++11

SOURCES += \
        main.cpp

HEADERS += \
    BaseLayout.h \
    SpButton.h \
    StyleHelper.h \
    WinTomeo.h

qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

