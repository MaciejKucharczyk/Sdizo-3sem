#pragma once
#include "mst.h"
#include "edge.h"
#include "zbiory.h"
#include "shortway.h"

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
        Tree grafDirect;
        Queue kolejka;
        //NodeQueue kolejkaP;
        DSStruct zbior(int n);
        int ** matrixMST;
        //DSNode *Z;

        void Random_graph_Generator(int density, int nodes);
        void Random_Directgraph_Generator(int density, int nodes);
        void Kruskal(int n);
        void Prim(int n);
        void Dijkstra_and_print(int n, int start);
        void Dijkstra(int n, int start);
};
