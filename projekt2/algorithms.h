#pragma once
#include "zbiory.h"
#include "mst.h"

class Algorithms
{
    public:
        Algorithms();
        ~Algorithms();
        
        int vertex, edges;
        MSTree drzewo;
        MSTree graf;
        Queue kolejka;
        DSStruct zbior;
        int ** matrixMST;

        void Random_graph_Generator(int density, int nodes);
        void Kruskal(int n);
        void Prim(int n);
        void Dijkstra();
};