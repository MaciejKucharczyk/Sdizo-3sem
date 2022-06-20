#include <iostream>
#include <iomanip>
#include "shortway.h"

using namespace std;

Tree::Tree(int n)
{
    ArrNeighbourList = new TNode * [n];         // lista sasiedztwa
    AllNodes = new TNode*[n];
    for (int i = 0; i < n; i++) ArrNeighbourList[i] = nullptr;
    ArrSize = n - 1;                  // dlugpsctablicy
    TreeDistance = INT16_MAX;                    // waga calego drzewa
    matrix = new int* [n];          // utworzenie macierzy
    for (int i = 0; i < n; i++)
        matrix[i] = new int[n];
    // inicjalizacja macierzy zerami
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            matrix[i][j] = 0;
}

Tree::Tree()
{
    ArrSize = 0;                  // Zdlugosc tablicy
    TreeDistance = 0;                    // waga calego drzewa
}


Tree::~Tree()
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

void Tree::addDirectEdge(Edge e, int vertex_id)
{
    TNode* p;

    //TreeDistance += e.weight;            // Do wagi drzewa dodajemy wage krawedzi
    p = new TNode;                 // nowy wierzcholek
    p->v = e.v2;                   //
    p->weight = e.weight;
    p->next = ArrNeighbourList[e.v1];          // Dodajemy p do listy wierzcholka v1
    ArrNeighbourList[e.v1] = p;

    AllNodes[vertex_id] = p;
}

void Tree::addNode(int n) // uzupelnienie konstruktora bezargumentowego
{
    ArrNeighbourList = new TNode * [n];
    for (int i = 0; i < n; i++) ArrNeighbourList[i] = nullptr;
    ArrSize = n - 1;
    AllNodes = new TNode*[n];

}

void Tree::makeMatrix(int n)
{
    matrix = new int* [n];          // utworzenie macierzy
    for (int i = 0; i < n; i++)
        matrix[i] = new int[n];
    // inicjalizacja macierzy zerami
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            matrix[i][j] = 0;
}

// Zwraca wska�nik pocz�tku listy s�siad�w wierzcho�ka

TNode* Tree::getAList(int n)
{
    return ArrNeighbourList[n];
}


void Tree::print_list() // wyswietlanie mst listowo
{
    int i;
    TNode* p;

    cout << endl << "vertex     | index ->(weight) |" << endl << endl;
    for (i = 0; i <= ArrSize; i++)
    {
        cout << "Vertex " << i << " - ";
        if (ArrNeighbourList[i] != nullptr)
            for (p = ArrNeighbourList[i]; p; p = p->next) cout << p->v << "->(" << p->weight << ")  ";
        cout << endl;
    }
    cout << endl << endl << "Najkrotsza droga = " << TreeDistance << endl << endl;
}

/*void MSTree::Dijkstra_print_list() // wyswietlanie mst listowo
{
    int i;
    TNode* p;

    cout << endl << "vertex     | index ->(weight) |" << endl << endl;
    for (i = 0; i <= ArrSize; i++)
    {
        cout << "Vertex " << i << " - ";
        if (ArrNeighbourList[i] != nullptr)
            for (p = ArrNeighbourList[i]; p; p = p->next) cout << p->v << "->(" << p->weight << ")  ";
        cout << endl;
    }
    cout << endl << endl << "Waga drzewa spinajacego = " << TreeWeight << endl << endl;
}*/

void Tree::zeros_matrix(int n) // funkcja inicjalizuje macierz zerami
{
    matrix = new int* [n]; // utworzenie macierzy
    for (int i = 0; i < n; i++)
        matrix[i] = new int[n];

    for (int i = 0; i < n; i++) // inicjalizacja zerami
        for (int j = 0; j < n; j++)
            matrix[i][j] = 0;
}

void Tree::addToMatrix(int e1, int e2)
{
    matrix[e1][e2] = 1;
    //matrixMST[e2][e1] = 1;
}

void Tree::print_matrix(int vertex)
{
    cout << "   ";
    for (int i = 0; i < vertex; i++)
        cout << setw(3) << i;
    cout << endl << endl;
    for (int i = 0; i < vertex; i++)
    {
        cout << setw(3) << i;
        for (int j = 0; j < vertex; j++) cout << setw(3) << matrix[i][j];
        cout << endl;
    }
}

void Tree::addToNodeList(TNode* n, int vertex)
{
    AllNodes[vertex] = n;
}

TNode* Tree::getFromNodeList(int vertex)
{
    return AllNodes[vertex];
}


