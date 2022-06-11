#pragma once

#include "node.h"
#include "edge.h"

class MSTree
{
private:
    TNode** ArrNeighbourList;                  // Tablica list sasiedztwa
    int ArrSize;                    // Liczba komorek w tablicy
    int TreeWeight;                  // Waga calego drzewa
    int **matrixMST;                // macierz sasiedztwa
public:
    MSTree(int n);
    MSTree();
    ~MSTree();

    void addNode(int n);
    void makeMatrix(int n);
    void addEdge(Edge e);
    TNode* getAList(int n);
    void zeros_matrix(int n);
    void addToMatrix(int e1, int e2);
    void print_matrixMST(int vertex);
    void print_list();
};

