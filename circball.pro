QT += 3dcore 3drender 3dinput 3dquick qml quick 3dquickextras

CONFIG += c++11

SOURCES += main.cpp \
    circballmesh/circballmesh.cpp

RESOURCES += qml.qrc \
    shaders.qrc

HEADERS += \
    circballmesh/circballmesh.h
