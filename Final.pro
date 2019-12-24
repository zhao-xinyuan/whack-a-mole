TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt
LIBS += -lglut -lGLU -lGL -lm
SOURCES += main.cpp \
    particalsystem.cpp \
    skybox.cpp \
    snowman.cpp \
    vector3d.cpp \
    errcheck.c \
    fatal.c \
    loadtexbmp.c \
    object.c \
    print.c \
    project.c

HEADERS += \
    CSCIx229.h \
    particalsystem.h \
    particle.h \
    skybox.h \
    snowman.h \
    vector3d.h \
    waterfall.h

