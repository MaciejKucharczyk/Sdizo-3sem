#include <iostream>

#include "mst.h"

using namespace std;

MSTree::MSTree(int n)
{
    int i;

    ArrNeighbourList = new TNode * [n];         // lista sasiedztwa 
    for (i = 0; i < n; i++) ArrNeighbourList[i] = NULL;
    ArrSize = n - 1;                  // d³ugoœæ tablicy
    TreeWeight = 0;                    // waga calego drzewa
}

MSTree::MSTree()
{
    ArrSize = 0;                  // Zapamiêtujemy d³ugoœæ tablicy
    TreeWeight = 0;                    // Zerujemy wagê drzewa
}

// Destruktor - usuwa listy oraz tablicê s¹siedztwa
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
                r = p;                     // Zapamiêtujemy wskazanie
                p = p->next;               // Przesuwamy siê do nastêpnego elementu listy
                delete r;                  // Usuwamy element
            }
        }

    delete[] ArrNeighbourList;                  // Usuwamy tablicê list s¹siedztwa
}

// Dodaje krawêdŸ do drzewa
//-------------------------
void MSTree::addEdge(Edge e)
{
    TNode* p;

    TreeWeight += e.weight;            // Do wagi drzewa dodajemy wagê krawêdzi
    p = new TNode;                 // Tworzymy nowy wêze³
    p->v = e.v2;                   // Wierzcho³ek koñcowy
    p->weight = e.weight;          // Waga krawêdzi
    p->next = ArrNeighbourList[e.v1];          // Dodajemy p do listy wierzcho³ka v1
    ArrNeighbourList[e.v1] = p;

    p = new TNode;                 // To samo dla krawêdzi odwrotnej
    p->v = e.v1;                   // Wierzcho³ek koñcowy
    p->weight = e.weight;          // Waga krawêdzi
    p->next = ArrNeighbourList[e.v2];          // Dodajemy p do listy wierzcho³ka v2
    ArrNeighbourList[e.v2] = p;
}

void MSTree::addNode(int n)
{
    ArrNeighbourList = new TNode * [n];                        // Tablica list 
    for (int i = 0; i < n; i++) ArrNeighbourList[i] = NULL;     // wype³niamy pustymi listami
    ArrSize = n - 1;                                 // d³ugoœæ tablicy
    TreeWeight = 0;                                 // Zerujemy wagê drzewa
}

// Zwraca wskaŸnik pocz¹tku listy s¹siadów wierzcho³ka
//----------------------------------------------------
TNode* MSTree::getAList(int n)
{
    return ArrNeighbourList[n];
}

// Wyœwietla zawartoœæ drzewa oraz jego wagê
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
