#include <iostream>
#include <iomanip>
#include <windows.h>
//#include "Query.cpp"

using namespace std;

class Max_Heap
{
	int* tab = nullptr;
	unsigned int aloc_size = 1024;
	int size = 0;

	string cr, cl, cp;

public:
	Max_Heap();
	virtual ~Max_Heap();
	//void load_from_file(string file_name);

	void heapify();
	void heapify_up(int index);
	void heapify_down(int index);
	bool findValue(int val);

	void push(int const val);
	void pop_root();
	void remove_key(int val);

	void display();
	void display_as_table();
	void print_tree(string sp = "",string sn = "", int v = 0);
	void generate_heap(unsigned int _size = 16);
	void clear();
	void loadFromFile(string filename);
	void displayMenu();
	void eksperyment();
protected:

	int parent(int i) { return (i - 1) / 2; }
	int left(int i) { return (2 * i + 1); }
	int right(int i) { return (2 * i + 2); }


	void copy(int* from, int* to, unsigned int size);
};

Max_Heap::Max_Heap()
{
	tab = new int[aloc_size];

	// ustawiamy ³añcuchy znakowe, poniewa¿ nie wszystkie edytory pozwalaj¹
	// wstawiaæ znaki konsoli do tworzenia ramek.
	// cr = +--
	//      |

	// cl = |
	//      +--

	// cp = |
	//      |
//	cr = cl = cp = "  ";
//	cr[0] = 218; cr[1] = 196;
//	cl[0] = 192; cl[1] = 196;
//	cp[0] = 179;

	cr = cl = cp = "  ";
	cr[0] = '*';  cr[1] = '=';
	cl[0] = '+'; cl[1] = '=';
	cp[0] = '|';
}

Max_Heap::~Max_Heap()
{
	delete[] tab;
}

/*void Max_Heap::load_from_file(string file_name)
{
	//clear();
	fstream file;
	string input;
	int x, s;
	file.open(file_name, ios::in);
	if (file.good() == true)
	{
		file >> input;
		s = stoi(input);
		while (!file.eof() && s--)
		{
			file >> input;
			x = stoi(input);
			this->push(x);
		}

		//tu operacje na pliku (zapis/odczyt)
		file.close();
	}
}*/

void Max_Heap::heapify()
{

}
void Max_Heap::heapify_up(int index)
{
	int temp;
	while (index > 0)
		if (tab[index] > tab[parent(index)])
		{
			temp = tab[index];
			tab[index] = tab[parent(index)];
			tab[parent(index)] = temp;
			index = parent(index);
		}
		else return;

}
void Max_Heap::heapify_down(int index)
{
	int p = index; //parent
	int l = left(p); //lewy syn ( l+1  -- prawy syn)
	int temp = tab[p];

	while (l < size) //dopóki istnieje przynajmniej jeden syn(lewy)
	{
		if (l + 1 < size && tab[l] < tab[l + 1])//wybierz wiekszego syna, o ile istnieje
		{
			l++;
		}

		if (temp < tab[l]) //half-swap, jesli syn wiekszy od ojca
		{
			tab[p] = tab[l];
		}
		else //temp zastepuje aktualny wierzcho³ek
		{
			tab[p] = temp;
			temp = tab[l];

		}
		p = l;
		l = 2 * l + 1;
		tab[p] = temp;
	}
}

void Max_Heap::push(int val)
{
	//realokacja z dwukrotnym nadmiarem jesli zabraknie miejsca w tablicy.
	if (size >= aloc_size)
	{
		aloc_size *= 2;
		int* new_tab = new int[aloc_size];
		copy(tab, new_tab, size);
		delete[] tab;
		tab = new_tab;
	}
	int p, i;
	i = size++;

	p = (i - 1) / 2;
	while (val > tab[p] && i > 0)
	{
		tab[i] = tab[p];
		i = p;
		p = (p - 1) / 2;
	}
	tab[i] = val;
}


void Max_Heap::pop_root()
{
	if (size == 0)
		return;
	size--;

	tab[0] = tab[size];
	heapify_down(0);
}

void Max_Heap::remove_key(int val)
{
	int index = 0;
	while (index < size)
	{
		if (tab[index] == val)
		{
			size--;
			tab[index] = tab[size];
			if (tab[index] > tab[parent(index)])
				heapify_up(index);
			else
				heapify_down(index);
		}
		else index++;
	}

}


bool Max_Heap::findValue(int val)
{
	int index = 0;
	while (index < size)
	{
		if (tab[index] == val)	return true;
		index++;
	}
	return false;
}

void Max_Heap::display()
{
	cout << endl;
	print_tree();
	cout << "rozmiar: " << size << endl;
	cout << endl;
}

void Max_Heap::display_as_table()
{
	for (int i = 0; i < size; i++)
		cout << tab[i]<<" ";
	cout << endl;
}
// Procedura wypisuje drzewo
//--------------------------
//s³abo sformatowana funkcja wypisuj¹ca drzewo (pocz¹tkowo wystarczy do testowania).
//przechodzi przez drzewo in-order "od prawej";
void Max_Heap::print_tree(string sp, string sn, int v)
{
	string s;

	if (v < size)
	{
		s = sp;
		if (sn == cr)
			s[s.length() - 2] = ' ';
		print_tree(s + cp, cr, 2 * v + 2);

		s = s.substr(0, sp.length() - 2);

		cout << s << sn << tab[v] << std::endl;

		s = sp;
		if (sn == cl)
			s[s.length() - 2] = ' ';
		print_tree(s + cp, cl, 2 * v + 1);
	}
}
//pomocnicze f.
void Max_Heap::generate_heap(unsigned int _size)
{
	for (unsigned int i = 0; i < _size; i++)
		push(rand() % 10000 - 5000);
}

void Max_Heap::copy(int* from, int* to, unsigned int size)
{
	for (unsigned int i = 0; i < size; i++)
	{
		to[i] = from[i];
	}
}
void Max_Heap::clear()
{
	delete[] tab;
	aloc_size = 1024;
	tab = new int[aloc_size];
	size = 0;
}

void Max_Heap::displayMenu()
{
	cout << endl;
	cout << "----- Kopiec binarny -----" << endl;
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

void Max_Heap::loadFromFile(string filename)
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
		push(liczba);
	}
	File.close();
}

void Max_Heap::eksperyment()
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
		//test_val = rand() % 1000 - 500;
		test_idx = rand() %100000;

//		start = read_QPC(); // poczatek pomiaru 
//		findValue(test_idx);
//		elapsed = read_QPC() - start; // koniec pomiaru
//		avgTime1 += (1000000.0 * elapsed) / frequency;

		/*start = read_QPC(); // poczatek pomiaru 
		remove_key(test_val);
		elapsed = read_QPC() - start; // koniec pomiaru
		avgTime2 += (1000000.0 * elapsed) / frequency;*/
	}
	avgTime1 = avgTime1 / 2000;
//	avgTime2 = avgTime2 / 2000;
	cout << "Sredni czas dodawania elementu [us]: " << avgTime1 << endl;
//	cout << "Sredni czas usuwania  elementu [us]: " << avgTime2 << endl;

}

