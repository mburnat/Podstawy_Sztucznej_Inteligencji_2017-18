#include "Neuron.h"
#include <time.h>

void Neuron::sumujWszystkieWejscia()
{
	double suma = 0;

	for (int i = 0; i < 3; i++)
	{
		suma += obliczPojedynczeWejscie(i);
	}

	sumaWszystkichWejsc = suma;
}

int Neuron::obliczWyjscieNeuronu()
{
	if (sumaWszystkichWejsc > 0)
	{
		wartoscWyjsciowa = 1;
		return wartoscWyjsciowa;
	}

	else
	{
		wartoscWyjsciowa = 0;
		return wartoscWyjsciowa;
	}
}

void Neuron::obliczNowaWage(int prawidlowaOdpowiedz, int odpowiedzNeuronu, int* macierzWejsc)
{
	wagi[0] += wspolczynnikUczenia * (prawidlowaOdpowiedz - odpowiedzNeuronu);

	for (int i = 1; i < 3; i++)
	{
		wagi[i] += wspolczynnikUczenia * (prawidlowaOdpowiedz - odpowiedzNeuronu) * macierzWejsc[i - 1];
	}
}

double Neuron::obliczPierwszaWage()
{
	double waga = ((double)rand() / (RAND_MAX));
	return waga;
}