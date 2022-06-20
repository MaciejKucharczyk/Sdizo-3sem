#include <iostream>
//#include "zbiory.h"
//#include "mst.h"
#include "algorithms.h"

using namespace std;

Algorithms::Algorithms()
{
    //MSTree drzewoPrim;
    //MSTree graf;
    //Queue kolejka;
    //DSStruct zbior;
}

Algorithms::~Algorithms()
{
	
}

void Algorithms::Random_graph_Generator(int density, int nodes)
{
	srand(time(NULL));

	Edge e;
	TNode* p;

	//int max_edges = nodes ^ 2;
    int max_edges = ((nodes*(nodes-1))/2);
	int min_edges = nodes - 1;
	int edges = max_edges * density / 100;
    edges = edges + min_edges;
	int v1 = 0, v2, weight;
	if (density == 99)
		edges = max_edges - 1;

    graf.addNode(nodes);
    graf.zeros_matrix(nodes);
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
        // dodajemy krawedz do listy i macierzy
		graf.addEdge(e);
        graf.addToMatrix(e.v1, e.v2);

		// dodajemy krawedz do tablicy krawedzi istniejacych
		visited2d[v1][v1] = true;
		visited2d[v2][v2] = true;
		visited2d[v1][v2] = true;
		visited2d[v2][v1] = true;
		v1++;
	}

    int k = nodes-1;
	if (min_edges < edges)

		for (int i = min_edges; i < edges; i++) // dodajemy brakujace krawedzie
		{
            int j;
            int nodesLeft = k;
            do
			{
				if(nodesLeft==0)
                {
                    k--;
                    nodesLeft=k;
                }
                j = rand() % min_edges;
                nodesLeft--;
			} while (visited2d[k][j]); // losuj wierzcholek, dopoki krawedz o danych dwoch wierzcholkach nie isntieje

			e.v1 = k;
			e.v2 = j;
			e.weight = rand() % 20;
			graf.addEdge(e);
            graf.addToMatrix(e.v1, e.v2);
            visited2d[k][j]= true;
            visited2d[j][k]= true; // oznaczamy krawedzie, ktore istnieja jako true
            if(k == 0) // na wypadek, gdyby k uroslo za duze (seg fault)
                break;
		}
    //visited2d = nullptr;
}

void Algorithms::Prim(int n)
{
    Edge e;
	TNode* p;
    //***********
    kolejka.addEdges(n);
	int v = 0; // rozpatrywany wierzcholek
	drzewoPrim.addNode(n);
	bool* visited = new bool[n];

	drzewoPrim.zeros_matrix(n);

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
		} while (visited[e.v2]); // Krawędź prowadzi poza drzewoPrim?

		drzewoPrim.addEdge(e);             // Dodajemy krawędź do drzewa rozpinającego
        drzewoPrim.addToMatrix(e.v1, e.v2);
		visited[e.v2] = true;     // Oznaczamy drugi wierzchołek jako odwiedzony
		v = e.v2;
	}
	graf = drzewoPrim;
}

void Algorithms::Kruskal(int n)
{
    DSStruct zbior(n);
    Edge e;
	for (int i = 0; i < n; i++)
		zbior.MakeSet(i);       // Dla każdego wierzchołka tworzymy osobny zbiór
	/*for (int i = 0; i < n; i++)
	{
		cin >> e.v1 >> e.v2 >> e.weight; // Odczytujemy kolejne krawędzie grafu
        cout<<"czy zadziala? "<<endl;
		kolejka.push(e);          // i umieszczamy je w kolejce priorytetowej
        cout<<"TAK!"<<endl;
	}*/
    drzewoPrim.addNode(n);
    drzewoPrim.zeros_matrix(n);

	for (int i = 1; i < n; i++) // Pętla wykonuje się n - 1 razy !!!
	{
		do
		{
			e = kolejka.front();      // Pobieramy z kolejki krawędź
			kolejka.pop();            // Krawędź usuwamy z kolejki
		} while (zbior.FindSet(e.v1) == zbior.FindSet(e.v2));
		drzewoPrim.addEdge(e);       // Dodajemy krawędź do drzewa
        drzewoPrim.addToMatrix(e.v1, e.v2);
		zbior.UnionSets(e);     // Zbiory z wierzchołkami łączymy ze sobą
	}
	graf = drzewoPrim;
}


void Algorithms::Dijkstra_and_print(int n, int start)
{
    int *S = new int [ n ];          // Stos
    int sptr = 0;                   // Wskaźnik stosu


    TNode* p = new TNode;
    int d[n]; // droga od w. startowego do wierzcholka v
    int prev[n]; // poprzednik wierzcholka v
    for (int i=0; i<n; i++)
    {
        d[i]=INT16_MAX;
        prev[i]= -1;
    }
    d[start]=0; // odleglosc wierzcholka startowego
    NodeQueue kolejkaP(n); // kolejka priorytetowa wierzcholkow
    for (int i=0; i<n; i++) // dodajemy wierzcholki do kolejki
    {
        p=grafDirect.getFromNodeList(i);
        /*if (ArrNeighbourList[i] != nullptr)
            for (p = ArrNeighbourList[i]; p; p = p->next) cout << p->v << "->(" << p->weight << ")  ";*/
        p->distance=d[p->v];
        kolejkaP.push(p);
    }
    while(kolejkaP.HeapIndex()>0)
    {
        TNode* tab; // tablica list sasiedztwa dla danego wierzcholka
        TNode* nn; // badany wierzcholek
        nn = kolejkaP.front();
        kolejkaP.pop();
       // tab = graf.getAList(nn->v);
       for(tab = grafDirect.getAList(nn->v); tab; tab = tab -> next)
       {
           if(d[tab->v] > d[nn->v] + tab->weight)
           {
               d[tab->v] = d[nn->v] + tab->weight;
               prev[tab->v] = nn->v;
           }
       }
    }

    // WYSWIETLANIE
    for(int i = 0; i < n; i++ )
    {
        cout << i << ": ";

        // Ścieżkę przechodzimy od końca ku początkowi,
        // Zapisując na stosie kolejne wierzchołki

        for(int  j = i; j > -1; j = prev [ j ] ) S [ sptr++ ] = j;

        // Wyświetlamy ścieżkę, pobierając wierzchołki ze stosu

        while( sptr ) cout << S [ --sptr ] << " ";

        // Na końcu ścieżki wypisujemy jej koszt

        cout << "$" << d [ i ] << endl;
    }
}

void Algorithms::Dijkstra(int n, int start)
{
    int *S = new int[n];          // Stos
    int sptr = 0;                   // Wskaźnik stosu


    TNode *p = new TNode;
    int d[n]; // droga od w. startowego do wierzcholka v
    int prev[n]; // poprzednik wierzcholka v
    for (int i = 0; i < n; i++) {
        d[i] = INT16_MAX;
        prev[i] = -1;
    }
    d[start] = 0; // odleglosc wierzcholka startowego
    NodeQueue kolejkaP(n); // kolejka priorytetowa wierzcholkow
    for (int i = 0; i < n; i++) // dodajemy wierzcholki do kolejki
    {
        p = grafDirect.getFromNodeList(i);
        /*if (ArrNeighbourList[i] != nullptr)
            for (p = ArrNeighbourList[i]; p; p = p->next) cout << p->v << "->(" << p->weight << ")  ";*/
        p->distance = d[p->v];
        kolejkaP.push(p);
    }
    while (kolejkaP.HeapIndex() > 0) {
        TNode *tab; // tablica list sasiedztwa dla danego wierzcholka
        TNode *nn; // badany wierzcholek
        nn = kolejkaP.front();
        kolejkaP.pop();
        // tab = graf.getAList(nn->v);
        for (tab = grafDirect.getAList(nn->v); tab; tab = tab->next) {
            if (d[tab->v] > d[nn->v] + tab->weight) {
                d[tab->v] = d[nn->v] + tab->weight;
                prev[tab->v] = nn->v;
            }
        }
    }
}

