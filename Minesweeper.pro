TEMPLATE = app

QT += qml quick widgets
CONFIG += c++11

SOURCES += main.cpp \
    gamemanager.cpp \
    game_playing_algo.cpp \
    gamemodel.cpp \
    message_bar.cpp

RESOURCES += qml.qrc

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Default rules for deployment.
include(deployment.pri)

HEADERS += \
    gamemanager.h \
    igameplayingalgo.h \
    game_playing_algo.h \
    gamemodel.h \
    message_bar.h

