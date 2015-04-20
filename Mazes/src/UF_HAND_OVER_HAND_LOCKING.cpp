#include "../include/UF_HAND_OVER_HAND_LOCKING.h"
#include <stdlib.h>

// -- Constructor.
UF_HAND_OVER_HAND_LOCKING::UF_HAND_OVER_HAND_LOCKING(int size) : UF_ADT(size)
{
    locks = (std::mutex *)malloc(sizeof(std::mutex) * size);
}


UF_HAND_OVER_HAND_LOCKING::~UF_ADT()
{
    free(locks);

    // CPP should automatically call the superclass destructor.
}

bool UF_HAND_OVER_HAND_LOCKING::connected(int v1, int v2)
{
    return op_find(v1) == op_find(v2);
}

void UF_HAND_OVER_HAND_LOCKING::op_union(int v1, int v2)
{
    link(op_find(v1), op_find(v2));
}

// An entire path of locks is taken, because any other finders will have
// to wait for the first one to do path compression anyways.
int UF_HAND_OVER_HAND_LOCKING::op_find(int vertex_initial)
{
    // 1st transversal, find the root.

    int vertex = vertex_initial;

    lock(vertex);
    int parent = parents[vertex];

    while(parent != vertex)
    {
        vertex = parent;
        lock(vertex);
        parent = parents[vertex];
    }

    int root = vertex;


    // Second transversal, path compression.

    vertex = vertex_initial;
    parent = parents[vertex];

    while(parent != vertex)
    {
        parents[vertex] = root;
        unlock(vertex);
        vertex = parent;
        parent = parents[vertex];
    }

    unlock(vertex);

    return root;
}

// Union by Rank.
void UF_HAND_OVER_HAND_LOCKING::link(int v1, int v2)
{
    // Very important.
    if(v1 == v2)
	{
		return;
	}

    lock(v1);
    lock(v2);
	int rank1 = ranks[v1];
	int rank2 = ranks[v2];

    // DANGER : Do not add any return statements to the below clauses.

	// v1 Greater depth.
	if(rank1 > rank2)
	{
		parents[v2] = v1;
	}

	// v2 Greater depth.
	else if(rank2 > rank1)
	{
		parents[v1] = v2;
	}

	// Equal depth --> increase rank.
	else
	{
	    parents[v2] = v1;
        ranks[v1] = rank1 + 1;
	}

    // DANGER : Do not add any return statements to the above clauses.


    unlock(v1);
    unlock(v2);
	return;
}


// Lock management code.

void UF_HAND_OVER_HAND_LOCKING::lock(int vert)
{
    locks[vert].lock;
}

void UF_HAND_OVER_HAND_LOCKING::unlock(int vert)
{
    locks[vert].unlock();
}


