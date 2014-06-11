#include "okno1.h"
#include "ui_okno1.h"

okno1::okno1(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::okno1)
{

    ui->setupUi(this);


}

okno1::~okno1()
{
    delete ui;
}

void okno1::ustaw_fabryki(){
    emit(fabryki(lin1->text()));
}

void okno1::ustaw_centra(){
    emit(centra(lin2->text()));
}

void okno1::zakoncz(){
    emit koniec();
}

void okno1::conf(){
    setGeometry(100,100,300,200);
    setWindowTitle("Wprowadź ilość fabryk i centrów dystrybucji");
    lab1 = new QLabel("fabryki",this);
    lab2 = new QLabel("centra", this);
    button = new QPushButton("dalej", this);
    lin1 = new QLineEdit("", this);
    lin2 = new QLineEdit("", this);
    lab1->setGeometry(20,20,100,20);
    lab2->setGeometry(20,40,100,20);
    lin1->setGeometry(100,20,50,20);
    lin2->setGeometry(100,40,50,20);
    button->setGeometry(100,100, 50,30);
    QObject::connect(button, SIGNAL(clicked()),this, SLOT(ustaw_fabryki()));
    QObject::connect(button, SIGNAL(clicked()),this, SLOT(ustaw_centra()));
    QObject::connect(button, SIGNAL(clicked()),this, SLOT(zakoncz()));
}
