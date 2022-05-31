#pragma once

#include "node.h"
#include "edge.h"

class MSTree
{
private:
    TNode** ArrNeighbourList;                  // Tablica list s¹siedztwa
    int ArrSize;                    // Liczba komórek w tablicy
    int TreeWeight;                  // Waga ca³ego drzewa
public:
    MSTree(int n);
    MSTree();
    ~MSTree();

    void addNode(int n);
    void addEdge(Edge e);
    TNode* getAList(int n);
    void print_list();
};

