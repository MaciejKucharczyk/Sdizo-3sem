#include <iostream>

#include "mst.h"

using namespace std;

MSTree::MSTree(int n)
{
    int i;

    ArrNeighbourList = new TNode * [n];         // lista sasiedztwa 
    for (i = 0; i < n; i++) ArrNeighbourList[i] = NULL;
    ArrSize = n - 1;                  // d�ugo�� tablicy
    TreeWeight = 0;                    // waga calego drzewa
}

MSTree::MSTree()
{
    ArrSize = 0;                  // Zapami�tujemy d�ugo�� tablicy
    TreeWeight = 0;                    // Zerujemy wag� drzewa
}

// Destruktor - usuwa listy oraz tablic� s�siedztwa
//-------------------------------------------------
MSTree::~MSTree()
{
    int i;
    TNode* p, * r;

    if (ArrNeighbourList)
        for (i = 0; i <= ArrSize; i++)
        {
            //p = A[i];
            while (ArrNeighbourList[i])
            {
                p = ArrNeighbourList[i];
                r = p;                     // Zapami�tujemy wskazanie
                p = p->next;               // Przesuwamy si� do nast�pnego elementu listy
                delete r;                  // Usuwamy element
            }
        }

    delete[] ArrNeighbourList;                  // Usuwamy tablic� list s�siedztwa
}

// Dodaje kraw�d� do drzewa
//-------------------------
void MSTree::addEdge(Edge e)
{
    TNode* p;

    TreeWeight += e.weight;            // Do wagi drzewa dodajemy wag� kraw�dzi
    p = new TNode;                 // Tworzymy nowy w�ze�
    p->v = e.v2;                   // Wierzcho�ek ko�cowy
    p->weight = e.weight;          // Waga kraw�dzi
    p->next = ArrNeighbourList[e.v1];          // Dodajemy p do listy wierzcho�ka v1
    ArrNeighbourList[e.v1] = p;

    p = new TNode;                 // To samo dla kraw�dzi odwrotnej
    p->v = e.v1;                   // Wierzcho�ek ko�cowy
    p->weight = e.weight;          // Waga kraw�dzi
    p->next = ArrNeighbourList[e.v2];          // Dodajemy p do listy wierzcho�ka v2
    ArrNeighbourList[e.v2] = p;
}

void MSTree::addNode(int n)
{
    ArrNeighbourList = new TNode * [n];                        // Tablica list 
    for (int i = 0; i < n; i++) ArrNeighbourList[i] = NULL;     // wype�niamy pustymi listami
    ArrSize = n - 1;                                 // d�ugo�� tablicy
    TreeWeight = 0;                                 // Zerujemy wag� drzewa
}

// Zwraca wska�nik pocz�tku listy s�siad�w wierzcho�ka
//----------------------------------------------------
TNode* MSTree::getAList(int n)
{
    return ArrNeighbourList[n];
}

// Wy�wietla zawarto�� drzewa oraz jego wag�
//------------------------------------------
void MSTree::print_list()
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
