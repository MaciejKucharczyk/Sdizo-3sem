#pragma once
#include "edge.h"

struct DSNode
{
    int up, rank;
};

class DSStruct
{
private:
    DSNode* Z;
public:
    DSStruct(int n);
    DSStruct();
    ~DSStruct();
    void addNodes(int n);
    void MakeSet(int v);
    int FindSet(int v);
    void UnionSets(Edge e);
};
