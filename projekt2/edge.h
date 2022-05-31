#pragma once

struct Edge
{
    int v1, v2, weight;            // Wierzcho³ki krawêdzi, waga krawêdzi
};

class Queue
{
private:
    Edge* Heap;
    int h_index;
public:
    Queue(int n);
    Queue();
    ~Queue();
    void addEdges(int n);
    Edge front();
    void push(Edge e);
    void pop();
};

