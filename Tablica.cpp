#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include <windows.h>
//#include "Query.cpp"

using namespace std;


class Table
{
	int* tab;
	int cnt; //iloœæ elementów w tablicy
public:

	Table();
	~Table();

	void displayMenu();
	
	void loadFromFile(string FileName);

	bool IsValueInTable(int val);

	void addValue(int index, int value);

	void push_front(int value);

	void push_back(int value);

	void pop_back();

	void pop_front();

	void deleteFromTable(int index);

	void display();

	void Eksperymenty1();

	void DeleteTable();

	void Eksperymenty2();

	//void generateTable(int size);

};

Table::Table()
{
	cnt = 0;
	tab = NULL;
}

void Table::push_front(int value) // dodanie wartosci o indeksie 0, czyli pierwszej w tablicy
{
	if (cnt == 0 || tab == NULL) //jesli tablicy nie ma, to tworzymy ja
	{
		cnt++;
		tab = new int[cnt];
		tab[0] = value;
		return;
	}

	int* t = tab;  // tymczasowa tablica bedaca kopia wlasciwej 
	tab = new int[cnt + 1]; // zwiekszenie rozmiaru wlasciwej tablicy 
	for (int i = 0; i < cnt; i++)
	{
		tab[i + 1] = t[i];
	}
	delete[] t;
	tab[0] = value;
	cnt++;
}

void Table::push_back(int value)
{
	if (cnt == 0 || tab == NULL) //jesli tablicy nie ma, to tworzymy ja
	{
		tab = new int[cnt];
		tab[0] = value;
		return;
	}
	int* t = tab;
	tab = new int[cnt+1]; // utworzenie zwiekszonej tablicy 
	for (int i = 0; i < cnt; i++)
		tab[i] = t[i];
	tab[cnt] = value;
	cnt++;
	delete[] t;
}

void Table::addValue(int index, int value)
{
	if (index > cnt)
		return;
	if (index == 0)
	{
		push_front(value);
		return;
	}
	if (index == cnt)
	{
		push_back(value);
		return;
	}
	
	int* t = tab; // tymczasowa kopia pierwotnej tablicy
	tab = new int[cnt + 1]; // zwiekszenie wlasciwej tablicy 
	for (int i = 0; i < index; i++)
		tab[i] = t[i];
	tab[index] = value;
	for (int i = index; i < cnt; i++)
		tab[i + 1] = t[i];
	cnt++;
	delete[] t;
}

void Table::pop_back() // usuwanie ostatniego elementu tablicy 
{
	if (tab == NULL || cnt == 0) 
		return;
	cnt--;
	int* t = tab;
	tab = new int[cnt]; // utworzenie zmiejszonej tablicy 
	for (int i = 0; i < cnt ; i++)
	{
		tab[i] = t[i];
	}
	delete[] t;
}

void Table::pop_front() // usuwanie pierwszego elementu tablicy 
{
	if (tab == NULL || cnt == 0)
		return;
	cnt--;
	int* t = tab;
	tab = new int[cnt]; // utworzenie zmiejszonej tablicy 
	for (int i = 0; i < cnt; i++)
	{
		tab[i] = t[i+1];
	}
	delete[] t;
}

void Table::deleteFromTable(int index)
{
	if (index >= cnt)
		return;
	if (index == 0)
	{
		pop_front();
		return;
	}
	if (index == cnt - 1)
	{
		pop_back();
		return;
	}
	int* t = tab; // tymczasowa kopia pierwotnej tablicy
	tab = new int[cnt - 1]; // zmniejszenie wlasciwej tablicy 
	for (int i = 0; i < index; i++)
		tab[i] = t[i];
	for (int i = index; i < cnt; i++)
		tab[i] = t[i+1];
	cnt--;
	delete[] t;
}

void Table::loadFromFile(string FileName)
{
	if (tab != NULL)
		delete[] tab;
	int lineNum = 1; // numer linii, z ktorej zczytywane sa dane
	int size, liczba; // zmienna liczba przechowuje aktualnie zczytywana liczbe
	fstream File;
	File.open(FileName);
	File >> size; // pierwszy element w pliku przechowuje ilosc elementow pliku
	size = size;
	//tab = new int[size];
	while (size >= lineNum)
	{
		lineNum++;
		File >> liczba;
		push_front(liczba);
	}
	File.close();
}

void Table::display()
{
	for (int i = 0; i < cnt; i++)
		cout << tab[i] << " ";
	cout << endl;
}

void Table::displayMenu()
{
	cout << endl;
	cout << "----- Tablica -----" << endl;
	cout << "1.Wczytaj z pliku" << endl;
	cout << "2.Usun" << endl;
	cout << "3.Dodaj" << endl;
	cout << "4.Znajdz" << endl;
	cout << "5.Utworz losowo" << endl;
	cout << "6.Wyswietl" << endl;
	cout << "7.Test (pomiary)" << endl;
	cout << "0.Powrot do menu" << endl;
	cout << "Podaj opcje:";
}

bool Table::IsValueInTable(int val)
{
	for (int i = 0; i < cnt - 1; i++)
	{
		if (tab[i] == val)
		{
			cout << "Wartosc jest w tablicy" << endl;
			return true;
		}
	}
	return false;
}

Table::~Table()
{
	cnt = 0;
	delete[] tab;
}

void Table::DeleteTable()
{
	cnt = 0;
	delete[] tab;
}


void Table::Eksperymenty1()
{
	double avgTime1 = 0;
	double avgTime2 = 0;
	cout << "Trwa wykonywanie pomiaru..." << endl;
	loadFromFile("zzLiczby100000.txt");
	cout << "100k" << endl;

	int test_val = 123;
	int test_idx = 0;
	for (int i = 0; i < 2000; i++)
	{
		test_val = rand() % 1000 - 500;
		//test_idx = rand() %1000;

//		start = read_QPC(); // poczatek pomiaru 
		IsValueInTable(test_val);
//		elapsed = read_QPC() - start; // koniec pomiaru
//		avgTime1 += (1000000.0 * elapsed) / frequency;
	}
	avgTime1 = avgTime1 / 2000;
	//avgTime2 = avgTime2 / 2000;
	cout << "Sredni czas usuwania elementu [us]: " << avgTime1 << endl;
	//cout << "Sredni czas usuwania ostatniego elementu [us]: " << avgTime2 << endl;

	//delete[] tab; // usuwanie tablicy
}

void Table::Eksperymenty2()
{
	float avgTime1 = 0;
	int test_val = 123;
	int test_idx = 0;

	test_val = rand() % 1000 - 500;
	test_idx = rand() % 100000;
	
	loadFromFile("zzLiczby100000.txt");
	cout << "100k" << endl;
	cout << test_idx << endl;

//	start = read_QPC(); // poczatek pomiaru 
	addValue(test_idx, test_val);
//	elapsed = read_QPC() - start; // koniec pomiaru
//	avgTime1 += (1000000.0 * elapsed) / frequency;

	cout << "Sredni czas usuwania elementu [us]: " << avgTime1 << endl;

}