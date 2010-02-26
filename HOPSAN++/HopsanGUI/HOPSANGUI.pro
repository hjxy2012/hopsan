# -------------------------------------------------
# Project created by QtCreator 2009-12-28T14:27:59
# -------------------------------------------------
QT += svg
TARGET = HOPSANGUI
TEMPLATE = app
SOURCES += main.cpp \
    mainwindow.cpp \
    listwidgetitem.cpp \
    ProjectTabWidget.cpp \
    LibraryWidget.cpp \
    GUIConnector.cpp \
    GUIPort.cpp \
    GUIComponent.cpp \
    GUIConnectorLine.cpp \
    plotwidget.cpp \
    GUIComponentSelectionBox.cpp
HEADERS += mainwindow.h \
    listwidgetitem.h \
    ProjectTabWidget.h \
    LibraryWidget.h \
    ../HopsanCore/HopsanCore.h \
    GUIConnector.h \
    GUIPort.h \
    GUIComponent.h \
    GUIConnectorLine.h \
    plotwidget.h \
    GUIComponentSelectionBox.h
OTHER_FILES += 

# win32:DEFINES += STATICCORE
DESTDIR = ../bin/debug
LIBS += -L../bin/debug \
    -lHopsanCore
INCLUDEPATH += ../HopsanCore
unix { 
    LIBS += -Wl,-rpath,./
    LIBS += -lqwt-qt4
    INCLUDEPATH += /usr/include/qwt-qt4/
}

# Ingopath:
win32 { 
    INCLUDEPATH += c:/temp_qwt/src
    LIBS += c:/temp_qwt/lib/qwtd5.dll
}
