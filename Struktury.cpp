#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include <windows.h>
//#include "Lista.cpp"

using namespace std;

long long int read_QPC() // funkcja mierzaca czas algorytmu
{
	LARGE_INTEGER count;
	QueryPerformanceCounter(&count);
	return((long long int)count.QuadPart);
}

long long int frequency, start, elapsed;

struct ElemList2 // struktura listy dwukierunkowej
{
	int data;
	ElemList2* next, * prev;
};

ElemList2* listhead, * listtail;

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

void ListDisplayBackwards(ElemList2* tail) //wyswietlanie listy od tylu
{
		//ElemList2 * tail = new ElemList2;
		//tail = findTail(head);
		while (tail!= NULL)
		{
			if(tail->prev!=NULL)
			{
				cout << tail->data << " ";
				tail = tail->prev;
			}
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
	//ElemList2* tail = new ElemList2;
	//tail = findTail(head);
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
	File.close();
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

void FileGenerator(int size) //funkcja generuje plik z liczbami (ilosc liczb jest rowna size)
{
    string file;
    srand(time(NULL));
    cout << "Wprowadz nazwe pliku: " << endl;
    cin >> file;
    ofstream MyFile;
    MyFile.open(file);
    MyFile << size << endl;
    for (int i = 0; i < size; i++)
        MyFile << rand() % 10000000000000 - 10000 << endl;
    MyFile.close();
}

void ListMenu()
{
	int option;
	string fileName;
	int index, value;


	do {
		displayMenu();
		cin >> option;
		cout << endl;
		switch (option) {
		case 1: //wczytytwanie listy z pliku
			cout << " Podaj nazwe zbioru:";
			cin >> fileName;
			start = read_QPC(); // poczatek pomiaru 
			ListLoad(listhead, fileName);
			listtail = findTail(listhead);
			ListDisplay(listhead);
			//ListDisplayBackwards(listhead);
			elapsed = read_QPC() - start; // koniec pomiaru 
			cout << "Czas[ms] = " << setprecision(0) << (1000.0 * elapsed) / frequency << endl;

			break;

		case 2: // usuwanie elemenu z listy
			cout << " Podaj wartosc:";
			cin >> value;
			start = read_QPC(); // poczatek pomiaru 
			DeleteElem(listhead, listtail, value);
			elapsed = read_QPC() - start; // koniec pomiaru 
			cout << "Czas[ms] = " << setprecision(0) << (1000.0 * elapsed) / frequency << endl;

			ListDisplay(listhead);
			break;

		case 3: // dodawanie elemetu do listy
			cout << " podaj index:";
			cin >> index;
			cout << " podaj wartosc:";
			cin >> value;
			cout << "Wartosc dodana na poczatek listy" << endl;

			start = read_QPC(); // poczatek pomiaru 
			push_front(listhead, value);
			
			elapsed = read_QPC() - start; // koniec pomiaru 
			cout << "Czas[ms] = " << setprecision(0) << (1000.0 * elapsed) / frequency << endl;
			ListDisplay(listhead); cout << endl;
			cout << "Wartosc dodana na koniec listy" << endl;
			
			start = read_QPC(); // poczatek pomiaru 
			push_back(listtail, value);
			elapsed = read_QPC() - start; // koniec pomiaru 
			cout << "Czas[ms] = " << setprecision(0) << (1000.0 * elapsed) / frequency << endl;

			ListDisplay(listhead); cout << endl;
			cout << "Wartosc dodana w miejsce o podanym indeksie " << index << " listy" << endl;
			
			start = read_QPC(); // poczatek pomiaru 
			push_whereIndex(listhead, value, index);
			elapsed = read_QPC() - start; // koniec pomiaru 
			cout << "Czas[ms] = " << setprecision(0) << (1000.0 * elapsed) / frequency << endl;

			ListDisplay(listhead); cout << endl;
			break;

		case 4: //znajdywanie elemetu w liscie
			cout << " Podaj wartosc:";
			cin >> value;

			start = read_QPC(); // poczatek pomiaru 
			if (findValue(listhead, value))
				cout << "Podana wartosc jest w liscie" << endl;
			else
				cout << "Podanej wartosci nie ma w liscie" << endl;
			elapsed = read_QPC() - start; // koniec pomiaru 
			cout << "Czas[ms] = " << setprecision(0) << (1000.0 * elapsed) / frequency << endl;

			break;

		case 5:  // generowanie  listy
			cout << "Podaj ilosc elementow listy:";
			cin >> value;

			start = read_QPC(); // poczatek pomiaru 
			FileGenerator(value);
			elapsed = read_QPC() - start; // koniec pomiaru 
			cout << "Czas[ms] = " << setprecision(0) << (1000.0 * elapsed) / frequency << endl;

			ListDisplay(listhead);
			break;

		case 6:  // wyswietlanie listy
			
			start = read_QPC(); // poczatek pomiaru 
			ListDisplay(listhead);
			elapsed = read_QPC() - start; // koniec pomiaru 
			cout << "Czas[ms] = " << setprecision(0) << (1000.0 * elapsed) / frequency << endl;
			break;

		case 7: //eksperymenty
			break;
		}

	} while (option != 0);
}





//====================================================================================== GLOWNY PROGRAM =====================================================================


int main()
{
    QueryPerformanceFrequency((LARGE_INTEGER*)&frequency);
    int size, option1; //rozmiar struktury, numer opcji

    do
    {
        cout << "=========== MENU GLOWNE ===========\n1. Tablica\n2. Lista dwukierunkowa\n3. Kopiec binarny\n4. BST\n5. Drzewo czerwono-czarne\n6. Drzewo AVL\n7. Eksperyment\n0. Zakmnij program\nPodaj opcje:\n";

        do
        {
            cin >> option1;
            if (option1 < 0 || option1>7)
                cout << "Wybrano niewlasciwy numer opcji\n\n";

        } while (option1 < 0 || option1>7);

        switch (option1)
        {
        case 1: //Tablica
            break;

        case 2: //Lista
            ListMenu();
            break;

        case 3: //Kopiec
            break;

        case 4: //BST
            break;

        case 5: //Drzewo czerwono czarne
            break;

        case 6: //AVL
            break;

        case 7: //Eksperymenty
            break;

        case 0: // wyjscie 
            break;
        default:
            cout << "Wystapil blad,wybierz strukture jeszcze raz\n\n";
            break;
        }
    } while (option1 != 0);
    return 0;
}
