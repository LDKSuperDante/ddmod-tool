QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = DDMod
TEMPLATE = app

CONFIG += c++11
CONFIG+= static

win32 {
LIBS += -lopengl32
}

#windows icon
RC_FILE = icon.rc
#mac icon
#ICON = icon.icns


SOURCES += main.cpp\
    renderer/geometryengine.cpp \
    renderer/mainwidget.cpp \
    renderer/trackball.cpp \
    modeleditor.cpp

HEADERS += \
    renderer/geometryengine.h \
    renderer/glextensions.h \
    renderer/mainwidget.h \
    renderer/Mat.h \
    renderer/MathUtil.h \
    renderer/trackball.h \
    renderer/Vec.h \
    modeleditor.h

qtHaveModule(opengl): QT += opengl

RESOURCES += ddons.qrc

FORMS +=
