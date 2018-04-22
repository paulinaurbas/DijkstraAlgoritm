#pragma once
#include <iostream>
#include <string>
#include "trasy.h"
#ifndef DIJKSTRA_H
#define DIJKSTRA_H
using namespace std; 
/** Funkcja znajdujaca punkt startowy".
@author Paulina Urbas
@date   2018-01-23
@param pHead
@param A
@return nic nie zwraca
*/
Wezel * znajdzStartowy(Wezel * pHead, NumerPunktu A);
/** Funkcja znajdujaca najblizszy i nieodwiedzony wezel".
@author Paulina Urbas
@date   2018-01-23
@params pHead
@return nic nie zwraca
*/
Wezel * znajdzNajblizszyNieodwiedzony(Wezel * pHead);
/** Funkcja wykonujaca algorytm dijkstry".
@author Paulina Urbas
@date   2018-01-23
@param pHead
@param Startowy
@return nic nie zwraca
*/
void dijkstra(Wezel * & pHead, Wezel * & Startowy);
/** Funkcja wyswieltajaca komunikat o braku wezla w grafie".
@author Paulina Urbas
@date   2018-01-23
@param A
@return nic nie zwraca
*/
void Komunikat(NumerPunktu A);
/** Funkcja znajdujaca najkrotsze trasy od danego punktu dla calej listy punktow startowych".
@author Paulina Urbas
@date   2018-01-23
@param pHead
@return nic nie zwraca
*/
void ZnajdzWszystkieTrasy(Wezel * & pHead, ListaPunktowPolaczen * & pHeadList, string & nazwapliku);
/** Funkcja drukujaca trasy".
@author Paulina Urbas
@date   2018-01-23
@param pHead
@param PunktStartowy
@return nic nie zwraca
*/
void DrukujListeTras(Wezel * & pHead, Wezel * PunktStartowy);
/** Funkcja zapisujaca do pliku".
@author Paulina Urbas
@date   2018-01-23
@param pHead
@param A
@return nic nie zwraca
*/
void ZapisdoPliku(string & nazwapliku, Wezel * & pHead, Wezel * A);

#endif
