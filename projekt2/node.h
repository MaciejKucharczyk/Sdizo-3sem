#pragma once
#include "edge.h"

struct TNode
{
    TNode* next;
    int v, weight, distance;
};

class NodeQueue // kopiec wierzcholkow do algorytmu Dijkstra
{
private:
    TNode** Heap;
    int heap_index;
public:
    NodeQueue(int n);
    NodeQueue();
    ~NodeQueue();
    void addNodes(int n);
    TNode* front();
    void push(TNode* node);
    void pop();
    int HeapIndex();
};

