#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include <windows.h>
#include "Lista.cpp"

using namespace std;

long long int read_QPC() // funkcja mierzaca czas algorytmu
{
	LARGE_INTEGER count;
	QueryPerformanceCounter(&count);
	return((long long int)count.QuadPart);
}

long long int frequency, start, elapsed;

List lista = List();
ElemList* listhead;
ElemList* listtail;

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
			lista.loadFromFile(listhead, fileName);
			listtail = lista.findTail(listhead);
			lista.display(listhead);
			lista.displayBackwards(listtail);
			elapsed = read_QPC() - start; // koniec pomiaru 
			cout << "Czas[ms] = " << setprecision(0) << (1000.0 * elapsed) / frequency << endl;

			break;

		case 2: // usuwanie elemenu z listy
			cout << " Podaj wartosc:";
			cin >> value;
			start = read_QPC(); // poczatek pomiaru 
			lista.deleteFromList(listhead, listtail, value);
			elapsed = read_QPC() - start; // koniec pomiaru 
			cout << "Czas[ms] = " << setprecision(0) << (1000.0 * elapsed) / frequency << endl;

			lista.display(listhead);
			break;

		case 3: // dodawanie elemetu do listy
			cout << " podaj index:";
			cin >> index;
			cout << " podaj wartosc:";
			cin >> value;
			cout << "Wartosc dodana na poczatek listy" << endl;

			start = read_QPC(); // poczatek pomiaru 
			lista.push_front(listhead, value);
			
			elapsed = read_QPC() - start; // koniec pomiaru 
			cout << "Czas[ms] = " << setprecision(0) << (1000.0 * elapsed) / frequency << endl;
			lista.display(listhead); cout << endl;
			cout << "Wartosc dodana na koniec listy" << endl;
			
			start = read_QPC(); // poczatek pomiaru 
			lista.push_back(listtail, value);
			elapsed = read_QPC() - start; // koniec pomiaru 
			cout << "Czas[ms] = " << setprecision(0) << (1000.0 * elapsed) / frequency << endl;

			lista.display(listhead); cout << endl;
			cout << "Wartosc dodana w miejsce o podanym indeksie " << index << " listy" << endl;
			
			start = read_QPC(); // poczatek pomiaru 
			lista.push_whereIndex(listhead, value, index);
			elapsed = read_QPC() - start; // koniec pomiaru 
			cout << "Czas[ms] = " << setprecision(0) << (1000.0 * elapsed) / frequency << endl;

			lista.display(listhead); cout << endl;
			break;

		case 4: //znajdywanie elemetu w liscie
			cout << " Podaj wartosc:";
			cin >> value;

			start = read_QPC(); // poczatek pomiaru 
			if (lista.IsValueInList(listhead, value))
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

			lista.display(listhead);
			break;

		case 6:  // wyswietlanie listy
			
			start = read_QPC(); // poczatek pomiaru 
			lista.display(listhead);
			lista.displayBackwards(listtail);
			elapsed = read_QPC() - start; // koniec pomiaru 
			cout << "Czas[ms] = " << setprecision(0) << (1000.0 * elapsed) / frequency << endl;
			break;

		case 7: //eksperymenty
			cout << "Ogon listy: " << endl;
			cout << listtail << endl;
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
