#include <iostream>
#include <fstream>
#include <string>

using namespace std;

struct ElemList2 // struktura listy dwukierunkowej
{
	int data;
	ElemList2* next, * prev;
};

ElemList2* listhead, * listtail;

ElemList2* findTail(ElemList2* head) //funkcja zwracajaca ogon listy
{
	if (head != NULL)
	{
		while (head->next != NULL)
		{
			head = head->next;
		}
	}
	return head;
}

void ListDisplay(ElemList2* head) //wyswietlanie listy
{
	while (head != NULL)
	{
		cout << head->data << " ";
		head = head->next;
	}
}

void push_front(ElemList2*& head, int val) //funkcja dodajaca element na poczatek listy
{
	ElemList2* p = new ElemList2;
	p->data = val;
	p->next = head;
	head = p;
}

void push_back(ElemList2*& tail, int val) //funkcja dodajaca element na koniec listy
{
	ElemList2* p = new ElemList2;
	
	p->data = val;
	p->prev = tail;
	tail = p;
}

void push_whereIndex(ElemList2*& head, int val, int in) //funkcja dodajaca element na miejsce elementu o danym indeksie
{
	ElemList2* p = new ElemList2;
	ElemList2* bufor1 = new ElemList2;
	ElemList2* bufor2 = new ElemList2;


	int counter = 0;
	p = head;

	while (p != NULL)
	{
		if (counter== in)
		{
			bufor1->data = p->data;
			p->data = val;

			while (p->next != NULL)
			{
				bufor2->data = p->next->data;
				p->next->data = bufor1->data;
				bufor1->data = bufor2->data;
				p = p->next;
			}
		}
		else
		{
			p = p->next;
			counter++;
		}
	}
}

void DeleteElem(ElemList2*& head, ElemList2*& tail, int val) //funkcja usuwajaca dany element z listy 
{
	ElemList2* p = findValue(head, val);
	if (p != NULL)
	{
		if (p->prev != NULL)
			p->prev->next = p->next;
		else
			head = p->next;

		if (p->next != NULL)
			p->next->prev = p->prev;
		else
			tail = p->prev;
		delete p;
	}
}

ElemList2* findValue(ElemList2* head, int val) //funkja szukajaca okreslonej wartosci w liscie
{
	while (head != NULL)
	{
		if (head->data == val)
			return head;
		head = head->next;
	}
	return NULL;
}

void ListLoad(ElemList2*& head, string filename) // zbudowanie listy z pliku
{
	int lineNum = 1; // numer linii, z ktorej zczytywane sa dane
	int size, liczba; // zmienna liczba przechowuje aktualnie zczytywana liczbe
	fstream File;
	File.open(filename);
	File >> size; // pierwszy element w pliku przechowuje ilosc elementow pliku
	while (size >= lineNum)
	{
		lineNum++;
		File >> liczba;
		push_front(listhead, liczba);
	}
}

void displayMenu()
{
	cout << endl;
	cout << "----- LISTA -----" << endl;
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

void ListMenu()
{
	char option;
	string fileName;
	int index, value;


	do {
		displayMenu();
		option = getche();
		cout << endl;
		switch (option) {
		case '1': //wczytytwanie listy z pliku
			cout << " Podaj nazwe zbioru:";
			cin >> fileName;
			ListLoad(listhead, fileName);
			ListDisplay(listhead);
			findTail(listhead);
			break;

		case '2': // usuwanie elemenu z listy
			cout << " Podaj wartosc:";
			cin >> value;
			DeleteELem(listhead, listtail, value);
			ListDisplay(listhead);
			break;

		case '3': //tutaj dodawanie elemetu do tablicy
			cout << " podaj index:";
			cin >> index;
			cout << " podaj wartosc:";
			cin >> value;
			cout << "Wartosc dodana na poczatek listy" << endl;
			push_front(listhead, value);
			ListDisplay(listhead);
			cout << "Wartosc dodana na koniec listy" << endl;
			push_back(listtail);
			ListDisplay(listhead);
			cout << "Wartosc dodana w miejsce o podanym indeksie "<<index<<" listy" << endl;
			push_whereIndex(listhead, value, index);
			break;

		case '4': //znajdowanie elemetu w liscie
			cout << " Podaj wartosc:";
			cin >> value;
			if (findValue(listhead, value))
				cout << "Podana wartosc jest w liscie" << endl;
			else
				cout << "Podanej wartosci nie ma w liscie" << endl;
			break;

		case '5':  // generowanie  listy
			cout << "Podaj ilosc elementow listy:";
			cin >> value;
			FileGenerator(value);
			ListDisplay(listhead);
			break;

		case '6':  // wyswietlanie listy
			ListDisplay(listhead);
			break;

		case '7': //eksperymenty
			break;
		}

	} while (option != '0');
}