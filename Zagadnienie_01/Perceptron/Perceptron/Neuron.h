#pragma once
#include <iostream>
using namespace std;

class Neuron
{
public: 
	double obliczPojedynczeWejscie(int indeks) { return wejscia[indeks] * wagi[indeks]; }
	void sumujWszystkieWejscia(); 
	int obliczWyjscieNeuronu(); 
	void obliczNowaWage(int prawidlowaOdpowiedz, int odpowiedzNeuronu, int *macierzWejsc);
	
	Neuron(int amount, double wsplUczenia)
	{
		wejscia[0] = 0;
		wejscia[1] = 0;
		wejscia[2] = 0;
		wagi[0] = obliczPierwszaWage();
		wagi[1] = obliczPierwszaWage();
		wagi[2] = obliczPierwszaWage();
		wspolczynnikUczenia = wsplUczenia;
	}

	double obliczPierwszaWage();
	double wejscia[3]; 
	double wagi[3];
	double sumaWszystkichWejsc;
	int wartoscWyjsciowa;
	double wspolczynnikUczenia;
};