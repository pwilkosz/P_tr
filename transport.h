#ifndef TRANSPORT_H
#define TRANSPORT_H

#include<vector>
#include<iostream>

using namespace std;


class transport{
/*Pola prywatne*/
int licznik;
bool flaga_przejscia;
int il_fabr;
int il_centr;
/*! \brief indeks najmniejszego elementu w tablicy optymalizacji*/
int ind1;
/*! \brief indeks najmniejszego elementu w tablicy optymalizacji*/
int ind2;
/*! \brief przejazdy zdegenerowane*/
vector <vector<int> > przejazdy_zdegenerowane;
/*! \brief przechowuje elementy polcyklu dodatniego*/
vector<vector<int> > polcykl_dodatni;
/*! \brief przechowuje elementy polcyklu ujemnego*/
vector<vector<int> > polcykl_ujemny;
vector <vector<int> > macierz_kosztow;

vector <vector<int> > macierz_optymalizacji;
vector<bool> przejrzane_u;
vector<bool> przejrzane_v;
/*Pola publiczne*/
public:
vector <vector<int> > macierz_sciezek;
transport(int il_fabryk, int il_centrow, vector<int> &dane){
    flaga_przejscia = false;
    il_fabr = il_fabryk;
    il_centr = il_centrow;
    vector<int> vec;
    for(int i = 0; i<=il_fabryk; i++){
        przejazdy_zdegenerowane.push_back(vec);
        macierz_kosztow.push_back(vec);
        macierz_sciezek.push_back(vec);
        macierz_optymalizacji.push_back(vec);
    }

    for(int i = 0; i<il_fabryk; i++){
        for(int k = 0; k<il_centrow; k++)
        macierz_kosztow.at(i).push_back(dane.at(i*il_fabryk + k));
    }
    for(int i = 0; i<il_fabryk; i++){
        macierz_kosztow.at(i).push_back(dane.at(il_fabryk*il_centrow + i));
    }

    for(int i = 0; i<il_centrow; i++){
        macierz_kosztow.at(il_fabryk).push_back(dane.at(il_fabryk*il_centrow + il_fabryk + i));
    }
    macierz_kosztow.at(il_fabryk).push_back(0);

    for(int i = 0; i<=il_fabryk; i++)
        for(int k = 0; k<=il_centrow; k++){
            macierz_sciezek.at(i).push_back(0);
        }
    for(int i = 0; i<=il_fabryk; i++)
        for(int k = 0; k<=il_centrow; k++){
            macierz_optymalizacji.at(i).push_back(0);
        }
    for(int i = 0; i<=il_fabryk; i++)
        for(int k = 0; k<=il_centrow; k++){
            przejazdy_zdegenerowane.at(i).push_back(0);
        }
    /*ustawienie przejrzane_u i przejrzane_v na false*/
    for(int i = 0; i<il_fabr; i++)
        przejrzane_u.push_back(false);
    for(int i = 0; i<il_centr; i++)
        przejrzane_v.push_back(false);

}

void pierwsze_rozw_bazowe();

/*! \brief szuka najmnijeszego elementu w macierzy, zwraca jego pozycje.*/
int spr_mac_opt();

void wypisz_mac_koszt();

void wypisz_mac_sc();

void wypisz_mac_opt();

bool wyznacz_mac_opt();

void uzupelnij_mac_opt();
/*! \brief aktualizuje trasy celem zmniejszenia kosztu*/
void aktualizuj_przejazdy();
/*! \brief dodaje elementy do cyklu dodatniego - tutaj bedziemiy mieli warunek stopu rekurencji*/
bool tworz_cykl_dodatni(int wiersz_start, int kolumna_start, int index1, int index2);
/*! \brief dodaje elementy do cyklu ujemnego*/
bool tworz_cykl_ujemny(int wiersz_start, int kolumna_start, int index1, int index2);

bool czy_przejrzane(vector<bool>* v);

bool przeszukaj_wiersz(int ind_wiersza);

bool przeszukaj_kolumne(int ind_kolumny);

bool czy_element_samotny(bool typ, int w, int k);
/*! \brief Metoda poprawia */
void popraw_rozwiazanie();

void wyzeruj_mac_opt();

void wypisz_mac_zd();

int koszt();
};


/*! \brief metoda zbiera dane, aby uruchomic algorytm optymalizacyjny.
    Jest to zrobione inaczej, niż w przypadku algorytmu simplex celem ewentualnego stworzenia GUI
*/
void zbierz_dane();


#endif // TRANSPORT_H
