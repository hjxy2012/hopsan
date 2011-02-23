# -------------------------------------------------
# Project created by QtCreator 2009-12-28T14:27:59
# -------------------------------------------------
# -------------------------------------------------
# Global project options
# -------------------------------------------------
include( ../Common.prf )

TARGET = HopsanGUI
TEMPLATE = app
DESTDIR = $${PWD}/../bin

QT += svg xml
QT += core gui webkit

TARGET = $${TARGET}$${DEBUG_EXT}

#Set default pythonqt path if it can be found, or use custom value supplied through env variable
PYTHONQT_DEFAULT_PATHS = $${PWD}/../ExternalDependencies/PythonQt2.0.1
PYTHONQT_PATH = $$selectPath($$(PYTHONQT_PATH), $$PYTHONQT_DEFAULT_PATHS, "pythonqt")

INCLUDEPATH += $${PWD}/../HopsanCore
INCLUDEPATH += $${PYTHONQT_PATH}/src \
               $${PYTHONQT_PATH}/extensions/PythonQt_QtAll

LIBS += -L$${PWD}/../lib -lHopsanCore$${DEBUG_EXT}
#PythonQt has same debug extension as Hopsan
LIBS += -L$${PYTHONQT_PATH}/lib -lPythonQt$${DEBUG_EXT} \
                                -lPythonQt_QtAll$${DEBUG_EXT}

# -------------------------------------------------
# Platform specific additional project options
# -------------------------------------------------
unix {
    LIBS += -Wl,-rpath,./,../lib
    LIBS += -lqwt-qt4
    INCLUDEPATH += /usr/include/qwt-qt4/
    INCLUDEPATH += /usr/include/python2.6

    LIBS += $$system(python$${PYTHON_VERSION}-config --libs)

    QMAKE_CXXFLAGS += $$system(python$${PYTHON_VERSION}-config --includes)
}
win32 {
    #DEFINES += STATICCORE

    #Set QWT paths, Paths that are earlier in the list will be used if found
    QWT_PATHS *= $${PWD}/../ExternalDependencies/qwt-5.2-svn
    QWT_PATH = $$selectPath($$(QWT_PATH), $$QWT_PATHS, "qwt")

    INCLUDEPATH += $${QWT_PATH}/include
    INCLUDEPATH += $${QWT_PATH}/src #Need to include this one also couse qwt is strange
    LIBS += -L$${QWT_PATH}/lib

    CONFIG(debug, debug|release) {
        LIBS += -lqwtd5
    }
    CONFIG(release, debug|release) {
        LIBS += -lqwt5
    }

    #Set Python paths
    PYTHON_DEFAULT_PATHS *= c:/Python26
    PYTHON_PATH = $$selectPath($$(PYTHON_PATH), $$PYTHON_DEFAULT_PATHS, "python")
    INCLUDEPATH += $${PYTHON_PATH}/include
    LIBS += -L$${PYTHON_PATH}/libs

    #Temporary hack
    CONFIG(debug, debug|release) {
        LIBS += -L$${PWD}/../ExternalDependencies/tbb30_20101215oss/build/windows_ia32_gcc_mingw_debug
        LIBS += -L$${PWD}/../ExternalDependencies/tbb30_20100406oss/build/windows_ia32_gcc_mingw_debug
        LIBS += -ltbb_debug
    }
    CONFIG(release, debug|release) {
        LIBS += -L$${PWD}/../ExternalDependencies/tbb30_20101215oss/build/windows_ia32_gcc_mingw_release
        LIBS += -L$${PWD}/../ExternalDependencies/tbb30_20100406oss/build/windows_ia32_gcc_mingw_release
        LIBS += -ltbb
    }

    #Debug output
    #message(Includepath is $$INCLUDEPATH)
    #message(Libs is $${LIBS})
}
RESOURCES += \  
    Resources.qrc

# Release compile only, will add the application icon
RC_FILE = HOPSANGUI.rc

# -------------------------------------------------
# Project files
# -------------------------------------------------
SOURCES += main.cpp \
    MainWindow.cpp \
    Widgets/ProjectTabWidget.cpp \
    Widgets/LibraryWidget.cpp \
    GUIConnector.cpp \
    GUIPort.cpp \
    Widgets/PlotWidget.cpp \
    Widgets/MessageWidget.cpp \
    SimulationThread.cpp \
    InitializationThread.cpp \
    Dialogs/OptionsDialog.cpp \
    UndoStack.cpp \
    GraphicsView.cpp \
    loadObjects.cpp \
    ProgressBarThread.cpp \
    GUIPortAppearance.cpp \
    GUIConnectorAppearance.cpp \
    Widgets/SystemParametersWidget.cpp \
    PlotWindow.cpp \
    PyWrapperClasses.cpp \
    Widgets/PyDockWidget.cpp \
    GUIObjects/GUIWidgets.cpp \
    GUIObjects/GUISystem.cpp \
    GUIObjects/GUIObject.cpp \
    GUIObjects/GUIModelObjectAppearance.cpp \
    GUIObjects/GUIModelObject.cpp \
    GUIObjects/GUIGroup.cpp \
    GUIObjects/GUIContainerObject.cpp \
    GUIObjects/GUIComponent.cpp \
    Utilities/XMLUtilities.cpp \
    Utilities/GUIUtilities.cpp \
    Configuration.cpp \
    CopyStack.cpp \
    Dialogs/ComponentPropertiesDialog.cpp \
    Dialogs/ContainerPropertiesDialog.cpp \
    Dialogs/AboutDialog.cpp \
    CoreAccess.cpp \
    Widgets/UndoWidget.cpp \
    Widgets/QuickNavigationWidget.cpp \
    GUIObjects/GUIContainerPort.cpp \
    Dialogs/ContainerPortPropertiesDialog.cpp \
    Dialogs/WelcomeDialog.cpp \
    Dialogs/HelpDialog.cpp

HEADERS += MainWindow.h \
    Widgets/ProjectTabWidget.h \
    Widgets/LibraryWidget.h \
    ../HopsanCore/HopsanCore.h \
    GUIConnector.h \
    GUIPort.h \
    Widgets/PlotWidget.h \
    Widgets/MessageWidget.h \
    SimulationThread.h \
    InitializationThread.h \
    version.h \
    Dialogs/OptionsDialog.h \
    UndoStack.h \
    CoreAccess.h \
    GraphicsView.h \
    loadObjects.h \
    ProgressBarThread.h \
    common.h \
    CoreAccess.h \
    GUIPortAppearance.h \
    GUIConnectorAppearance.h \
    Widgets/SystemParametersWidget.h \
    PlotWindow.h \
    PyWrapperClasses.h \
    Widgets/PyDockWidget.h \
    GUIObjects/GUIWidgets.h \
    GUIObjects/GUISystem.h \
    GUIObjects/GUIObject.h \
    GUIObjects/GUIModelObjectAppearance.h \
    GUIObjects/GUIModelObject.h \
    GUIObjects/GUIGroup.h \
    GUIObjects/GUIContainerObject.h \
    GUIObjects/GUIComponent.h \
    Utilities/XMLUtilities.h \
    Utilities/GUIUtilities.h \
    Configuration.h \
    CopyStack.h \
    Dialogs/ComponentPropertiesDialog.h \
    Dialogs/ContainerPropertiesDialog.h \
    Dialogs/AboutDialog.h \
    Widgets/UndoWidget.h \
    Widgets/QuickNavigationWidget.h \
    GUIObjects/GUIContainerPort.h \
    Dialogs/ContainerPortPropertiesDialog.h \
    Dialogs/WelcomeDialog.h \
    Dialogs/HelpDialog.h
