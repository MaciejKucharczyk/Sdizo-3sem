#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include <windows.h>
#include "Lista.cpp"
#include "Tablica.cpp"
#include "Kopiec.cpp"
//#include "DrzewoBST.cpp"

using namespace std;

/*long long int read_QPC() // funkcja mierzaca czas algorytmu
{
	LARGE_INTEGER count;
	QueryPerformanceCounter(&count);
	return((long long int)count.QuadPart);
}*/

//long long int frequency, start, elapsed;


List lista;
Table tablica;
//Heap kopiec;
Max_Heap kopiec;

string FileGenerator(int size) //funkcja generuje plik z liczbami (ilosc liczb jest rowna size)
{
    string file;
    srand(time(NULL));
    cout << "Wprowadz nazwe nowego pliku zrodlowego do struktury: " << endl;
    cin >> file;
    ofstream MyFile;
    MyFile.open(file);
    MyFile << size << endl;
    for (int i = 0; i < size; i++)
        MyFile << rand() % 10000000000000 - 10000 << endl;
    MyFile.close();
	return file;
}

void ListMenu()
{
	int option;
	string fileName;
	int index, value;


	do {
		lista.displayMenu();
		cin >> option;
		cout << endl;
		switch (option) {
		case 1: //wczytytwanie listy z pliku
			cout << " Podaj nazwe zbioru:";
			cin >> fileName;
			lista.loadFromFile(fileName);
			lista.display();
			lista.displayBackwards();
			break;

		case 2: // usuwanie elemenu z listy
			cout << " Podaj wartosc:";
			cin >> value; 
			// ------ POCZATKOWEGO -----------
			lista.pop_front();
			lista.display();
			// ------ KONCOWEGO -----------
			lista.pop_back();
			lista.display();
			// ---------WYBRANEGO-------------
			lista.deleteFromList(value);
			lista.display();
			break;

		case 3: // dodawanie elemetu do listy
			cout << " podaj index:";
			cin >> index;
			cout << " podaj wartosc:";
			cin >> value;
			cout << "Wartosc dodana na poczatek listy" << endl;

			lista.push_front(value);
			lista.display(); cout << endl;

			cout << "Wartosc dodana na koniec listy" << endl;
			lista.push_back(value);
			lista.display(); cout << endl;

			cout << "Wartosc dodana w miejsce o podanym indeksie " << index << " listy" << endl;
			lista.push_whereIndex(value, index);
			lista.display(); cout << endl;
			break;

		case 4: //znajdywanie elemetu w liscie
			cout << " Podaj wartosc:";
			cin >> value;
			if (lista.IsValueInList(value))
				cout << "Podana wartosc jest w liscie" << endl;
			else
				cout << "Podanej wartosci nie ma w liscie" << endl;
			break;

		case 5:  // generowanie  listy
			
			lista.~List(); // usuwanie poprzedniej listy jezeli byla 
			cout << "Podaj ilosc elementow listy:";
			cin >> value;
			lista.loadFromFile(FileGenerator(value));
			lista.display();
			break;

		case 6:  // wyswietlanie listy
			
			lista.display();
			lista.displayBackwards();
			break;

		case 7: //eksperymenty
			lista.eksperymenty();
			break;
		}

	} while (option != 0);
	lista.~List(); // usuwanie listy 
}

void TableMenu()
{
	int opt;
	string fileName;
	int index, value;


	do {
		tablica.displayMenu();
		cin >> opt;
		cout << endl;
		switch (opt) {
		case 1: //tutaj wczytytwanie  tablicy z pliku
			cout << " Podaj nazwe zbioru:";
			cin >> fileName;
			tablica.loadFromFile(fileName);
			tablica.display();
			break;

		case 2: //tutaj usuwanie elemenu z tablicy
			cout << " podaj index:";
			cout << "Usunuecie ostatmiego elementu:" << endl;
			cin >> index;
			cout << "Usunuecie ostatmiego elementu:" << endl;  
			tablica.pop_back();
			tablica.display();
			cout << "Usunuecie pierwszego elementu:" << endl;
			tablica.pop_front();
			tablica.display();
			break;

		case 3: // dodawanie elemetu do tablicy
			cout << " podaj index:";
			cin >> index;
			cout << " podaj waertość:";
			cin >> value;
			cout << "Wartosc dodana z przodu tablicy" << endl;
			tablica.push_front(value);
			tablica.display();
			cout << "Wartosc dodana na koniec tablicy" << endl;
			tablica.push_back(value);
			tablica.display();
			cout << "Wartosc dodana w miejsce o wskazanym indeksie tablicy" << endl;
			tablica.addValue(index, value);
			tablica.display();
			break;

		case 4: //tutaj znajdowanie elemetu w tablicy
			cout << " podaj waertość:";
			cin >> value;
			if (tablica.IsValueInTable(value))
				cout << "poadana wartosc jest w tablicy";
			else
				cout << "poadanej wartości NIE ma w tablicy";
			break;

		case 5:  //tutaj generowanie  tablicy		
			tablica.DeleteTable();
			cout << "Podaj ilość elementów tablicy:";
			cin >> value;
			tablica.loadFromFile(FileGenerator(value));
			tablica.display();
			break;

		case 6:  //tutaj wyświetlanie tablicy
			tablica.display();
			break;

		case 7: // funkcja do eksperymentów
			//tablica.Eksperymenty();
			break;
		}

	} while (opt != 0);
}

void HeapMenu()
{
	int opt;
	string fileName;
	int index, value;


	do {
		tablica.displayMenu();
		cin >> opt;
		cout << endl;
		switch (opt) {
		case 1: //tutaj wczytytwanie  kopca z pliku
			cout << " Podaj nazwe zbioru:";
			cin >> fileName;
			kopiec.loadFromFile(fileName);
			kopiec.print();
			break;

		case 2: //tutaj usuwanie elemenu z kopca
			cout << " podaj wartosc:";
			cin >> value;
			cout << "Usunuecie elementu:" << endl;
			//kopiec.remove(value);
			//kopiec.display();
			break;

		case 3: // dodawanie elemetu do kopca
			cout << " podaj wartosc:";
			cin >> value;
			cout << "Wartosc dodana do kopca" << endl;
			//kopiec.add(value);
			//kopiec.display();
			break;

		case 4: //tutaj znajdowanie elemetu w kopcu		
			cout << " podaj wartosc:";
			cin >> value;
			//if (kopiec.IsValueInHeap(value))
				cout << "Szukana wartosc jest w kopcu" << endl;
			//else
				cout << "Danej wartosci NIE ma w kopcu" << endl;
			break;

		case 5:  //tutaj generowanie  kopca										********************************************
			cout << "Podaj ilość elementów kopca:";
			cin >> value;
			kopiec.loadFromFile(FileGenerator(value));
			//kopiec.display();
			break;

		case 6:  //tutaj wyświetlanie kopca													
			//kopiec.display();
			break;

		case 7: // funkcja do eksperymentów
			break;
		}

	} while (opt != 0);
	//kopiec.~Kopiec();
}

/*void BSTMenu()
{
	int opt;
	string fileName;
	int index, value;



	do {
		tablica.displayMenu();
		cin >> opt;
		cout << endl;
		switch (opt) {
		case 1: //tutaj wczytytwanie drzewa z pliku           ************************************************
			cout << " Podaj nazwe zbioru:";
			cin >> fileName;
			kopiec.loadFromFile(fileName);
			kopiec.display();
			break;

		case 2: //tutaj usuwanie elemenu z drzewa           ********************************************
			cout << " podaj wartosc:";
			cin >> value;
			cout << "Usunuecie elementu:" << endl;
			kopiec.remove(value);
			kopiec.display();
			break;

		case 3: // dodawanie elemetu do drzewa				*************************************************
			cout << " podaj wartosc:";
			cin >> value;
			cout << "Wartosc dodana do kopca" << endl;
			kopiec.add(value);
			kopiec.display();
			break;

		case 4: //tutaj znajdowanie elemetu w drzewie			**********************************************	
			cout << " podaj wartosc:";
			cin >> value;
			kopiec.IsValueInHeap(value);
			break;

		case 5:  //tutaj generowanie  drzewa										********************************************
			cout << "Podaj ilość elementów kopca:";
			cin >> value;
			kopiec.loadFromFile(FileGenerator(value));
			kopiec.display();
			break;

		case 6:  //tutaj wyświetlanie drzewa								*****************************************												
			kopiec.display();
			break;

		case 7: // funkcja do eksperymentów
			break;
		}

	} while (opt != 0);
}*/









//====================================================================================== GLOWNY PROGRAM =====================================================================


int main()
{
	QueryPerformanceFrequency((LARGE_INTEGER*)&frequency); // funkcja mierzaca czas

    int size, option1; //rozmiar struktury, numer opcji

    do
    {
        cout << "=========== MENU GLOWNE ===========\n1. Tablica\n2. Lista dwukierunkowa\n3. Kopiec binarny\n4. Drzewo BST\n5. Eksperyment\n0. Zakmnij program\nPodaj opcje:\n";
        do
        {
            cin >> option1;
            if (option1 < 0 || option1>7)
                cout << "Wybrano niewlasciwy numer opcji\n\n";

        } while (option1 < 0 || option1>7);

        switch (option1)
        {
        case 1: //Tablica
			TableMenu();
            break;

        case 2: //Lista
            ListMenu();
            break;

        case 3: //Kopiec
			//HeapMenu();
            break;

        case 4: //BST
            break;

        case 5: //Eksperymenty
			FileGenerator(1000);
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
