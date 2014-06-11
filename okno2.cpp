#include "okno2.h"
#include "ui_okno2.h"
#include "transport.h"
#include <QLabel>
okno2::okno2(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::okno2)
{
    ui->setupUi(this);
}

okno2::~okno2()
{
    delete ui;
}
void okno2::ustaw_f(QString wart){
    il_fabr = wart.toInt();
}

void okno2::ustaw_c(QString wart){
    il_centr = wart.toInt();
}

void okno2::zbierz_dane(){
    for(int i = 0; i<il_fabr; i++)
        for(int k = 0;k<il_centr;k++){
            dane.push_back(formularz.at(i).at(k)->text().toInt());
        }
    for(int i = 0; i<il_fabr;i++){
        dane.push_back(formularz.at(i).at(il_centr)->text().toInt());
    }
    for(int i = 0; i<il_centr;i++){
        dane.push_back(formularz.at(il_fabr).at(i)->text().toInt());
    }
    transport T(il_fabr,il_centr, dane);
    T.pierwsze_rozw_bazowe();

        T.wyznacz_mac_opt();
        T.uzupelnij_mac_opt();

        while(T.spr_mac_opt()<0){
            T.aktualizuj_przejazdy();

            T.wyzeruj_mac_opt();


            T.wyznacz_mac_opt();
            T.uzupelnij_mac_opt();


        }
    QString temp;
    for(int i = 0; i<il_fabr; i++)
        for(int k = 0; k<il_centr;k++){
            formularz.at(i).at(k)->setText(temp.setNum(T.macierz_sciezek.at(i).at(k)));
        }
    koszt_w->setText(temp.setNum(T.koszt()));

}


void okno2::conf(){
    std::vector<QLineEdit*> vec;
    for(int i = 0; i<=il_fabr; i++){
        formularz.push_back(vec);
        fabryki.push_back(new QLabel("", this));
    }
    for(int i = 0; i<=il_centr;i++){
        centra.push_back(new QLabel("",this));
    }
    for(int i = 0; i<= il_fabr; i++)
        for(int k = 0; k<=il_centr;k++)
            formularz.at(i).push_back(new QLineEdit("", this));
    /*Rozmieszczenie formularza, ustawienie rozmiarow, okna, pol i przycisku "dalej"*/
    setGeometry(100,100,il_centr*240,il_fabr*180);
    setWindowTitle("Wprowadź dane");
    /*ustawienia dla labelow*/
    QString temp;
    for(int i = 0; i<il_fabr; i++){
        fabryki.at(i)->setGeometry(20,50+20*i,100,20);
        fabryki.at(i)->setText("Fabryka nr "+ temp.setNum(i));
    }
    fabryki.at(il_fabr)->setGeometry(20,50+20*il_fabr,100,20);
    fabryki.at(il_fabr)->setText("Popyt");
    /*ustawienia dla labelow dla centrow*/
    for(int i = 0; i<il_centr;i++){
        centra.at(i)->setGeometry(120+100*i,20,100,20);
        centra.at(i)->setText("Centrum nr "+temp.setNum(i));
    }
    centra.at(il_centr)->setGeometry(120+100*il_centr,20,100,20);
    centra.at(il_centr)->setText("Podaż");


    /*Ustawienia dla pól lineedit*/

    for(int i = 0; i<=il_fabr; i++)
        for(int k = 0; k<=il_centr; k++){
            formularz.at(i).at(k)->setGeometry(120+100*k,50+20*i,100,20);
        }
    przycisk = new QPushButton("Oblicz", this);
    przycisk->setGeometry(120 + 100*il_centr,150 + 20*il_fabr, 60,30);
    przycisk_q = new QPushButton("Wyjdz", this);
    przycisk_q->setGeometry(120 + 100*il_centr,180 + 20*il_fabr, 60,30);
    koszt_l = new QLabel("Koszt", this);
    koszt_l->setGeometry(20,150+20*il_fabr,100,20);
    koszt_w = new QLineEdit("",this);
    koszt_w->setGeometry(100,150+20*il_fabr,60,20);
    /*Trzeba polaczyc przycisk z funkcja ktora zbierze dane, przesle je do metody
nastepnie wyswietli wynik takze na tablicy w podobny sposob jak wyzej*/

    QObject::connect(przycisk, SIGNAL(clicked()), this, SLOT(zbierz_dane()));
    QObject::connect(przycisk_q, SIGNAL(clicked()), this, SLOT(close()));

    show();
}

