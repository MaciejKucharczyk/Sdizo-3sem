#include <iostream>

#include "zbiory.h"

using namespace std;

// Konstruktory
DSStruct::DSStruct()
{

}

DSStruct::DSStruct(int n)
{
    Z = new DSNode[n];    // Tworzymy tablice dla elementow zbiorow
}

// Destruktor
//-----------
DSStruct::~DSStruct()
{
    delete[] Z;            // Usuwamy tablice ze zbiorami
}

void DSStruct::addNodes(int n)
{
    Z = new DSNode[n];    // Tworzymy tablice dla elementow zbiorow
}

// Tworzy wpis w tablicy Z
//------------------------
void DSStruct::MakeSet(int v)
{
    Z[v].up = v;
    Z[v].rank = 0;
}

// Zwraca indeks reprezentanta zbioru, w ktorym jest wierzcholek v
//----------------------------------------------------------------
int DSStruct::FindSet(int v)
{
    if (Z[v].up != v) Z[v].up = FindSet(Z[v].up);
    return Z[v].up;
}

// ��czy ze sob� zbiory z v i u
//-----------------------------
void DSStruct::UnionSets(Edge e)
{
    int ru, rv;

    ru = FindSet(e.v1);   // Wyznaczamy korzen drzewa z wezlem u
    rv = FindSet(e.v2);   // Wyznaczamy korzen drzewa z wezlem v
    if (ru != rv)           // Korzenie musza byc rozne
    {
        if (Z[ru].rank > Z[rv].rank) // Porownujemy rangi drzew
            Z[rv].up = ru;    // ru wieksze, dolaczamy rv
        else
        {
            Z[ru].up = rv;    // rowne lub rv wieksze, dolaczamy ru
            if (Z[ru].rank == Z[rv].rank) Z[rv].rank++;
        }
    }
}