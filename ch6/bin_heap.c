#include <stdio.h>
#include <stdlib.h>
#include "bin_heap.h"

#define MinPQSize 9
#define MinData -99

int IsFull(PriorityQueue H)
{
	return H->Size == H->Capacity;
}

int IsEmpty(PriorityQueue H)
{
	return H->Size == 0;
}

PriorityQueue Initialize(int MaxElements)
{
	PriorityQueue H;

	if (MaxElements < MinPQSize)
		printf("Priority queue size is too small");

	H = malloc(sizeof(struct HeapStruct));
	if (H == NULL)
		printf("Out of space!!!");

	H->Elements = malloc((MaxElements + 1) * sizeof(ElementType));

	if (H->Elements == NULL)
		printf("Out of space!!!!");

	H->Capacity = MaxElements;
	H->Size = 0;
	H->Elements[0] = MinData;

	return H;
}

void Insert(ElementType X, PriorityQueue H)
{
	int i;

	if (IsFull(H))
	{
		Error("Priority queue is full");
		return; 
	}

	for (i = ++H->Size; H->Elements[i/2] > X; i /= 2)
		H->Elements[i] = H->Elements[i/2];
	H->Elements[i] = X;
}

ElementType DeleteMin(PriorityQueue H)
{
	int i, Child;
	ElementType MinElement, LastElement;

	if (IsEmpty(H))
	{
		printf("Priority queue is empty");
		return H->Elements[0];
	}
	MinElement = H->Elements[1];
	LastElement = H->Elements[H->Size--];

	for (i = 1; i * 2 <= H->Size; i = Child)
	{
		Child = i * 2;
		if (Child != H->Size && H->Elements[Child + 1] < H->Elements[Child])
			Child++;

		if (LastElement > H->Elements[Child])
			H->Elements[i] = H->Elements[Child];
		else
			break;
	}
	H->Elements[i] = LastElement;
	return MinElement;
}
