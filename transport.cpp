#include "transport.h"
#include<limits>
#include<cstdlib>






void transport::wyzeruj_mac_opt(){

    for(int i = 0; i<=il_fabr; i++)
            for(int k = 0; k<=il_centr; k++){
                macierz_optymalizacji.at(i).at(k) = 0;
        }


    for(int i = 0; i<il_fabr; i++)
            for(int k = 0; k<il_centr; k++){
                if(macierz_sciezek.at(i).at(k)!=0 || przejazdy_zdegenerowane.at(i).at(k)) {macierz_optymalizacji.at(i).at(k) = macierz_kosztow.at(i).at(k);}
        }
}

void transport::pierwsze_rozw_bazowe(){


    /*przpisz podaz kazdej fabryki*/
    for(int i = 0; i<il_fabr; i++){
        macierz_sciezek.at(i).at(il_centr) = macierz_kosztow.at(i).at(il_centr);
    }
    for(int i = 0; i<il_centr; i++)
        macierz_sciezek.at(il_fabr).at(i) = macierz_kosztow.at(il_fabr).at(i);

    /*ustalenie kosztow*/
    for(int k = 0; k<il_centr; k++)
        for(int i = 0; i<il_fabr; i++){
            macierz_sciezek.at(i).at(k) = (macierz_sciezek.at(il_fabr).at(k)<macierz_sciezek.at(i).at(il_centr))?macierz_sciezek.at(il_fabr).at(k):macierz_sciezek.at(i).at(il_centr);

            macierz_sciezek.at(il_fabr).at(k) -= macierz_sciezek.at(i).at(k);

            macierz_sciezek.at(i).at(il_centr) -= macierz_sciezek.at(i).at(k);
        }
        /*Trzeba teraz wprowadzic ewentualne przewozy zdegenerowane*/
    /*for(int k = 0; k<il_centr; k++){
        int licznik = 0;
        int index1 = 0; int index2 = 0;
        for(int i = 0; i<il_fabr; i++){
            if(macierz_sciezek.at(i).at(k)>0) {licznik++; index1 = i; index2 = k;}
            }
            if(licznik>1){
                if(index1 == il_fabr) przejazdy_zdegenerowane.at(index1-1).at(index2) = true;
                else przejazdy_zdegenerowane.at(index1+1).at(index2) = true;
            }

        }*/
        /*Przepisanie poszczegolnych elementow do macierzy optymalizacji*/

        for(int i = 0; i<il_fabr; i++)
            for(int k = 0; k<il_centr; k++){
                if(macierz_sciezek.at(i).at(k)!=0 || przejazdy_zdegenerowane.at(i).at(k)) {macierz_optymalizacji.at(i).at(k) = macierz_kosztow.at(i).at(k);}
            }


}

int transport::spr_mac_opt(){
    int wsk = 0;
    for(int i = 0; i<il_fabr; i++)
        for(int k = 0; k<il_centr; k++){
            if(macierz_optymalizacji.at(i).at(k)<wsk) {
                wsk = macierz_optymalizacji.at(i).at(k);
                ind1 = i; ind2 = k;
            }
        }
        cout<<"WSK"<<wsk<<endl;
    return wsk;
}

void transport::wypisz_mac_sc(){
    cout<<"wypisz macierz sciezek"<<endl;
    for(int i = 0; i<=il_fabr;i++){
        for(int k = 0; k<=il_centr; k++)
            cout<<macierz_sciezek.at(i).at(k)<<" , ";
        cout<<endl;
    }
}

void transport::wypisz_mac_koszt(){
    cout<<"wypisz macierz kosztow"<<endl;
    for(int i = 0; i<=il_fabr;i++){
        for(int k = 0; k<=il_centr; k++)
            cout<<macierz_kosztow.at(i).at(k)<<" , ";
        cout<<endl;
    }
}

void transport::wypisz_mac_zd(){
    cout<<"wypisz macierz przejazdow zdegenerowanych"<<endl;
    for(int i = 0; i<=il_fabr;i++){
        for(int k = 0; k<=il_centr; k++)
            cout<<przejazdy_zdegenerowane.at(i).at(k)<<" , ";
        cout<<endl;
    }
}

void transport::wypisz_mac_opt(){cout<<"MACIERZ OPTYMALIZACJI: "<<endl;
    for(int i = 0; i<=il_fabr;i++){
        for(int k = 0; k<=il_centr; k++)
            cout<<macierz_optymalizacji.at(i).at(k)<<" , ";
        cout<<endl;
    }
}

bool transport::wyznacz_mac_opt(){
    przeszukaj_wiersz(0);

    for(int i = 0; i<il_fabr; i++)
        przejrzane_u.at(i) = false;
    for(int i = 0; i<il_centr; i++)
        przejrzane_v.at(i) = false;


    wypisz_mac_opt();
}



void transport::uzupelnij_mac_opt(){
    for(int i = 0; i<il_fabr; i++){
        for(int k = 0;k<il_centr; k++){
            macierz_optymalizacji.at(i).at(k) = macierz_optymalizacji.at(i).at(il_centr) + macierz_optymalizacji.at(il_fabr).at(k);
        }
    }
    for(int i = 0;i<il_fabr;i++)
        for(int k = 0; k<il_centr; k++)
            macierz_optymalizacji.at(i).at(k) = macierz_kosztow.at(i).at(k) - macierz_optymalizacji.at(i).at(k);
}
/*! \brief tworzy cykl, ktory posluzy do poprawienia funkcji celu*/
void transport::aktualizuj_przejazdy(){
    /*sprawdzenia optymalnosci dokonamy osobno - mamy z gorty ind1 i ind2*/
    licznik = 0;
    vector<int> vec_pom;
    for(int i =0; i<2; i++)
        polcykl_dodatni.push_back(vec_pom);
    for(int i = 0; i<3; i++)
        polcykl_ujemny.push_back(vec_pom);
    polcykl_dodatni.at(0).push_back(ind1);
    polcykl_dodatni.at(1).push_back(ind2);
    tworz_cykl_ujemny(ind1,ind2, ind1, ind2);


    /*znalezienie elementu najmniejszego*/
    int index11, index22, min_przejazd, min_koszt;
    int powtorzenia;

    min_przejazd = polcykl_ujemny.at(0).at(0);

    index11 = polcykl_ujemny.at(1).at(0);

    index22 = polcykl_ujemny.at(2).at(0);

    for(int i = 0; i< polcykl_ujemny.at(1).size(); i++){
        if(polcykl_ujemny.at(0).at(i)<min_przejazd){
            powtorzenia = 1;
            min_przejazd = polcykl_ujemny.at(0).at(i);
            index11 = polcykl_ujemny.at(1).at(i);

            index22 = polcykl_ujemny.at(2).at(i);
            min_koszt = macierz_kosztow.at(polcykl_ujemny.at(1).at(i)).at(polcykl_ujemny.at(2).at(i));
        }
        else if(polcykl_ujemny.at(0).at(i) == min_przejazd) powtorzenia++;

    }


    if(powtorzenia != 1){

        for(int i = 0; i<polcykl_ujemny.at(0).size(); i++){
            if(polcykl_ujemny.at(0).at(i) == min_przejazd){
                if(macierz_kosztow.at(polcykl_ujemny.at(1).at(i)).at(polcykl_ujemny.at(2).at(i))>macierz_kosztow.at(index11).at(index22)){
                    index11 = polcykl_ujemny.at(1).at(i);
                    index22 = polcykl_ujemny.at(2).at(i);
                }
            }
        }
    }

    /*odejmowanie w polcyklu ujemnym*/
    for(int i = 0; i<polcykl_ujemny.at(0).size(); i++){

        macierz_sciezek.at(polcykl_ujemny.at(1).at(i)).at(polcykl_ujemny.at(2).at(i)) -= min_przejazd;


        if((macierz_sciezek.at(polcykl_ujemny.at(1).at(i)).at(polcykl_ujemny.at(2).at(i)) == 0) && (polcykl_ujemny.at(1).at(i) != index11 || polcykl_ujemny.at(2).at(i) != index22)){
            //wprowadzamy przejazd zdegenerowany

            przejazdy_zdegenerowane.at(polcykl_ujemny.at(1).at(i)).at(polcykl_ujemny.at(2).at(i)) = 1;
        }
        if((macierz_sciezek.at(polcykl_ujemny.at(1).at(i)).at(polcykl_ujemny.at(2).at(i)) != 0) || (polcykl_ujemny.at(1).at(i) == index11 && polcykl_ujemny.at(2).at(i) == index22)){ przejazdy_zdegenerowane.at(polcykl_ujemny.at(1).at(i)).at(polcykl_ujemny.at(2).at(i)) = 0; }
    }


    /*dodawanie do polcyklu dodatniego*/

    for(int i = 0; i<polcykl_dodatni.at(0).size(); i++){
        macierz_sciezek.at(polcykl_dodatni.at(0).at(i)).at(polcykl_dodatni.at(1).at(i)) += min_przejazd;
        if(min_przejazd == 0 && macierz_sciezek.at(polcykl_dodatni.at(0).at(i)).at(polcykl_dodatni.at(1).at(i)) == 0)przejazdy_zdegenerowane.at(polcykl_dodatni.at(0).at(i)).at(polcykl_dodatni.at(1).at(i)) = 1;
    }

    polcykl_ujemny.clear();
    polcykl_dodatni.clear();



}

bool transport::tworz_cykl_ujemny(int wiersz_start, int kolumna_start, int index1, int index2){

    if(licznik > 12) return true;
    if(index1 != wiersz_start) {flaga_przejscia = true; }
    //if(index1 = wiersz_start || index2 == kolumna_start) return true;
    //sprawdzenie czy el. jest samotny w wierszu!
    if(czy_element_samotny(true, index1,index2)){  return false;}
    //przeszukujemy wiersz
    int l = 0;
    for(int i = 0; i<il_centr; i++){

        if(i == index2 || ((macierz_sciezek.at(index1).at(i) == 0) && (przejazdy_zdegenerowane.at(index1).at(i) == 0))) {continue;}
        if(tworz_cykl_dodatni(wiersz_start, kolumna_start, index1,i)){

            l++;
            polcykl_ujemny.at(0).push_back(macierz_sciezek.at(index1).at(i));
            polcykl_ujemny.at(1).push_back(index1);
            polcykl_ujemny.at(2).push_back(i);
            return true;
        }
    }
    return l;
}

bool transport::tworz_cykl_dodatni(int wiersz_start, int kolumna_start, int index1, int index2){


    if((index2 == kolumna_start)  && flaga_przejscia ) {return true;}
    //Sprawdzenie czy element jest samotny w kolumnie!
    if(czy_element_samotny(false, index1, index2)) {return false;}
    //przeszukujemy kolumne
    int l = 0;
    for(int i = 0; i<il_fabr; i++){

        if(i == index1 || ((macierz_sciezek.at(i).at(index2) == 0) && (przejazdy_zdegenerowane.at(i).at(index2) == 0))) continue;
        if(tworz_cykl_ujemny(wiersz_start, kolumna_start, i, index2)){
            l++;
            polcykl_dodatni.at(0).push_back(i);
            polcykl_dodatni.at(1).push_back(index2);
            return true;
        }
    }
    return l;
}



/*STARSZA WERSJA TWORZENIA MACIERZY OPTYMALIZACJI---------------------------

/*warunek stopu
    if((fabryka == il_fabr - 1) && (centrum == il_centr - 1) ) return true;

    if((fabryka == 0) && (centrum == 0)) { //tylko na poczatku taka sytuacja moze miec miejsce
        macierz_optymalizacji.at(fabryka).at(il_centr) = 0;
        macierz_optymalizacji.at(il_fabr).at(centrum) = macierz_optymalizacji.at(fabryka).at(centrum) - macierz_optymalizacji.at(fabryka).at(il_centr);
        cout<<"ustawiam pierwszy element na 0"<<endl;
    }

    if(fabryka == il_fabr - 1) {
        macierz_optymalizacji.at(il_fabr).at(centrum+1) = macierz_optymalizacji.at(fabryka).at(centrum+1) - macierz_optymalizacji.at(fabryka).at(il_centr);
        return wyznacz_mac_opt(fabryka, centrum + 1 );}
    else if(centrum == il_centr -1) {
        macierz_optymalizacji.at(fabryka+1).at(il_centr) = macierz_optymalizacji.at(fabryka+1).at(centrum) - macierz_optymalizacji.at(il_fabr).at(centrum);

        return wyznacz_mac_opt(fabryka + 1, centrum);}
    /*sprawdzic, w ktorym miejscu jest kolejny
    else if (macierz_optymalizacji.at(fabryka + 1).at(centrum)) {
        macierz_optymalizacji.at(fabryka+1).at(il_centr) = macierz_optymalizacji.at(fabryka+1).at(centrum) - macierz_optymalizacji.at(il_fabr).at(centrum);

        return wyznacz_mac_opt(fabryka + 1, centrum);}
    else {
        macierz_optymalizacji.at(il_fabr).at(centrum+1) = macierz_optymalizacji.at(fabryka).at(centrum+1) - macierz_optymalizacji.at(fabryka).at(il_centr);
        return wyznacz_mac_opt(fabryka, centrum + 1);}

    */


bool transport::czy_przejrzane(vector<bool>* v){
    for(vector<bool>::iterator it = v->begin(); it != v->end(); it++)
        if(!(*it)) return false;
    return true;
}

bool transport::przeszukaj_wiersz(int ind_wiersza){
    if(czy_przejrzane(&przejrzane_u)) {return true;}
    if(przejrzane_u.at(ind_wiersza)) {return true;}
    przejrzane_u.at(ind_wiersza) = true;
    for(int i = 0; i<il_centr; i++){
        if(macierz_optymalizacji.at(ind_wiersza).at(i) || przejazdy_zdegenerowane.at(ind_wiersza).at(i)){
            //znalezlismy niezerowy element, lub zdegenerowany
            macierz_optymalizacji.at(il_fabr).at(i) = macierz_optymalizacji.at(ind_wiersza).at(i) - macierz_optymalizacji.at(ind_wiersza).at(il_centr);
            przeszukaj_kolumne(i);
        }

    }
}

bool transport::przeszukaj_kolumne(int ind_kolumny){
    if(czy_przejrzane(&przejrzane_v)) return true;
    if(przejrzane_v.at(ind_kolumny)) return true;
    przejrzane_v.at(ind_kolumny) = true;
    for(int i = 0; i<il_fabr; i++){
        if(macierz_optymalizacji.at(i).at(ind_kolumny) || przejazdy_zdegenerowane.at(i).at(ind_kolumny)){
            //znalezlismy niezerowy element, lub zdegenerowany
            macierz_optymalizacji.at(i).at(il_centr) = macierz_optymalizacji.at(i).at(ind_kolumny) - macierz_optymalizacji.at(il_fabr).at(ind_kolumny);
            przeszukaj_wiersz(i);
        }

    }
}

bool transport::czy_element_samotny(bool typ, int w, int k){
    if(typ){//SPRAWDZAMY CZY ELEMENT JEST SAMOTNY W WIERSZU
        for(int i = 0; i< il_centr; i++){
            if(i ==k) continue;
            if(macierz_sciezek.at(w).at(i) || przejazdy_zdegenerowane.at(w).at(i)) return false;

        }
        return true;
    }
    else{//czy element samotny w kolumnie
        for(int i = 0; i<il_fabr; i++){
            if(i == w) continue;
            if(macierz_sciezek.at(i).at(k) || przejazdy_zdegenerowane.at(i).at(k)) return false;
        }
        return true;
    }

}

int transport::koszt(){
    int koszt = 0;
    for(int i = 0; i<il_fabr; i++)
        for(int k = 0; k<il_centr; k++)
            koszt += (macierz_sciezek.at(i).at(k)*macierz_kosztow.at(i).at(k));
    //cout<<"KOSZT: "<<koszt<<endl;
    return koszt;
}
