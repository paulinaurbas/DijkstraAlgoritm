#include <iostream>
#include <string>
#include <limits>
#include <fstream>
#include "Dijkstra.h"
#include "trasy.h"
#include "debug.h"
using namespace std;

Wezel * znajdzStartowy(Wezel * pHead, NumerPunktu A)
{
	Wezel * pStartowy = nullptr;
	while (pHead)
	{
		if (pHead->Wierzcholek == A)
		{
			pStartowy = pHead;
			pStartowy->odleglosc = 0;
		}
		else // niestartowy
		{
			pHead->odleglosc = std::numeric_limits< double >::max();
		
		}
		pHead = pHead->Nastepny;
	}
	return pStartowy;

}
Wezel * znajdzNajblizszyNieodwiedzony(Wezel * pHead)
{
	double mini = std::numeric_limits<double>::max();
	auto p = pHead;
	Wezel * pNajblizszy = nullptr;
	while (p)
	{
		if (!p->Odwiedzony)
		{
			if (p->odleglosc < mini)
			{
				mini = p->odleglosc;
				pNajblizszy = p;
			}
		}
		p = p->Nastepny;
	}
	return pNajblizszy;
}
void dijkstra(Wezel * & pHead, Wezel * & Startowy)
{
	Wezel * pNajblizszy = znajdzNajblizszyNieodwiedzony(pHead);
	while (pNajblizszy) // jezeli w ogole jest 
	{
		pNajblizszy->Odwiedzony = true;
		// relaksacja wszystkich krawedzi wychodzacych z najblizszego
		// to do 
		auto p = pNajblizszy->pKrawedzie;
		while (p != nullptr)
		{
			if (p->Odleglosc + pNajblizszy->odleglosc < p->Koniec->odleglosc)
			{
				p->Koniec->Poprzednik = pNajblizszy->Wierzcholek;
				p->Koniec->odleglosc = p->Odleglosc + pNajblizszy->odleglosc;
			}
			p = p->kNastepny;
		}
		pNajblizszy = znajdzNajblizszyNieodwiedzony(pHead);
	}
}
void Komunikat(NumerPunktu A)
{
	cout << "Nie ma takiego wezla: " << A << " w grafie" << endl;
}
void ZnajdzWszystkieTrasy(Wezel * & pHead, ListaPunktowPolaczen * & pHeadList, string & nazwapliku)
{
	ListaPunktowPolaczen * pomoc = pHeadList;
	while (pomoc)
	{
		if (znajdzStartowy(pHead, pomoc->A) == nullptr)
		{
			Komunikat(pomoc->A);
		}
		else
		{
			Wezel * w = znajdzStartowy(pHead, pomoc->A);
			cout << "Oto odleglosci dla startowego punktu numer:" << w->Wierzcholek << endl;
			dijkstra(pHead, w);
			DrukujListeTras(pHead,w);
			ZapisdoPliku(nazwapliku, pHead, w);
			cout << endl;
		}
		pomoc = pomoc->pNext;
	}
}
void DrukujListeTras(Wezel * & pHead, Wezel * PunktStartowy)
{
	if (pHead)
	{
		auto p = pHead;
		while (p)
		{
			cout << " " << PunktStartowy->Wierzcholek << "-> " << p->Poprzednik << "-> " << p->Wierzcholek << ": " << p->odleglosc << endl;
			p = p->Nastepny;
		}
	}
}
void ZapisdoPliku(string & nazwapliku, Wezel * & pHead, Wezel * PunktStartowy)
{
	fstream plik;
	plik.open(nazwapliku, ios::out); //otworzenie pliku 
	if (plik.is_open() == false)
	{
		return;
	}
	else
	{
		plik << endl;
		plik << "Odpowiedzi" << endl;
		if (pHead)
		{
			auto p = pHead;
			while (p)
			{
				plik <<" " << PunktStartowy->Wierzcholek << "-> " << p->Wierzcholek << "-> " << p->Poprzednik << " " << p->odleglosc << endl;
				p = p->Nastepny;
			}
		}
		plik.close();
	}
}