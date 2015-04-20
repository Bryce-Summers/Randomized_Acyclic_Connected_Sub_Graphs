#include "../include/UF_FULL_LOCKING.h"
#include <stdlib.h>

UF_FULL_LOCKING::UF_FULL_LOCKING() : UF_ADT()
{
    //ctor
}

UF_FULL_LOCKING::~UF_FULL_LOCKING()
{
    //dtor
}

// -- Constructor.

bool UF_FULL_LOCKING::connected(int v1, int v2)
{
    return op_find(v1) == op_find(v2);
}

void UF_FULL_LOCKING::op_union(int v1, int v2)
{
    link(op_find(v1), op_find(v2));
}

/* // Recursive Version of find.
int UF_Serial::op_find(int vertex)
{
    int parent = parents[vertex];

    if(parent != vertex)
    {
        // Recursive Find;
        parent = op_find(parent);

        // Path Compression.
        parents[vertex] = parent;
    }

    return parent;
}*/

int UF_FULL_LOCKING::op_find(int vertex_initial)
{

    lock_all();

    // 1st transversal, find the root.

    int vertex = vertex_initial;

    int parent = parents[vertex];

    while(parent != vertex)
    {
        vertex = parent;
        parent = parents[vertex];
    }

    int root = vertex;


    // Second transversal, path compression.

    vertex = vertex_initial;
    parent = parents[vertex];

    while(parent != vertex)
    {
        parents[vertex] = root;
        vertex = parent;
        parent = parents[vertex];
    }


    unlock_all();
    return root;
}

// Union by Rank.
void UF_FULL_LOCKING::link(int v1, int v2)
{
    // Very important.
    if(v1 == v2)
	{
		return;
	}

	lock_all();

	int rank1 = ranks[v1];
	int rank2 = ranks[v2];

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

	unlock_all();
}

// Global locking functions.
void UF_FULL_LOCKING::lock_all()
{
    lock_all.lock();
}

void UF_FULL_LOCKING::unlock_all()
{
    lock_all.unlock();
}