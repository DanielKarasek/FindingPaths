QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++2a
# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    alphastar.cpp \
    bfs.cpp \
    dfs.cpp \
    main.cpp \
    mainwindow.cpp \
    map.cpp \
    mapeditbar.cpp \
    mediator.cpp \
    solutionpaintdevice.cpp \
    solutionsettingbar.cpp \
    solvingmethod.cpp \
    valuelabeledslider.cpp

HEADERS += \
    alphastar.h \
    bfs.h \
    dfs.h \
    mainwindow.h \
    map.h \
    mapeditbar.h \
    mediator.h \
    solutionpaintdevice.h \
    solutionsettingbar.h \
    solvingmethod.h \
    valuelabeledslider.h

FORMS += \
    mainwindow.ui

CONFIG += lrelease

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
