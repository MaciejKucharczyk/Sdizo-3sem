#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include <windows.h>
#include "Lista.h"

using namespace std;

List::List()
{
	head = tail = NULL;
}

// Usuwa listê z pamiêci
List::~List()
{
	cout << "Nic nie robie" << endl;
}

ElemList* List::findTail(ElemList* head) //funkcja zwracajaca ogon listy
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

ElemList* List::IsValueInList(ElemList* head, int val)
{
	while (head != NULL)
	{
		if (head->data == val)
			return head;
		head = head->next;
	}
	return NULL;
}

void List::addValue(int index, int value)
{

}

void List::deleteFromList(ElemList*& head, ElemList*& tail, int val)
{
	ElemList* p = IsValueInList(head, val);
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

void List::display(ElemList* head)
{
	while (head != NULL)
	{
		cout << head->data << " ";
		head = head->next;
	}
	cout << endl;
}

void List::displayBackwards(ElemList* tail)
{
	while (tail != NULL)
	{
		cout << tail->data << " ";
		tail = tail->prev;
	}
}

/*void List::generateList(int size)
{

}*/

void List::push_front(ElemList*& head, int val) //funkcja dodajaca element na poczatek listy
{
	ElemList* p = new ElemList;
	p->data = val;
	p->next = head;
	p->prev = NULL;
	head = p;

	if (p->next) 
		p->next->prev = p;
	else 
		tail = p;
}

void List::push_back(ElemList*& tail, int val) //funkcja dodajaca element na koniec listy
{
	ElemList* p = new ElemList;

	p->data = val;
	p->prev = tail;
	p->next = NULL;
	tail = p;
}

void List::push_whereIndex(ElemList*& head, int val, int in) //funkcja dodajaca element na miejsce elementu o danym indeksie
{
	ElemList* p = new ElemList;
	ElemList* bufor1 = new ElemList;
	ElemList* bufor2 = new ElemList;


	int counter = 0;
	p = head;

	while (head != NULL)
	{
		if (counter == in)
		{
			bufor1->data = head->data;
			head->data = val;

			while (head->next != NULL)
			{
				bufor2->data = head->next->data;
				head->next->data = bufor1->data;
				bufor1->data = bufor2->data;
				head = head->next;
			}
			break;
		}
		else
		{
			head = head->next;
			counter++;
		}
	}
}

void List::loadFromFile(ElemList*&head, string filename)
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
		push_front(head, liczba);
	}
	File.close();
}