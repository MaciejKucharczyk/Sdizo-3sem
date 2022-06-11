#include <iostream>
//#include "zbiory.h"
//#include "mst.h"
#include "algorithms.h"

using namespace std;

Algorithms::Algorithms()
{
    MSTree drzewo;
    MSTree graf;
    Queue kolejka;
    DSStruct zbiory;
}

Algorithms::~Algorithms()
{
	
}

void Algorithms::Random_graph_Generator(int density, int nodes)
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

void Algorithms::Prim(int n)
{
    Edge e;
	TNode* p;
	int v = 0; // rozpatrywany wierzcholek
	drzewo.addNode(vertex);
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
			cout<<"Dziala2"<<endl;
		matrixMST[e.v1][e.v2] = 1;
		matrixMST[e.v2][e.v1] = 1;
		visited[e.v2] = true;     // Oznaczamy drugi wierzchołek jako odwiedzony
		v = e.v2;
	}
	cout<<"Dziala juz prawie"<<endl;
	graf = drzewo;
}

void Algorithms::Kruskal(int n)
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

void Algorithms::Dijkstra()
{
    
}
