TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt
LIBS += -lSDL -lglut -lGLU -lGL -lm
SOURCES += \
    vector3d.cpp \
    particalsystem.cpp \
    errcheck.c \
    fatal.c \
    loadtexbmp.c \
    object.c \
    print.c \
    project.c \
    skybox.cpp \
    main.cpp \
    snowman.cpp

DISTFILES += \
    FinalProject.pro.user

HEADERS += \
    vector3d.h \
    particle.h \
    particalsystem.h \
    CSCIx229.h \
    skybox.h \
    snowman.h

