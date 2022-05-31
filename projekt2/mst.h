#pragma once

#include "node.h"
#include "edge.h"

class MSTree
{
private:
    TNode** ArrNeighbourList;                  // Tablica list s�siedztwa
    int ArrSize;                    // Liczba kom�rek w tablicy
    int TreeWeight;                  // Waga ca�ego drzewa
public:
    MSTree(int n);
    MSTree();
    ~MSTree();

    void addNode(int n);
    void addEdge(Edge e);
    TNode* getAList(int n);
    void print_list();
};

