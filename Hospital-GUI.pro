QT += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17 no_keywords

TARGET = HospitalManagementGUI
TEMPLATE = app

SOURCES += \
    main_gui.cpp \
    mainwindow.cpp \
    dialogs.cpp \
    database.cpp

HEADERS += \
    mainwindow.h \
    dialogs.h \
    database.h

# Disable MOC processing
MOC_DIR = moc

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
