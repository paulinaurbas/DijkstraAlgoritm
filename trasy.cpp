#include <iostream>
#include <string>
#include <fstream>
#include <iomanip>
#include "trasy.h"
using namespace std; 
//definicje funkcja 
int SprawdzWywolanie(int argc, char *argv[], string & nazwaplikuwejsciowego, string & WyjsciowyWierzcholki, string & WyjsciowyOdleglosci)
{
	int ok = 0;
	if (argc <= 7) // sprawdzenie czy przy wywolaniu z listy polecen zostala podana dobra liczba argumnetow 
	{
		for (int i = 1; i < argc; i++)
		{
			if (string(argv[i]) == string("-h"))
			{
				return 1;
			}
			if (string(argv[i]) == string("-g"))
			{
				nazwaplikuwejsciowego = string(argv[i + 1]);
				ok++;
			}
			if (string(argv[i]) == string("-w"))
			{
				WyjsciowyWierzcholki = string(argv[i + 1]);
				ok++;
			}
			if (string(argv[i]) == string("-o"))
			{
				WyjsciowyOdleglosci = string(argv[i + 1]);
				ok++;
			}
		}
		if (ok == 3)
		{
			return 0;
		}
		else
		{
			return 2;
		}
	}
	else
	{
		return 2;
	}
}
void Pomoc()
{
		cout << "POMOC" << endl;
		cout << "Aby podac nazwe pliku wejsciowego nalezy uzyc komendy -g, a nastepnie podac nazwe pliku wejsciowego" << endl;
		cout << "Aby podac nazwe pliku wejsciowego z wierzcholkami nalezy uzyc komendy -w, a nastepnie podac nazwe pliku wyjsciowego" << endl;
		cout << "Aby podac nazwe pliku wyjsciowego z wynikami nalezy uzyc komendy -o, a nastepnie podac nazwe pliku wyjsciowego" << endl;
}
Wezel * StworzWezel(Wezel * & pHead, NumerPunktu A) //sprawdza czy lista jest pusta, czy wezel istnieje, Jesli nie istnieje to dodaje nowy, jesli istnieje to zwraca istniejacy 
{
	if (!pHead)
	{
		pHead = new Wezel{ A, nullptr, nullptr, 0, false, 0};
		return pHead;
	}
	else
	{
		Wezel * pomoc = pHead;
		bool nie_ma = true;
		while (pomoc != nullptr && nie_ma)
		{
			if (pomoc->Wierzcholek == A)
			{
				//nie_ma = false;
				return pomoc;
			}
			else
			{
				pomoc = pomoc->Nastepny;
			}
		}
		if (nie_ma)
		{
			auto p = pHead;
			while (p->Nastepny)
			{
				p = p->Nastepny;
			}
			p->Nastepny = new Wezel{ A, nullptr, nullptr, 0, false, 0};
			return p->Nastepny;
		}
		// KS: Co zwroci ta funkcja w tym miejscu?
	}
}
void DodajKrawedz(Wezel * A, Wezel * B, DlugoscTrasy Odleglosc) //dodaje krawedz
{
    A->pKrawedzie = new Krawedz { Odleglosc, A, B, A->pKrawedzie }; // dodalismy na poczatek listy krawedzie :-) 
}
void DodajTraseSkierowana( Wezel * & pHead, NumerPunktu A, NumerPunktu B, DlugoscTrasy Odleglosc)
	{
	Wezel * w1 = StworzWezel(pHead, A);
	Wezel * w2 = StworzWezel(pHead, B);
	DodajKrawedz(w1, w2, Odleglosc);
	}
void DodajTraseNieskierowana(Wezel * & pHead, NumerPunktu A, NumerPunktu B, DlugoscTrasy Odleglosc)
{
    DodajTraseSkierowana(pHead, A, B, Odleglosc);
    DodajTraseSkierowana(pHead, B, A, Odleglosc);
}
bool CzySkierowany(string znak)
{
	if (znak == "->")
	{
		return true;
	}
	else
	{
		return false;
	}
}
void UsunListeWezlow(Wezel * & pHead)
{
		while (pHead)
		{
			auto p = pHead;
		   UsunKrawedz(p->pKrawedzie);
			pHead = pHead->Nastepny;
			delete p;
		}
}
void UsunListePolaczen (ListaPunktowPolaczen * & pHead)
{
	while (pHead)
	{
		auto p = pHead;
		pHead = pHead->pNext;
		delete p;
	}
}
void UsunWezel(Wezel * & pHead, Wezel * element)
{
		Wezel * p;

		if (pHead == element)
		{
		   pHead = pHead->Nastepny;
      	delete element;
		}
		else
		{
			p = pHead;
			while (p->Nastepny != element) 
			   p = p->Nastepny;
			p->Nastepny = element->Nastepny;
			delete element;
		}
	}
void DrukujListeWezlow(Wezel * & pHead)
{
	if (pHead)
	{
		auto p = pHead;
		while (p)
		{
		    //cout << "A: "<< p->Wierzcholek << "	";
			WypiszKrawedz(p->pKrawedzie);
			p = p->Nastepny;
		}
	}
}
void UsunKrawedz(Krawedz * & pHead)
{
	while (pHead)
	{
		auto p = pHead;
		pHead = pHead->kNastepny;
		delete p;
	}
}
void WypiszKrawedz(Krawedz * & pHead)
{
	if (pHead)
	{
		cout << "A: " << pHead->Start->Wierzcholek <<"	";
		cout << "Odleglosc: " << pHead->Odleglosc << "	";
		cout << "B: " << pHead->Koniec->Wierzcholek << "	";
		cout << endl;
		WypiszKrawedz(pHead->kNastepny);
	}
}
void OdczytzPlikuGrafu(const string & nazwapliku, Wezel * & pHead)
{

   
   // probne utworzenie pliku w tej samej lokalizacji:
   std::ofstream testowy ("../../Doc"+ nazwapliku+"test");
   testowy.close();
   //////////// koniec testu
   
	//cout << "punkt kontrolny 1" << endl;
	ifstream plik;
	plik.open("Users/User/Documents/Paulina-Urbas-gr07-repo/projekt-02/Doc/"+ nazwapliku); //otwieranie pliku 
	try
	{
		//cout << "punkt kontrolny 2" << endl;
		
		if (plik.good() == false) //sprawdzenie czy plik moze byc otwarty 
		{
			//cout << "punkt kontrolny 3" << endl;
			throw ("nie znaleziono pliku<" + nazwapliku + ">!");
			plik.close(); //zamykanie pliku 
		}
		else
		{
			//cout << "punkt kontrolny 4" << endl;
			try
			{
			//	cout << "punkt kontrolny 5" << endl;
				NumerPunktu A;
				NumerPunktu B;
				DlugoscTrasy Odleglosc;
				string Kierunek;
				char znak = 0;
				while (!plik.eof())
				{

					plik >> A;
					plik >> Kierunek;
					plik >> B;
					plik >> znak;
					plik >> Odleglosc;
					if (CzySkierowany(Kierunek))
					{
						DodajTraseSkierowana(pHead, A, B, Odleglosc);
						//cout << "trasa jednokierunkowa " << A << " --> " << B << " : odleglosc == " << Odleglosc << endl;
					}
					else
					{
						//cout << " 3 b" << endl;
						DodajTraseNieskierowana(pHead, A, B, Odleglosc);
						//cout << "trasa dwukierunkowa " << A << " --- " << B << " : odleglosc == " << Odleglosc << endl;
					}
				}
				plik.close(); //zamykanie pliku
			}
			catch (...)
			{
			plik.close(); //zamykanie pliku
			throw("Blad odczytu z pliku" + nazwapliku + "\n");
		}
		}
		}
		
	catch (...)
	{
		//throw("Plik<" + nazwapliku + "> nie zostal znaleziony!");
	}
	
}
void DrukujListePunktow(ListaPunktowPolaczen * & pHead)
{
	if (pHead)
		{
			auto p = pHead; 
			while (p)
			{
				cout << p->A << endl;
				p = p->pNext;
			}
	}
}
void OdczytzPlikuPunktow(const string & nazwapliku, ListaPunktowPolaczen *&  pHead)
{
	ifstream plik;
	plik.open(nazwapliku);
	try
	{
		if (plik.good() == false) //sprawdzenie czy plik moze byc otwarty 
		{
			throw ("nie znalezionio pliku<" + nazwapliku + ">!");
			plik.close(); //zamykanie pliku 
		}
		else
		{
			NumerPunktu wartosc;
			while(!plik.eof())
			{
				try
				{
					plik >> wartosc;
					if (!pHead)
					{
						pHead = new ListaPunktowPolaczen{ wartosc, nullptr };
					}
					else
					{
						auto p = pHead;
						while (p->pNext)
						{
							p = p->pNext;
						}
						p->pNext = new ListaPunktowPolaczen{ wartosc, nullptr };
					}
				}
				catch (...)
				{
					throw("Blad odczytu z pliku" + nazwapliku + "\n");
				}
			}
		}
	}
	catch (...)
	{
		throw("Plik<" + nazwapliku + "> nie zostal znaleziony!");
	}

}

 
