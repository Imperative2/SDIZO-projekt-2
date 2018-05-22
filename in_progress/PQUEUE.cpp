#include "stdafx.h"
#include "PQUEUE.h"
#include <iostream>




// add edge to the queue and repair the heap e- edge
void PQUEUE::push(Edge e)
{
	
	heap[size] = e;
	bubbleUp(size);
	size++;

}
// pops root from the queue and repairs the heap
void PQUEUE::pop()
{
	

	if (size == 0)
	{
		return;
	}
	heap[0] = heap[size - 1];
	size--;
	bubbleDown(0);

}
// gets root of the heap
Edge PQUEUE::getFront()
{
		return heap[0];
}
//displays the heap
void PQUEUE::display()
{
	std::cout << std::endl;
	for (int i = 0; i < size; i++)
	{
		std::cout << "start :" << heap[i].v1 << " finish:" << heap[i].v2 << " weight:" << heap[i].weight << std::endl;
	}
}
// repairs the heap upward
void PQUEUE::bubbleUp(int index)
{
	if (index == 0)
		return;

	int parentIndex = (index - 1) / 2;

	if (heap[parentIndex].weight > heap[index].weight)
	{
		Edge temp = heap[parentIndex];
		heap[parentIndex] = heap[index];
		heap[index] = temp;
		bubbleUp(parentIndex);
	}
}
// repairs the heap downward
void PQUEUE::bubbleDown(int index)
{
	int length = size;
	int leftChildIndex = 2 * index + 1;
	int rightChildIndex = 2 * index + 2;

	if (leftChildIndex >= length)
		return; //index is a leaf

	int minIndex = index;

	if (heap[index].weight > heap[leftChildIndex].weight)
	{
		minIndex = leftChildIndex;
	}

	if ((rightChildIndex < length) && (heap[minIndex].weight > heap[rightChildIndex].weight))
	{
		minIndex = rightChildIndex;
	}

	if (minIndex != index)
	{
		//need to swap
		Edge temp = heap[index];
		heap[index] = heap[minIndex];
		heap[minIndex] = temp;
		bubbleDown(minIndex);
	}
}
// creates the queue with n being max size of the heap
PQUEUE::PQUEUE(int n)
{
	heap = new Edge[n];
	maxSizeHeap = n;

}
// destructor 
PQUEUE::~PQUEUE()
{
	size = 0;
	delete [] heap;
}
