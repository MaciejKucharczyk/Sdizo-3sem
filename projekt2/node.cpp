#include <iostream>
#include "node.h"

NodeQueue::NodeQueue()
{
    heap_index = 0;                      // Pozycja w kopcu
}

NodeQueue::NodeQueue(int n)
{
    Heap = new TNode*[n];         // Tworzymy tablice
    heap_index = 0;
}

NodeQueue::~NodeQueue()
{
    delete[] Heap;
}

void NodeQueue::addNodes(int n)
{
    Heap = new TNode*[n];         // Tworzymy tablice
    heap_index = 0;
}


TNode* NodeQueue::front() // zwraca krawedz o najmniejsze wadze
{
    return Heap[0];
}

void NodeQueue::push(TNode* node)
{
    int i, j;

    i = heap_index++;                    // i ustawiamy na koniec kopca
    j = (i - 1) >> 1;            // Obliczamy pozycje rodzica

    // Szukamy miejsca w kopcu dla wierzcholka

    while (i && (Heap[j]->distance > node->distance))
    {
        Heap[i] = Heap[j];
        i = j;
        j = (i - 1) >> 1;
    }

    Heap[i] = node;                // Kraw�d� wstawiamy do kopca
}


void NodeQueue::pop() // usuwa korzen z kopca
{
    int i, j;
    TNode* node;

    if (heap_index)
    {
        node = Heap[--heap_index];

        i = 0;
        j = 1;

        while (j < heap_index)
        {
            if ((j + 1 < heap_index) && (Heap[j + 1]->distance < Heap[j]->distance)) j++;
            if (node->distance <= Heap[j]->distance) break;
            Heap[i] = Heap[j];
            i = j;
            j = (j << 1) + 1;
        }

        Heap[i] = node;
    }
}

int NodeQueue::HeapIndex()
{
    return heap_index;
}
