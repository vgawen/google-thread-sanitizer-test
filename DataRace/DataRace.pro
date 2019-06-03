TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.c

QMAKE_CXXFLAGS+="-fsanitize=thread -fPIE -pie -fno-omit-frame-pointer"
QMAKE_CFLAGS+="-fsanitize=thread -fPIE -pie -fno-omit-frame-pointer"
QMAKE_LFLAGS+="-fsanitize=thread -fPIE -pie -fno-omit-frame-pointer"
