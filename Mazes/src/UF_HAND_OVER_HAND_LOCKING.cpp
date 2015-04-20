#include "../include/UF_HAND_OVER_HAND_LOCKING.h"
#include <stdlib.h>

/*
 * Concurrent Union Find Data structure.
 *
 * Written by Bryce Summers and Brandon Lum.
 * 4/19/2015
 *
 * Features locks for ever node.
 * Hand over Hand locking is used.
 *
 * Invariants : All nodes are greater than or equal to their parents.
 *
 * Implementation details :
 * 1. All locks should be taken in descending order.
 *    lock(1) before lock(2), to prevent dead lock with the finds.
 * 2. locks may theoretically be released in any order.
 */


// BL: Locality of structure should be revisited
// BS : We should box these pieces of data. (parents, locks) instead of parents*locks to enhance cache locality.

// -- Constructor.
UF_HAND_OVER_HAND_LOCKING::UF_HAND_OVER_HAND_LOCKING(int size) : UF_ADT(size)
{

    this->parents = (int*) malloc(sizeof(int)*size);
    this->ranks   = (int*) malloc(sizeof(int)*size);
    this->size = size;

    for(int i = 0; i < size; i++)
    {
        parents[i] = i;
        ranks[i]   = 0;
    }

    this->locks = (std::mutex *)malloc(sizeof(std::mutex) * size);
}


UF_HAND_OVER_HAND_LOCKING::~UF_HAND_OVER_HAND_LOCKING()
{

    free(parents);
    free(ranks);

    free(locks);

    // CPP should automatically call the superclass destructor.
}

bool UF_HAND_OVER_HAND_LOCKING::connected(int v1, int v2)
{
    int root1 = find_and_lock(v1);
    int root2 = find_and_lock(v2, v1);

    // BS: FIXME : again, ensure that the locks are taken in decreasing order.


    if(root1 == root2)
    {
        unlock(root1);
        return true;
    }

    unlock(root1);
    unlock(root2);

    return false;
}

// Returns true iff two separate partitions have now been joined.
bool UF_HAND_OVER_HAND_LOCKING::op_union(int v1, int v2)
{
    int root1 = op_find(v1);
    int root2 = op_find(v2);

    // Connected already.
    if(root1 == root2)
    {
        return false;
    }

    // FIXME : Make sure the locks are taken in decreasing order!!
    // Potential deadlock oppurtunity here if root1 < root2?


    // Find and hold the locks for the current roots.
    root1 = find_and_lock(root1);
    // Prevent deadlock by stopping at root1 if found.
    root2 = find_and_lock(root2, root1);

    // Connected already.
    if(root1 == root2)
    {
        unlock(root1);
        return false;
    }

    link(root1, root2);

    unlock(root1);
    unlock(root2);

    // Link went through.
    return true;
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
        // BL: We want to keep track of prev vertex
        // and unlock it too
        // want to do something like this:
        // unlock(vertex)
        // ...
        vertex = parent;
        lock(vertex);
        parent = parents[vertex];
    }

    int root = vertex;

    // Second transversal, path compression.

    // BL: Unlock root
    // unlock(root);
    // do the updates, we don't need root locked,
    // cause we know the node will not be deleted,
    // and we are just getting a pointer to it
    // so code should look identical to previous one
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

// See .h file for specification.
int UF_HAND_OVER_HAND_LOCKING::find_and_lock(int vert, int stop)
{
    if(vert == stop)
    {
        return stop;
    }

    lock(vert);

    int parent = parents[vert];

    while(parent != vert)
    {
        if(parent == stop)
        {
            unlock(vert);
            return stop;
        }

        lock(parent);
        unlock(vert);

        vert = parent;
        parent = parents[vert];
    }

    // ASSERT (parent == vert);

    return vert; // or parent.
}

/* Union by parents less than children.
 * REQUIRES : v1 and v2 are locked.
 * REQUIRES : v1 != v2.
 */
void UF_HAND_OVER_HAND_LOCKING::link(int v1, int v2)
{

    // Very important.
    // Note : Should never happen, because this case is now handled in union.
    if(v1 == v2)
	{
	    throw runtime_error("Error : Concurrent link of equal roots.");
		return;
	}

    // Link greater --> lesser.
    if(v1 < v2)
    {
        parents[v2] = v1;
    }
    else
    {
        parents[v1] = v2;
    }

	return;
}


// Lock management code.

void UF_HAND_OVER_HAND_LOCKING::lock(int vert)
{
    locks[vert].lock();
}

void UF_HAND_OVER_HAND_LOCKING::unlock(int vert)
{
    locks[vert].unlock();
}


