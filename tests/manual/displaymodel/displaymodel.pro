TEMPLATE = app
TARGET = tst_displaymodel
CONFIG += qt warn_on

QT += 3dquick

SOURCES += main.cpp

ICON_FILE = ../icon.png

QML_FILES = \
    qml/desktop.qml \
    qml/TestDisplayModel.qml

QML_INFRA_FILES = \
    $$QML_FILES

QML_MESHES_FILES = \
    qml/meshes/monkey.obj \
    qml/meshes/monkey.mtl \
    qml/meshes/lunar-lander.3ds \
    qml/meshes/teapot.bez

CATEGORY = manual
include(../../../pkg.pri)

OTHER_FILES += \
    $$QML_INFRA_FILES
