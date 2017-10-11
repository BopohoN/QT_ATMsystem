#-------------------------------------------------
#
# Project created by QtCreator 2016-06-04T08:44:23
#
#-------------------------------------------------

QT       += core gui \
            sql \
            widgets

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = MyChat
TEMPLATE = app


SOURCES += main.cpp\
    login.cpp \
    register.cpp \
    chatwindow.cpp \
    forgetpwd.cpp \
    savemoney.cpp \
    takemoney.cpp \
    transcash.cpp

HEADERS  += \
    login.h \
    register.h \
    chatwindow.h \
    forgetpwd.h \
    savemoney.h \
    takemoney.h \
    transcash.h

FORMS    += \
    login.ui \
    register.ui \
    chatwindow.ui \
    forgetpwd.ui \
    savemoney.ui \
    takemoney.ui \
    transcash.ui

RESOURCES += \
    chat.qrc
