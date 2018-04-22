
/** @file */

// Projekt2.cpp : Defines the entry point for the console application.
//
#include <iostream>
#include <string>
#include <fstream>
#include <iomanip>
#include "trasy.h"
#include "Dijkstra.h"
#include "Grafy.h"
#include "debug.h"
#include "../../../memory-leaks/debug_new.h"

using namespace std;
int main(int argc, char *argv[])
{
	try
	{
		string nazwaplikuwejsciowego;
		string WejsciowyWierzcholki;
		string WyjsciowyOdleglosci;
		int blad = SprawdzWywolanie(argc, argv, nazwaplikuwejsciowego, WejsciowyWierzcholki, WyjsciowyOdleglosci);
		switch (blad)
		{
		case 0:
		{
			//lista numer 1, czyli lista z punktami miedzy ktorymi trzeba znalezc polaczenia 
			ListaPunktowPolaczen * pGlowa = 0;
			debug(pGlowa);
			cout << endl;
			cout << "Lista punktow pomiedzy ktorymi nalezy odczytac odleglosci:" << endl;
			cout << endl;
			OdczytzPlikuPunktow(WejsciowyWierzcholki, pGlowa);
                        debug(pGlowa);
			//lista numer 2, czyli listo-drzewo z grafem 
			DrukujListePunktow(pGlowa);
			Wezel * G = 0;
			DodajTraseSkierowana(G, 1, 2, 4);
			DodajTraseSkierowana(G, 1, 3, 2);
			DodajTraseSkierowana(G, 2, 3, 3);
			DodajTraseSkierowana(G, 3, 2, 1);
			DodajTraseSkierowana(G, 3, 5, 5);
			DodajTraseSkierowana(G, 2, 5, 3);
			DodajTraseSkierowana(G, 2, 4, 2);
			DodajTraseSkierowana(G, 5, 4, 1);
			DodajTraseSkierowana(G, 3, 4, 4);
			OdczytzPlikuGrafu(nazwaplikuwejsciowego, G); 
			cout << "Lista wezlow:" << endl;
			DrukujListeWezlow(G);
			ZnajdzWszystkieTrasy(G, pGlowa, WyjsciowyOdleglosci);
			UsunListePolaczen(pGlowa); //usuniecie 1 listy
			UsunListePolaczen(pGlowa); //usuniecie 1 listy
			UsunListeWezlow(G); //usuniecie listo-drzewa
			UsunListeWezlow(G); //usuniecie listo-drzewa
            debug(G);
			return 0;
			break;
		}
		case 1:
		{
			Pomoc();
			return 0;
			break;
			getchar();
			getchar();
		}
		case 2:
		{
			cout << "Podano za malo parametrow" << endl; 
			Pomoc();
			return 0;
			break;
			getchar();
			getchar();
		}
		}
	}
	catch (...)
	{
		throw;
		return 0;
		getchar();
		getchar();
	}
}
