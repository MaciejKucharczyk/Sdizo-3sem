#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include <windows.h>
//#include "Query.cpp"

using namespace std;

struct ElemList
{
	ElemList* next, * prev;   // nastêpnik i poprzednik
	int data;
};

class List
{
	ElemList* head, * tail;
public:

	List();
	~List();

	void displayMenu();

	void loadFromFile(string filename);

	ElemList* IsValueInList(int val);

	void addValue(int index, int value);

	void deleteFromList(int val);

	void pop_front();

	void pop_back();

	void DeleteThis(ElemList* p);

	void display();

	void displayBackwards();

	//	void generateList(int size);

	ElemList* findTail(); //funkcja zwracajaca ogon listy

	void push_front(int val);

	void push_back(int val);

	void push_whereIndex(int val, int in);

	void eksperymenty();

	void DeleteAll();

	int countElements();


};

void List::displayMenu()
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


List::List()
{
	head = tail = NULL;
}

// Usuwa listê z pamiêci
List::~List()
{
	while (head)
		pop_front();
}

ElemList* List::findTail() //funkcja zwracajaca ogon listy
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

ElemList* List::IsValueInList(int val)
{
	ElemList* p;
	p = head;

	while (p != NULL)
	{
		if (p->data == val)
			return p;
		p = p->next;
	}
	return NULL;
}

int List::countElements()
{
	int elements = 0;
	ElemList* p;
	p = head;

	while (p != NULL)
	{
		elements++;
		p = p->next;
	}
	return elements;
}

void List::addValue(int index, int value)
{

}

void List::pop_front()
{
	if (head != NULL)
		DeleteThis(head);

}

void List::pop_back()
{
	if (tail != NULL)
		DeleteThis(tail);
}

void List::DeleteThis(ElemList* p)
{
		if (p->prev)
			p->prev->next = p->next;
		else
			head = p->next;
		if (p
			->next)
			p->next->prev = p->prev;
		else
			tail = p->prev;
		delete p;
}

void List::deleteFromList(int val)
{
	ElemList* p = IsValueInList(val);
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

void List::display()
{
	ElemList* p;
	p = head;

	while (p != NULL)
	{
		cout << p->data << " ";
		p = p->next;
	}
	cout << endl;
}

void List::displayBackwards()
{
	ElemList* p;

	p = tail;
	while (p != NULL)
	{
		cout << p->data << " ";
		p = p->prev;
	}
}


void List::push_front(int val) //funkcja dodajaca element na poczatek listy
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

void List::push_back(int val) //funkcja dodajaca element na koniec listy
{
	ElemList* p = new ElemList;

	p->data = val;
	p->prev = tail;
	p->next = NULL;
	tail = p;
	if (p->prev)
		p->prev->next = p;
	else 
		head = p;
}

void List::push_whereIndex(int val, int in) //funkcja dodajaca element na miejsce elementu o danym indeksie
{
	ElemList* p = new ElemList;
	p->data = val;
	ElemList* startElem;
	int counter = 0; //licznik indeksu

	if (in == 0)
	{
		push_front(val);
		return;
	}
	in--;

	startElem = head;
	while (counter != in)
	{
		startElem = startElem->next;
		counter++;
	}

	ElemList* prevItem = startElem;
	ElemList* nextItem = nullptr;

	if (prevItem == tail || prevItem == nullptr)
		push_back(val);
	else
	{
		//Znajdujemy element, który bêdzie nastêpnikiem nowego.
		nextItem = prevItem->next;
		prevItem->next = p;
		nextItem->prev = p;

		//Na koniec ustawiamy odpowiednie wskaŸniki nowego elementu 
		p->next = nextItem;
		p->prev = prevItem;
	}
	/*ElemList* p = new ElemList;
	ElemList* bufor1 = new ElemList;
	ElemList* bufor2 = new ElemList;

	if (in == 0)
	{
		push_front(val);
		return;
	}
	if (in == countElements() - 1)
	{
		push_back(val);
		return;
	}
	
	int counter = 0;
	p = head;
	bufor1 = head;

	while (p != NULL)
	{
		if (counter == in)
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
			return;
		}
		else
		{
			p = p->next;
			bufor1 = bufor1->next;
			counter++;
		}
	}*/
}

void List::loadFromFile(string filename)
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
		push_front(liczba);
	}
	File.close();
}

void List::DeleteAll()
{
	while (head)
		pop_front();
}

void List::eksperymenty()
{
	float avgTime1 = 0;
	float avgTime2 = 0;
	cout << "Trwa wykonywanie pomiaru..." << endl;
	loadFromFile("zzLiczby100000.txt");
	cout << "100k" << endl;

	ElemList* g;
	g = head;

	int licznik = 123;
	int indeksik = 0; 
	for (int i = 0; i < 2000; i++)
	{	
		// ======================================
		ElemList* g;
		g = head;
		for (int q = 0; q < rand() % 100000; q++)
		{
			g = g->next;							// losowanie elementu do usuniecia
			licznik = g->data;
		}
		//======================================= 

		licznik = rand() % 10000 - 5000;
		//indeksik = rand() %100000;
		
//		start = read_QPC(); // poczatek pomiaru 
		IsValueInList(licznik);
//		elapsed = read_QPC() - start; // koniec pomiaru
//		avgTime1 += (1000000.0 * elapsed) / frequency;

		pop_front(); // usuniecie elementu, aby zachowac ten sam rozmiar listy 

		for (int j = 0; j < 3000; j++) // petla zmieniajaca n pierwszych i n ostatnich elementow listy (n_max dobrane do wielkosci pliku)
		{
			pop_back();
			push_front(rand()%10000);
		}
	}
	avgTime1 = avgTime1/2000;
	//avgTime2 = avgTime2 /5000;
	cout << "Sredni czas znajdowania elementu [us]: " << avgTime1 <<endl;
	//cout << "Sredni czas dodawania ostatniego elementu [us]: " << avgTime2 << endl;

	DeleteAll(); // usuwanie listy
}