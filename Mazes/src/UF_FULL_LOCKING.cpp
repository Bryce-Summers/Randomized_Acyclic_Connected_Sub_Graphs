#include "../include/UF_FULL_LOCKING.h"
#include <stdlib.h>

UF_FULL_LOCKING::UF_FULL_LOCKING(int size)
{
    this->parents = (int*) malloc(sizeof(int)*size);
    this->ranks   = (int*) malloc(sizeof(int)*size);
    this->size = size;

    for(int i = 0; i < size; i++)
    {
        parents[i] = i;
        ranks[i]   = 0;
    }
}

UF_FULL_LOCKING::~UF_FULL_LOCKING()
{
    free(parents);
    free(ranks);
}

// -- Constructor.

bool UF_FULL_LOCKING::connected(int v1, int v2)
{
  lock_all();
  bool result = find_no_lock(v1) == find_no_lock(v2);
  unlock_all();

  return result;

}

bool UF_FULL_LOCKING::op_union(int v1, int v2)
{
    lock_all();
    bool result = link(find_no_lock(v1), find_no_lock(v2));
	unlock_all();

    return result;
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
	int root = find_no_lock(vertex_initial);
    unlock_all();
    return root;
}


int UF_FULL_LOCKING::find_no_lock(int vertex_initial)
{

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

    return root;
}

// Union by Rank.
bool UF_FULL_LOCKING::link(int v1, int v2)
{
    // Very important.
    if(v1 == v2)
	{
		return false;
	}

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

	return true;

}

// Global locking functions.
void UF_FULL_LOCKING::lock_all()
{
    lock_global.lock();
}

void UF_FULL_LOCKING::unlock_all()
{
    lock_global.unlock();
}
