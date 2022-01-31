#include "mainwindow.h"

#include <QApplication>
#include <QObject>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QSizePolicy>
#include "map.h"
#include "mediator.h"
#include "solutionpaintdevice.h"
#include "alphastar.h"
#include "solvingmethod.h"
#include "solutionsettingbar.h"
#include "mapeditbar.h"
#include <iostream>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    Map m{50,50};
    std::shared_ptr<Map> m2 =std::make_shared<Map>(m);
    Mediator mediator(m2);

    MainWindow w(mediator);

//    Map m{{{0,0,3,0,0,0,0,0,0,0,3},
//           {0,0,3,0,3,0,0,0,0,0,3},
//           {3,0,3,0,3,0,0,0,0,0,1},
//           {3,0,3,0,3,3,3,3,3,3,3},
//           {3,3,0,3,3,0,0,0,0,0,2},
//           {0,0,0,0,0,0,0,0,0,0,3}}};


    w.show();
    return a.exec();
}
