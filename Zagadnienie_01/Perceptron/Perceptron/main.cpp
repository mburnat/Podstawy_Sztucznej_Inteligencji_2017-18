#include <iostream>
#include "Neuron.h"
#include <time.h>
#include <fstream>
using namespace std;

void ustawWartosciWejsc(Neuron& neuron, bool testowanie);
void ucz(Neuron& neuron, bool testowanie);

fstream PLIK_WYNIK_UCZENIA;
fstream PLIK_WYNIK_TESTOWANIA;
fstream PLIK_DO_NAUKI;
fstream PLIK_DO_TESTOWANIA;
int ILOSC_ZLYCH_ODPOWIEDZI;
int ILOSC_DOBRYCH_ODPOWIEDZI;
int PRAWIDLOWA_ODPOWIEDZ;

int main()
{
	srand(time(NULL));
	Neuron neuron(3, 0.1);
	PLIK_WYNIK_UCZENIA.open("wynik_nauki.txt", ios::out);
	PLIK_WYNIK_TESTOWANIA.open("wynik_testowania.txt", ios::out);
	PLIK_DO_NAUKI.open("do_nauki.txt", ios::in);
	PLIK_DO_TESTOWANIA.open("do_testowania.txt", ios::in);

	do
	{
		cout << "1. Ucz sie" << endl;
		cout << "2. Testuj " << endl;
		cout << "3. Wyjdz" << endl;

		int wybor;
		cin >> wybor;
		switch (wybor)
		{
		case 1:
			int liczbaDanych;
			ILOSC_ZLYCH_ODPOWIEDZI = 0;
			ILOSC_DOBRYCH_ODPOWIEDZI = 0;
			cout << "Wpisz liczbe danych: " << endl;
			cin >> liczbaDanych;
			
			for (int i = 0; i < liczbaDanych; i++)
			{
				ucz(neuron, false);
			}

			PLIK_WYNIK_UCZENIA << "ILOSC ZLYCH ODPOWIEDZI: " << ILOSC_ZLYCH_ODPOWIEDZI << endl;
			PLIK_WYNIK_UCZENIA << "ILOSC DOBRYCH ODPOWIEDZI: " << ILOSC_DOBRYCH_ODPOWIEDZI << endl;
			break;

		case 2:
			ILOSC_ZLYCH_ODPOWIEDZI = 0;
			ILOSC_DOBRYCH_ODPOWIEDZI = 0;
			
			for (int i = 0; i < 50; i++)
			{
				ucz(neuron, true);
			}

			PLIK_WYNIK_TESTOWANIA << "ILOSC ZLYCH ODPOWIEDZI: " << ILOSC_ZLYCH_ODPOWIEDZI << endl;
			PLIK_WYNIK_TESTOWANIA << "ILOSC DOBRYCH ODPOWIEDZI: " << ILOSC_DOBRYCH_ODPOWIEDZI << endl;
			break;

		case 3:
			PLIK_WYNIK_UCZENIA.close();
			PLIK_WYNIK_TESTOWANIA.close();
			PLIK_DO_TESTOWANIA.close();
			PLIK_DO_NAUKI.close();

			return 0;
		}
	} while (true);

	return 0;
}

void ustawWartosciWejsc(Neuron& neuron, bool testowanie)
{
	if (testowanie == false)
	{
		int czyt1, czyt2, czyt3, odp;
		PLIK_DO_NAUKI >> czyt1;
		PLIK_DO_NAUKI >> czyt2;
		PLIK_DO_NAUKI >> czyt3;
		PLIK_DO_NAUKI >> odp;

		neuron.wejscia[0] = czyt1;
		neuron.wejscia[1] = czyt2;
		neuron.wejscia[2] = czyt3;
		PRAWIDLOWA_ODPOWIEDZ = odp;

		PLIK_WYNIK_UCZENIA << "Wej 0b: " << neuron.wejscia[0];
		PLIK_WYNIK_UCZENIA << " Wej 1: " << neuron.wejscia[1];
		PLIK_WYNIK_UCZENIA << " Wej 2: " << neuron.wejscia[2];
		PLIK_WYNIK_UCZENIA << " POdp: " << PRAWIDLOWA_ODPOWIEDZ;
	}

	else
	{
		int zczyt1, zczyt2, zczyt3, odpow;
		PLIK_DO_TESTOWANIA >> zczyt1;
		PLIK_DO_TESTOWANIA >> zczyt2;
		PLIK_DO_TESTOWANIA >> zczyt3;
		PLIK_DO_TESTOWANIA >> odpow;

		neuron.wejscia[0] = zczyt1;
		neuron.wejscia[1] = zczyt2;
		neuron.wejscia[2] = zczyt3;
		PRAWIDLOWA_ODPOWIEDZ = odpow;

		PLIK_WYNIK_TESTOWANIA << "Wej 0b: " << neuron.wejscia[0];
		PLIK_WYNIK_TESTOWANIA << " Wej 1: " << neuron.wejscia[1];
		PLIK_WYNIK_TESTOWANIA << " Wej 2: " << neuron.wejscia[2];
		PLIK_WYNIK_TESTOWANIA << " POdp: " << PRAWIDLOWA_ODPOWIEDZ;
	}
}

void ucz(Neuron& neuron, bool testowanie)
{
	ustawWartosciWejsc(neuron, testowanie);
	neuron.sumujWszystkieWejscia();
	int odpowiedzNeuronu = neuron.obliczWyjscieNeuronu();
	int *macierzWejsc = new int[2];
	macierzWejsc[0] = neuron.wejscia[1];
	macierzWejsc[1] = neuron.wejscia[2];

	if (odpowiedzNeuronu)
	{
		if (PRAWIDLOWA_ODPOWIEDZ == 0)
		{
			ILOSC_ZLYCH_ODPOWIEDZI++;
			if (testowanie == false)
			{
				PLIK_WYNIK_UCZENIA << " Odp: 1";
				neuron.obliczNowaWage(PRAWIDLOWA_ODPOWIEDZ, odpowiedzNeuronu, macierzWejsc);
				PLIK_WYNIK_UCZENIA << " -" << " ZMIANA WAG: " << neuron.wagi[0] << " " << neuron.wagi[1] << " " << neuron.wagi[2] << endl;
			}

			else
			{
				PLIK_WYNIK_TESTOWANIA << " Odp: 1 -" << endl;
			}

		}

		else
		{
			ILOSC_DOBRYCH_ODPOWIEDZI++;

			if (testowanie == false)
			{
				PLIK_WYNIK_UCZENIA << " Odp: 1";
				PLIK_WYNIK_UCZENIA << " +" << " ZOSTAWIENIE WAG: " << neuron.wagi[0] << " " << neuron.wagi[1] << " " << neuron.wagi[2] << endl;
			}

			else
			{
				PLIK_WYNIK_TESTOWANIA << " Odp: 1 +" << endl;
			}
		}
	}

	else 
	{
		if (PRAWIDLOWA_ODPOWIEDZ == 1)
		{
			ILOSC_ZLYCH_ODPOWIEDZI++;
	
			if (testowanie == false)
			{
				PLIK_WYNIK_UCZENIA << " Odp: 0";
				neuron.obliczNowaWage(PRAWIDLOWA_ODPOWIEDZ, odpowiedzNeuronu, macierzWejsc);
				PLIK_WYNIK_UCZENIA << " -" << " ZMIANA WAG: " << neuron.wagi[0] << " " << neuron.wagi[1] << " " << neuron.wagi[2] << endl;
			}

			else
			{
				PLIK_WYNIK_TESTOWANIA << " Odp: 0 -" << endl;
			}
		}

		else
		{
			ILOSC_DOBRYCH_ODPOWIEDZI++;
		
			if (testowanie == false)
			{
				PLIK_WYNIK_UCZENIA << " Odp: 0";
				PLIK_WYNIK_UCZENIA << " +" << " ZOSTAWIENIE WAG: " << neuron.wagi[0] << " " << neuron.wagi[1] << " " << neuron.wagi[2] << endl;
			}

			else
			{
				PLIK_WYNIK_TESTOWANIA << " Odp: 0 +" << endl;
			}
		}
	}
}