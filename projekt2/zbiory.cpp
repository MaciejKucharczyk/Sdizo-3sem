#include <iostream>

#include "zbiory.h"

using namespace std;

// Konstruktory
DSStruct::DSStruct()
{

}

DSStruct::DSStruct(int n)
{
    Z = new DSNode[n];    // Tworzymy tablicê dla elementów zbiorów
}

// Destruktor
//-----------
DSStruct::~DSStruct()
{
    delete[] Z;            // Usuwamy tablicê ze zbiorami
}

void DSStruct::addNodes(int n)
{
    Z = new DSNode[n];    // Tworzymy tablicê dla elementów zbiorów
}

// Tworzy wpis w tablicy Z
//------------------------
void DSStruct::MakeSet(int v)
{
    Z[v].up = v;
    Z[v].rank = 0;
}

// Zwraca indeks reprezentanta zbioru, w którym jest wierzcho³ek v
//----------------------------------------------------------------
int DSStruct::FindSet(int v)
{
    if (Z[v].up != v) Z[v].up = FindSet(Z[v].up);
    return Z[v].up;
}

// £¹czy ze sob¹ zbiory z v i u
//-----------------------------
void DSStruct::UnionSets(Edge e)
{
    int ru, rv;

    ru = FindSet(e.v1);   // Wyznaczamy korzeñ drzewa z wêz³em u
    rv = FindSet(e.v2);   // Wyznaczamy korzeñ drzewa z wêz³em v
    if (ru != rv)           // Korzenie musz¹ byæ ró¿ne
    {
        if (Z[ru].rank > Z[rv].rank) // Porównujemy rangi drzew
            Z[rv].up = ru;    // ru wiêksze, do³¹czamy rv
        else
        {
            Z[ru].up = rv;    // równe lub rv wiêksze, do³¹czamy ru
            if (Z[ru].rank == Z[rv].rank) Z[rv].rank++;
        }
    }
}