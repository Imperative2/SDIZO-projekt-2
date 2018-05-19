#include "stdafx.h"
#include "PQUEUE.h"
#include <iostream>





void PQUEUE::push(Edge e)
{
	int i, j;

	i = hpos++;                     
	j = (i - 1) >> 1;               

	while (i && (heap[j].weight > e.weight))
	{
		heap[i] = heap[j];
		i = j;
		j = (i - 1) >> 1;
	}

	heap[i] = e;

}

void PQUEUE::pop()
{
	int i, j;
	Edge e;

	if (hpos)
	{
		e = heap[--hpos];

		i = 0;
		j = 1;

		while (j < hpos)
		{
			if ((j + 1 < hpos) && (heap[j + 1].weight < heap[j].weight)) j++;
			if (e.weight <= heap[j].weight) break;
			heap[i] = heap[j];
			i = j;
			j = (j << 1) + 1;
		}

		heap[i] = e;
	}
}

Edge PQUEUE::getFront()
{
		return heap[0];
}

PQUEUE::PQUEUE(int n)
{
	heap = new Edge[n];
	size = n;
	hpos = 0;
}

PQUEUE::~PQUEUE()
{
	size = 0;
	delete heap;
}
