TEMPLATE = app
TARGET = shadertut
CONFIG += qt warn_on
QT += qml quick 3dquick

SOURCES += main.cpp

ICON_FILE = ../icon.png

QML_FILES = \
    qml/ShaderTutorial.qml \
    qml/desktop.qml \
    qml/TutorialTeapot.qml \
    qml/shader-tutorial-1-textures.qml \
    qml/shader-tutorial-3-transformed-coordinates.qml \
    qml/shader-tutorial-varying.qml \
    qml/shader-tutorial-2-vertex-shader.qml \
    qml/shader-tutorial-lighting.qml

QML_INFRA_FILES = \
    $$QML_FILES

QML_MESHES_FILES = \
    qml/meshes/teapot.bez

CATEGORY = tutorials
include(../../../pkg.pri)

OTHER_FILES += \
    shadertut.rc \
    $$QML_INFRA_FILES

RC_FILE = shadertut.rc
