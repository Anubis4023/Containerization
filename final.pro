QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    balance.cpp \
    balance_upload.cpp \
    balancecalc.cpp \
    comment.cpp \
    dialog.cpp \
    loading.cpp \
    login.cpp \
    main.cpp \
    mainwindow.cpp \
    movements.cpp

HEADERS += \
    balance.h \
    balance_upload.h \
    balancecalc.h \
    comment.h \
    container.h \
    dialog.h \
    loading.h \
    loading_code.h \
    login.h \
    mainwindow.h \
    movements.h

FORMS += \
    balance_upload.ui \
    balancecalc.ui \
    comment.ui \
    dialog.ui \
    loading.ui \
    login.ui \
    mainwindow.ui \
    movements.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
