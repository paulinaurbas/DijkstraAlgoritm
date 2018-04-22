#pragma once
#include <iostream>
#include <string>
#include <iomanip>
#ifndef TRASY_H
#define TRASY_H
using namespace std;
typedef double DlugoscTrasy;
typedef int NumerPunktu;
struct Krawedz;
/** Deklaracja Punktu Grafu.
@author Paulina Urbas
@date   2017-12-25
*/
struct Wezel
{
    /** etykieta wezla */
	NumerPunktu Wierzcholek;
    /** wskaznik na nastepny wezel w liscie wezlow */
	Wezel * Nastepny;
    /** wskaznik na liste krawedzi wezla */
    Krawedz * pKrawedzie; 
    /** odleglosc od wierzcholka startowego **/
    DlugoscTrasy odleglosc;
	/** Czy wierzcholek zostal odwiedzony */
	bool Odwiedzony;
	/** etykieta na poprzednik wezla */
	NumerPunktu Poprzednik;
};
/** Deklaracja Krawedzi Grafu
@author Paulina Urbas
@date   2017-12-25
*/
struct Krawedz
{
	/** etykieta odleglosci */
	DlugoscTrasy Odleglosc; 
	/** wskaznik na wezel poczatkowy */
	Wezel * Start;
	/** wskaznik na wezel koncowy */
	Wezel * Koniec;
	/** wskaznik na nastepna krawedz */
	Krawedz * kNastepny; 
};
/** Deklaracja Krawedzi Grafu
@author Paulina Urbas
@date   2017-12-25
*/
struct ListaPunktowPolaczen
{
	/** etykieta wezla */
	NumerPunktu A;
	/** wskaznik na nastepny numerpunktu w liscie */
	ListaPunktowPolaczen * pNext;
};
/** Funkcja odczytujaca parametry programu".
@author Paulina Urbas
@date   2017-12-25
@params argc 
@params argv
@params nazwaplikuwejsciowego
@params WyjsciowyWierzcholki
@params WyjsciowyOdleglosci
@return zwraca int
*/
int SprawdzWywolanie(int argc, char *argv[], string & nazwaplikuwejsciowego, string & WejsciowyWierzcholki, string & WyjsciowyOdleglosci);
/** Funkcja wyswietlajaca pomoc".
@author Paulina Urbas
@date   2017-12-25
@params brak
@return niczego nie zwraca
*/
void Pomoc();
/** Funkcja dodajaca wezel do listy z punktami".
@author Paulina Urbas
@date   2017-12-25
@params pHead
@params A
@return zwraca wezel
*/
Wezel * StworzWezel(Wezel * & pHead, NumerPunktu A);
/** Funkcja dodajaca krawedz do wezla".
@author Paulina Urbas
@date   2017-12-25
@params pHead
@params A
@params B
@params Odleglosc
@return nic nie zwraca
*/
void DodajKrawedz(Wezel * A, Wezel * B, DlugoscTrasy Odleglosc);
/** Funkcja sprawdzajaca czy trasa grafu jest skierowana".
@author Paulina Urbas
@date   2018-01-10
@params znak
@return nic nie zwraca
*/
bool CzySkierowany(string znak);
/** Funkcja odczytujaca z pliku graf".
@author Paulina Urbas
@date   2018-01-10
@params nazwapliku
@params pHead
@return nic nie zwraca
*/
void OdczytzPlikuGrafu(const string & nazwapliku, Wezel *& pHead);
/** Funkcja odczytujaca z pliku liste punktow".
@author Paulina Urbas
@date   2018-01-08
@params nazwapliku
@params pHead
@return nic nie zwraca
*/
void OdczytzPlikuPunktow(const string & nazwapliku, ListaPunktowPolaczen *&  pHead);
/** Funkcja usuwajaca jeden wezel z struktury".
@author Paulina Urbas
@date   2018-01-08
@params pHead
@params element
@return nic nie zwraca
*/
void UsunWezel(Wezel * & pHead, Wezel * element); 
/** Funkcja usuwajaca liste wezlow".
@author Paulina Urbas
@date   2018-01-08
@params pHead
@params element
@return nic nie zwraca
*/
void UsunListeWezlow(Wezel * & pHead);
/** Funkcja usuwajaca liste punktow".
@author Paulina Urbas
@date   2018-01-08
@params pHead
@return nic nie zwraca
*/
void UsunListePolaczen(ListaPunktowPolaczen * & pHead); 
/** Funkcja drukujaca liste wezlow grafu".
@author Paulina Urbas
@date   2018-01-08
@params pHead
@return nic nie zwraca
*/
void DrukujListeWezlow(Wezel * & pHead);
/** Funkcja drukujaca liste punktow do znalezienia odleglosci miedzy nimi".
@author Paulina Urbas
@date   2018-01-08
@params pHead
@return nic nie zwraca
*/
void DrukujListePunktow(ListaPunktowPolaczen * & pHead);
/** Funkcja dodajaca trase skierowana".
@author Paulina Urbas
@date   2018-01-08
@params pHead
@params A
@params B
@params Odleglosc
@return nic nie zwraca
*/
void DodajTraseSkierowana(Wezel * & pHead, NumerPunktu A, NumerPunktu B, DlugoscTrasy Odleglosc);
/** Funkcja dodajaca trase nieskierowana".
@author Paulina Urbas
@date   2018-01-08
@params pHead
@params A
@params B
@params Odleglosc
@return nic nie zwraca
*/
void DodajTraseNieskierowana(Wezel * & pHead, NumerPunktu A, NumerPunktu B, DlugoscTrasy Odleglosc);
/** Funkcja wypisujaca krawedz".
@author Paulina Urbas
@date   2018-01-08
@params pHead
@return nic nie zwraca
*/
void WypiszKrawedz(Krawedz* & pHead);
/** Funkcja usuwajaca krawedz grafu".
@author Paulina Urbas
@date   2018-01-08
@params pHead
@return nic nie zwraca
*/
void UsunKrawedz(Krawedz * & pHead);
#endif
