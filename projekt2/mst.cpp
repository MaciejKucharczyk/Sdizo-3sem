#include <iostream>
#include <iomanip>

#include "mst.h"

using namespace std;

MSTree::MSTree(int n)
{
    int i;

    ArrNeighbourList = new TNode * [n];         // lista sasiedztwa 
    for (i = 0; i < n; i++) ArrNeighbourList[i] = NULL;
    ArrSize = n - 1;                  // dlugpsctablicy
    TreeWeight = 0;                    // waga calego drzewa
    matrixMST = new int* [n];          // utworzenie macierzy 
	for (int i = 0; i < n; i++)
		matrixMST[i] = new int[n];
	// inicjalizacja macierzy zerami 
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            matrixMST[i][j] = 0; 
}

MSTree::MSTree()
{
    ArrSize = 0;                  // Zdlugosc tablicy 
    TreeWeight = 0;                    // waga calego drzewa
}


MSTree::~MSTree()
{
    int i;
    TNode* p, * r;

    if (ArrNeighbourList)
    {
       for (i = 0; i <= ArrSize; i++)
        {
            //p = A[i];
            while (ArrNeighbourList[i])
            {
                p = ArrNeighbourList[i];
                r = p;                     // Zapamietujemy wskazanie
                p = p->next;             
                delete r;
            }
        }
       // delete[] ArrNeighbourList;
    }    
}


void MSTree::addEdge(Edge e)
{
    TNode* p;

    TreeWeight += e.weight;            // Do wagi drzewa dodajemy wage krawedzi
    p = new TNode;                 // nowy wierzcholek
    p->v = e.v2;                   // 
    p->weight = e.weight;         
    p->next = ArrNeighbourList[e.v1];          // Dodajemy p do listy wierzcholka v1
    ArrNeighbourList[e.v1] = p;

    p = new TNode;                 // analogicznie dla krawedzi odwrotnej
    p->v = e.v1;                   
    p->weight = e.weight;          
    p->next = ArrNeighbourList[e.v2];          
    ArrNeighbourList[e.v2] = p;
}

void MSTree::addNode(int n) // uzupelnienie konstruktora bezargumentowego
{
    ArrNeighbourList = new TNode * [n];                        
    for (int i = 0; i < n; i++) ArrNeighbourList[i] = NULL;     
    ArrSize = n - 1;                                 
    TreeWeight = 0;                               
}

void MSTree::makeMatrix(int n)
{
    matrixMST = new int* [n];          // utworzenie macierzy 
	for (int i = 0; i < n; i++)
		matrixMST[i] = new int[n];
	// inicjalizacja macierzy zerami 
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            matrixMST[i][j] = 0; 
}

// Zwraca wska�nik pocz�tku listy s�siad�w wierzcho�ka

TNode* MSTree::getAList(int n)
{
    return ArrNeighbourList[n];
}


void MSTree::print_list() // wyswietlanie mst listowo
{
    int i;
    TNode* p;

    cout << endl << "vertex     | index ->(weight) |" << endl << endl;
    for (i = 0; i <= ArrSize; i++)
    {
        cout << "Vertex " << i << " - ";
        if (ArrNeighbourList[i] != NULL)
            for (p = ArrNeighbourList[i]; p; p = p->next) cout << p->v << "->(" << p->weight << ")  ";
        cout << endl;
    }
    cout << endl << endl << "Waga drzewa spinajacego = " << TreeWeight << endl << endl;
}

void MSTree::zeros_matrix(int n) // funkcja inicjalizuje macierz zerami
{
    matrixMST = new int* [n]; // utworzenie macierzy
    for (int i = 0; i < n; i++)
        matrixMST[i] = new int[n];

    for (int i = 0; i < n; i++) // inicjalizacja zerami
        for (int j = 0; j < n; j++)
            matrixMST[i][j] = 0;
}

void MSTree::addToMatrix(int e1, int e2)
{
	matrixMST[e1][e2] = 1;
	matrixMST[e2][e1] = 1;
}

void MSTree::print_matrixMST(int vertex)
{
	cout << "   ";
	for (int i = 0; i < vertex; i++) 
		cout << setw(3) << i;
	cout << endl << endl;
	for (int i = 0; i < vertex; i++)
	{
		cout << setw(3) << i;
		for (int j = 0; j < vertex; j++) cout << setw(3) << matrixMST[i][j];
		cout << endl;
	}
}
