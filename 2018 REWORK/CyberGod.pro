#-------------------------------------------------
#
# Project created by QtCreator 2018-01-12T14:32:09
#
#-------------------------------------------------

QT       += core gui sql network concurrent

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = CyberGod
TEMPLATE = app


SOURCES += main.cpp\
        cybergod.cpp \
    drives.cpp \
    usbdrives.cpp \
    hash.cpp \
    url.cpp \
    file.cpp \
    usbscan.cpp \
    scanfile.cpp \
    threatinfo.cpp \
    scan.cpp \
    aboutus.cpp \
    cybergod_menu_definitions.cpp \
    shortcutvirusremover.cpp \
    executecommand.cpp \
    rubberduckydetector.cpp \
    hashdatabase.cpp \
    strings.cpp \
    customscan.cpp \
    customscanfile.cpp \
    thirdparty.cpp \
    customscanfolder.cpp \
    deletefile.cpp

HEADERS  += cybergod.hpp \
    drives.hpp \
    usbdrives.hpp \
    hash.hpp \
    url.hpp \
    file.hpp \
    usbscan.hpp \
    scanfile.hpp \
    threatinfo.hpp \
    scan.hpp \
    aboutus.hpp \
    shortcutvirusremover.hpp \
    executecommand.hpp \
    rubberduckydetector.hpp \
    hashdatabase.hpp \
    strings.hpp \
    customscan.hpp \
    customscanfile.hpp \
    thirdparty.hpp \
    customscanfolder.hpp \
    deletefile.hpp

FORMS    += cybergod.ui \
    aboutus.ui \
    shortcutvirusremover.ui \
    rubberduckydetector.ui \
    customscan.ui \
    thirdparty.ui

RESOURCES += \
    img.qrc

win32:LIBS += -luser32
