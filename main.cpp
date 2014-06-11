#include "okno1.h"
#include "okno2.h"
#include <QApplication>
#include <QLineEdit>
#include <QPushButton>
#include <QLabel>
#include <cstdlib>
QString il_fabr;
int il_centr;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    okno1 o1;
    okno2 o2;

    o1.conf();
    o1.show();





    QObject::connect(&o1, SIGNAL(fabryki(QString)),&o2, SLOT(ustaw_f(QString)));
    QObject::connect(&o1, SIGNAL(centra(QString)),&o2, SLOT(ustaw_c(QString)));
    QObject::connect(&o1, SIGNAL(koniec()),&o2, SLOT(conf()));




    return a.exec();
}
