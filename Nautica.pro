QT       += core gui sql printsupport charts network script serialport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    arduino.cpp \
    client.cpp \
    connection.cpp \
    email.cpp \
    employes.cpp \
    equipement.cpp \
    abonement.cpp \
    main.cpp \
    mainwindow.cpp \
    pdf.cpp \
    stat1.cpp \
    maintenance.cpp \
    smoke-detector.cpp\
    dialog.cpp

HEADERS += \
    arduino.h \
    client.h \
    connection.h \
    email.h \
    employes.h \
    equipement.h \
    abonement.h \
    mainwindow.h \
    pdf.h \
    stat1.h \
    maintenance.h \
    smoke-detector.h\
    dialog.h

FORMS += \
    accueil.ui \
    mainwindow.ui \
    pdf.ui \
    stat1.ui\
    dialog.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    ressources.qrc
