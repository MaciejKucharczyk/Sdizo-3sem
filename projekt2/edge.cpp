#include <iostream>
#include "edge.h"

using namespace std;

Queue::Queue()
{
    h_index = 0;                      // Pozycja w kopcu
}

Queue::Queue(int n)
{
    Heap = new Edge[n];         // Tworzymy tablicê
    h_index = 0;
}

Queue::~Queue()
{
    delete[] Heap;
}

void Queue::addEdges(int n)
{
    Heap = new Edge[n];         // Tworzymy tablicê
    h_index = 0;
}


Edge Queue::front() // zwraca krawedz o najmniejsze wadze
{
    return Heap[0];
}

void Queue::push(Edge e)
{
    int i, j;

    i = h_index++;                    // i ustawiamy na koniec kopca
    j = (i - 1) >> 1;            // Obliczamy pozycjê rodzica

    // Szukamy miejsca w kopcu dla krawedzi

    while (i && (Heap[j].weight > e.weight))
    {
        Heap[i] = Heap[j];
        i = j;
        j = (i - 1) >> 1;
    }

    Heap[i] = e;                // KrawêdŸ wstawiamy do kopca
}


void Queue::pop() // usuwa korzen z kopca
{
    int i, j;
    Edge e;

    if (h_index)
    {
        e = Heap[--h_index];

        i = 0;
        j = 1;

        while (j < h_index)
        {
            if ((j + 1 < h_index) && (Heap[j + 1].weight < Heap[j].weight)) j++;
            if (e.weight <= Heap[j].weight) break;
            Heap[i] = Heap[j];
            i = j;
            j = (j << 1) + 1;
        }

        Heap[i] = e;
    }
}

