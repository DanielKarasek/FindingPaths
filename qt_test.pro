QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++2a
# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    src/alphastar.cpp \
    src/bfs.cpp \
    src/dfs.cpp \
    src/main.cpp \
    src/mainwindow.cpp \
    src/map.cpp \
    src/mapeditbar.cpp \
    src/mediator.cpp \
    src/solutionpaintdevice.cpp \
    src/solutionsettingbar.cpp \
    src/solvingmethod.cpp \
    src/valuelabeledslider.cpp

HEADERS += \
    include/alphastar.h \
    include/bfs.h \
    include/dfs.h \
    include/mainwindow.h \
    include/map.h \
    include/mapeditbar.h \
    include/mediator.h \
    include/solutionpaintdevice.h \
    include/solutionsettingbar.h \
    include/solvingmethod.h \
    include/valuelabeledslider.h

FORMS += \
    mainwindow.ui

CONFIG += lrelease

INCLUDEPATH += include\

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
