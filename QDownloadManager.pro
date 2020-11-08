QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    basedownload.cpp \
    downloadfileinfodialog.cpp \
    downloadmanager.cpp \
    downloadmodel.cpp \
    main.cpp \
    mainwindow.cpp \
    newdldialog.cpp \
    optionsdialog.cpp \
    paralleldownload.cpp \
    remotefileinfo.cpp \
    segment.cpp \
    segmentmodel.cpp

HEADERS += \
    basedownload.h \
    downloadfileinfodialog.h \
    downloadmanager.h \
    downloadmodel.h \
    downloadstate.h \
    downloadtype.h \
    mainwindow.h \
    newdldialog.h \
    optionsdialog.h \
    paralleldownload.h \
    remotefileinfo.h \
    segment.h \
    segmentmodel.h \
    segmentstate.h

FORMS += \
    downloadfileinfodialog.ui \
    mainwindow.ui \
    newdldialog.ui \
    optionsdialog.ui

TRANSLATIONS += \
    QDownloadManager_en_US.ts

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    icons.qrc
