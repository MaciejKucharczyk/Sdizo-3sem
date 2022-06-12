#pragma once
#include "mst.h"
#include "edge.h"
#include "zbiory.h"

/*struct DSNode
{
    int up, rank;
};*/

class Algorithms
{
    public:
        Algorithms();
        ~Algorithms();
        
        int vertex, edges;
        MSTree drzewoPrim;
        MSTree drzewoKruskal;
        MSTree graf;
        Queue kolejka;
        DSStruct zbior(int n);
        int ** matrixMST;
        //DSNode *Z;

        void Random_graph_Generator(int density, int nodes);
        void Kruskal(int n);
        void Prim(int n);
        void Dijkstra();
};