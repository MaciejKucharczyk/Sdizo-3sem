#include <iostream>
#include <fstream>
#include <time.h>
#include <stdlib.h>
#include <iomanip>
#include <windows.h>
#include <chrono>
#include <thread>

#include "zbiory.h"
#include "mst.h"

using namespace std;

int edges, vertex;
string filename;
bool type;
int** matrixMST; // macierz sasiedztwa

MSTree drzewo; // drzewo MST
Queue kolejka; // kolejka priorytetowa
MSTree graf; // caly graf z pliku
DSStruct zbior;

long long int read_QPC() // funkcja mierzaca czas algorytmu
{
	LARGE_INTEGER count;
	QueryPerformanceCounter(&count);
	return((long long int)count.QuadPart);
}

long long int frequency, start, elapsed;

void Kruskal(int n)
{
	Edge e;
	for (int i = 0; i < n; i++)
		zbior.MakeSet(i);       // Dla każdego wierzchołka tworzymy osobny zbiór
	for (int i = 0; i < n; i++)
	{
		cin >> e.v1 >> e.v2 >> e.weight; // Odczytujemy kolejne krawędzie grafu
		kolejka.push(e);          // i umieszczamy je w kolejce priorytetowej
	}

	for (int i = 1; i < n; i++) // Pętla wykonuje się n - 1 razy !!!
	{
		do
		{
			e = kolejka.front();      // Pobieramy z kolejki krawędź
			kolejka.pop();            // Krawędź usuwamy z kolejki
		} while (zbior.FindSet(e.v1) == zbior.FindSet(e.v2));
		drzewo.addEdge(e);       // Dodajemy krawędź do drzewa
		zbior.UnionSets(e);     // Zbiory z wierzchołkami łączymy ze sobą
	}
	graf = drzewo;
}

void Prim(int n)
{
	Edge e;
	TNode* p;
	int v = 0; // rozpatrywany wierzcholek
	bool* visited = new bool[n];

	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
			matrixMST[i][j] = 0;

	for (int i = 0; i < n; i++)
		visited[i] = false;       // Inicjujemy tablicę odwiedzin

	visited[v] = true;

	for (int i = 1; i < n; i++)       // Do drzewa dodamy n - 1 krawędzi grafu
	{
		for (p = graf.getAList(v); p; p = p->next) // Przeglądamy listę sąsiadów
			if (!visited[p->v])    // Jeśli sąsiad jest nieodwiedzony, 
			{
				e.v1 = v;                // to tworzymy krawędź
				e.v2 = p->v;
				e.weight = p->weight;
				kolejka.push(e);            // Dodajemy ją do kolejki priorytetowej
			}

		do
		{
			e = kolejka.front();            // Pobieramy krawędź z kolejki
			kolejka.pop();
		} while (visited[e.v2]); // Krawędź prowadzi poza drzewo?

		drzewo.addEdge(e);             // Dodajemy krawędź do drzewa rozpinającego
		matrixMST[e.v1][e.v2] = 1;
		matrixMST[e.v2][e.v1] = 1;
		visited[e.v2] = true;     // Oznaczamy drugi wierzchołek jako odwiedzony
		v = e.v2;
	}
	graf = drzewo;
}

void ReadFromFile(string filename /*bool type*/)
{
	fstream file;
	file.open(filename);

	if (file.good() == true)
	{
		Edge e;
		TNode* p;

		file >> edges >> vertex;

		// ***************************
		//drzewo.addNode(vertex);
		kolejka.addEdges(edges);           // Kolejka priorytetowa oparta na kopcu
		graf.addNode(vertex);               // Graf
		// ***************************
		matrixMST = new int* [vertex]; // utworzenie macierzy 
		for (int i = 0; i < vertex; i++)
			matrixMST[i] = new int[vertex];
		// inicjalizacja macierzy zerami 
		for (int i = 0; i < vertex; i++)
			for (int j = 0; j < vertex; j++)
				matrixMST[i][j] = 0;

		for (int i = 0; i < edges; i++)
		{

			file >> e.v1 >> e.v2 >> e.weight; // Odczytujemy kolejne krawędzie grafu
			graf.addEdge(e);
			matrixMST[e.v1][e.v2] = 1;
			matrixMST[e.v2][e.v1] = 1;
		}

		file.close();
	}
	else cout << "Error opening file!!!" << endl;
}

void Random_graph_Generator(int density, int nodes)
{
	srand(time(NULL));

	Edge e;
	TNode* p;

	matrixMST = new int* [nodes]; // utworzenie macierzy 
	for (int i = 0; i < nodes; i++)
		matrixMST[i] = new int[nodes];
	// inicjalizacja macierzy zerami 
	for (int i = 0; i < nodes; i++)
		for (int j = 0; j < nodes; j++)
			matrixMST[i][j] = 0;

	int max_edges = nodes ^ 2;
	int min_edges = nodes - 1;
	int edges = max_edges * density / 100;
	int v1 = 0, v2, weight;

	if (density == 99)
		edges = max_edges - 1;

	graf.addNode(nodes);
	kolejka.addEdges(edges);

	bool* visited = new bool[nodes];
	bool** visited2d = new bool* [nodes]; // tablica dwuwymiarowa zawierajaca informacje o tym,
										 // czy krawedz pomiedzy dwoma danymi wierzcholkami istnieje  
	for (int i = 0; i < nodes; ++i)
		visited2d[i] = new bool[nodes];

	for (int i = 0; i < nodes; i++)
		for (int j = 0; j < nodes; j++)
			visited2d[i][j] = false;   // na razie zadna krawedz nie istnieje, wiec wszystkie sa jako 'false'

	for (int i = 0; i < nodes; i++)
		visited[i] = false;       // na razie zadna krawedz nie zostala odwiedzona, wiec sa jako 'false'

	for (int i = 0; i < min_edges; i++) // na poczatek generujemy mst
	{
		// pierwszy wierzcholek krawedzi w pierwszej iteracji
		// ma wartosc 0 i zwieksza sie o 1 z kazda iteracja
		visited[v1] = true;
		e.v1 = v1;
		do
		{
			v2 = rand() % nodes; // losowanie koncowego wierzcholka
		} while (visited[v2]);
		e.v2 = v2;
		weight = rand() & 20; // losujemy wage dla krawedzi
		e.weight = weight;
		graf.addEdge(e);
		matrixMST[e.v1][e.v2] = 1;
		matrixMST[e.v2][e.v1] = 1;
		// dodajemy krawedz do tablicy krawedzi istniejacych
		visited2d[v1][v1] = true;
		visited2d[v2][v2] = true;
		visited2d[v1][v2] = true;
		visited2d[v2][v1] = true;
		v1++;
	}

	if (min_edges < edges)

		for (int i = min_edges; i <= edges; i++) // dodajemy brakujace krawedzie 
		{
			int k;
			int j = 0;
			do
			{
				k = rand() % min_edges;
			} while (visited2d[j][k]); // losuj wierzcholek, dopoki krawedz o danych dwoch wierzcholkach nie isntieje

			e.v1 = j;
			e.v2 = k;
			e.weight = rand() % 20;
			graf.addEdge(e);
		}
}

void print_matrixMST(int vertex)
{
	cout << "   ";
	for (int i = 0; i < vertex; i++) cout << setw(3) << i;
	cout << endl << endl;
	for (int i = 0; i < vertex; i++)
	{
		cout << setw(3) << i;
		for (int j = 0; j < vertex; j++) cout << setw(3) << matrixMST[i][j];
		cout << endl;
	}
}

void mst_menu()
{
	int density, nodes;
	int opt = 0;
	type = false;

	do
	{
		cout << "===== MENU =====" << endl;
		cout << "1. Wczytaj z pliku" << endl;
		cout << "2. Wygeneruj graf losowo" << endl;
		cout << "3. Wyswietl listowo i macierzowo" << endl;
		cout << "4. Algorytm Prima " << endl;
		cout << "5. Algorytm Kruskala " << endl;
		cout << "6. Pomiary " << endl;
		cout << "0. Cofnij do menu " << endl;

		cin >> opt;
		switch (opt)
		{
		case 1:
			// wczytywanie grafu z pliku
			cout << "Wprowadz nazwe zbioru: " << endl;
			cin >> filename;
			ReadFromFile(filename);
			break;

		case 2: // generowanie losowego grafu
			cout << "Wprowadz gestosc grafu w procentach:" << endl;
			cin >> density;
			cout << "Wprowadz ilosc wierzcholkow grafu:" << endl;
			cin >> nodes;
			Random_graph_Generator(density, nodes);
			break;

		case 3: // wyswietlanie listowo i macierzowo
			cout << "Wyswietlenie listowo:" << endl;
			graf.print_list();
			cout << endl << "Wyswietlanie macierzowo: " << endl;
			print_matrixMST(vertex);
			break;

		case 4: //algorytm Prima 
			cout << "Algorytm Prima:" << endl;
			Prim(vertex);
			break;

		case 5: //algorytm Kruskala
			cout << "Algorytm Kruskala:" << endl;
			Kruskal(vertex);
			break;

		case 6: //pomiary
			float avg1 = 0, avg2 = 0, avg3 = 0;
			cout << "Pomiary:" << endl;
			int d = 20;
			int nn = 10000;

			for (int i = 0; i < 50; i++)
			{
				Random_graph_Generator(d, nn);
				//start = read_QPC(); // poczatek pomiaru
				auto t1 = std::chrono::high_resolution_clock::now(); // czas start
				Prim(vertex);
				//elapsed = read_QPC() - start; // koniec pomiaru
				auto t2 = std::chrono::high_resolution_clock::now();
				avg1 += std::chrono::duration_cast<std::chrono::microseconds>(t2 - t1).count();
			}
			avg1 = avg1 / 50;
			cout << d << " " << nn << endl << "Sredni czas Prim [us]: " << avg1 << endl;

			d = 60;
			avg1 = 0;
			for (int i = 0; i < 50; i++)
			{
				Random_graph_Generator(d, nn);
				//start = read_QPC(); // poczatek pomiaru
				auto t1 = std::chrono::high_resolution_clock::now(); // czas start
				Prim(vertex);
				//elapsed = read_QPC() - start; // koniec pomiaru
				auto t2 = std::chrono::high_resolution_clock::now();
				avg1 += std::chrono::duration_cast<std::chrono::microseconds>(t2 - t1).count();
			}
			avg1 = avg1 / 50;
			cout << d << " " << nn << endl << "Sredni czas Prim [us]: " << avg1 << endl;

			d = 99;
			avg1 = 0;
			for (int i = 0; i < 50; i++)
			{
				Random_graph_Generator(d, nn);
				//start = read_QPC(); // poczatek pomiaru
				auto t1 = std::chrono::high_resolution_clock::now(); // czas start
				Prim(vertex);
				//elapsed = read_QPC() - start; // koniec pomiaru
				auto t2 = std::chrono::high_resolution_clock::now();
				avg1 += std::chrono::duration_cast<std::chrono::microseconds>(t2 - t1).count();
			}
			avg1 = avg1 / 50;
			cout << d << " " << nn << endl << "Sredni czas Prim [us]: " << avg1 << endl;

			break;
		}

	} while (opt != 0);
}

void shortest_way_menu()
{
	int opt = 0;

	cout << "===== MENU =====" << endl;
	cout << "1. Wczytaj z pliku" << endl;
	cout << "2. Wygeneruj graf losowo" << endl;
	cout << "3. Wyswietl listowo i macierzowo" << endl;
	cout << "4. Algorytm Dijkstry " << endl;
	cout << "5. Algorytm Forda-Bellmana " << endl;
	cout << "0. Cofnij do menu " << endl;

	do
	{
		switch (opt)
		{
		case 1:
			break;

		case 2:
			break;

		case 3:
			break;

		case 4:
			break;

		case 5:
			break;
		}

	} while (opt != 0);
}

void menu()
{
	int option = 0;

	do
	{
		cout << "===== MENU =====" << endl;
		cout << "1. Wyznaczanie minimalnego drzewa rozpinajacego (MST)" << endl;
		cout << "2. Wyznaczanie najkrotszej sciezki w grafie" << endl;
		cout << "0. Wyjscie  " << endl;

		cin >> option;

		switch (option)
		{
		case 1:
			mst_menu();
			break;

		case 2:
			shortest_way_menu();
			break;
		}

	} while (option != 0);
}


int main()
{
	menu();
	return 0;
}


