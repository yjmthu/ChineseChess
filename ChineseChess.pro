QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

CONFIG += release
DEFINES += QT_NO_DEBUG_OUTPUT

SOURCES += \
    chessstate.cpp \
    main.cpp \
    mainwindow.cpp \
    widgetboard.cpp \
    widgetstone.cpp

HEADERS += \
    chessmove.h \
    chessplayer.h \
    chessstate.h \
    chessstone.h \
    mainwindow.h \
    widgetboard.h \
    widgetstone.h

FORMS +=

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
