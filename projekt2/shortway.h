#pragma once

#ifndef PROJEKT2_SHORTWAY_H
#define PROJEKT2_SHORTWAY_H

#endif //PROJEKT2_SHORTWAY_H

#pragma once

#include "node.h"
#include "edge.h"

class Tree
{
private:
    TNode** ArrNeighbourList; // Tablica list sasiedztwa
    TNode** AllNodes;        // Tablica wszystkich wierzcholkow
    int ArrSize;                    // Liczba komorek w tablicy
    int TreeDistance;                  // Waga calego drzewa
public:
    int **matrix;                // macierz sasiedztwa
    Tree(int n);
    Tree();
    ~Tree();

    void addNode(int n);
    void makeMatrix(int n);
    void addDirectEdge(Edge e, int vertex_id);
    TNode* getAList(int n);
    void zeros_matrix(int n);
    void addToMatrix(int e1, int e2);
    void print_matrix(int vertex);
    void print_list();
    void Dijkstra_print_list();
    void addToNodeList(TNode* n, int vertex);
    TNode* getFromNodeList(int vertex);
};


