using namespace std;

#include "../include/UF_HAND_OVER_HAND_LOCKING.h"
#include <stdlib.h>
#include <mutex>

/*
 * Concurrent Union Find Data structure.
 *
 * Written by Bryce Summers and Brandon Lum.
 * 4/19/2015
 *
 * Major Overhaul by Bryce Summers on 5/9/2015.
 *
 * Features locks for ever node.
 * Hand over Hand locking is used.
 *
 * Invariants : All nodes are greater than or equal to their parents.
 *
 * Implementation details :
 * 1. All locks should be taken in descending order.
 *    lock(2) before lock(1), to prevent dead lock with the finds.
 * 2. locks may theoretically be released in any order.
 */


// -- Constructor.
UF_HAND_OVER_HAND_LOCKING::UF_HAND_OVER_HAND_LOCKING(int size)
{

    this->size = size;

    this->nodes = (uf_hand_over_hand_node_t *)malloc(sizeof(uf_hand_over_hand_node_t) * size);


    for(int i = 0; i < size; i++)
    {
        this->nodes[i].parent = i;
		new (&nodes[i].lock)std::mutex();// Special cpp syntax.
    }

}


UF_HAND_OVER_HAND_LOCKING::~UF_HAND_OVER_HAND_LOCKING()
{

  free(this->nodes);

    // CPP should automatically call the superclass destructor.
}


// true --> nodes are connected as of the ending of this call.
// false -> nodes were disconnected at the time of beginning of the call.
bool UF_HAND_OVER_HAND_LOCKING::connected(int v1, int v2)
{

    int root1 = v1;
    int root2 = v2;

	while(true)
	{

	  root1 = op_find(root1);
	  root2 = op_find(root2);

	  // If two nodes that are identical were found,
	  // then these branches must be connected for all time.
	  if(root1 == root2)
	  {
		return true;
	  }

	  int max = std::max(root1, root2);
	  int min = std::min(root1, root2);

	  lock(max);
	  lock(min);

	  // If both parents are root nodes, but are not equal, then return false.
	  if(nodes[max].parent == max && nodes[min].parent == min)
	  {
		unlock(max);
		unlock(min);
		return false;
	  }

	  unlock(max);
	  unlock(min);
	  continue;
	}
}

// Returns true iff the two separate partitions have now been joined.
bool UF_HAND_OVER_HAND_LOCKING::op_union(int v1, int v2)
{

  int root1 = v1;
  int root2 = v2;

  do
  {

	root1 = op_find(v1);
	root2 = op_find(v2);

	// Already unioned.
	if(root1 == root2)
	{
	  return false;
	}

  }while(!link(root1, root2));

  // These nodes must have now been successfully linked.
  return true;

}

// finds the current root node of this vertex.
// Does not leave any locked nodes.
int UF_HAND_OVER_HAND_LOCKING::op_find(int vertex_initial)
{

  int vertex = vertex_initial;

  lock(vertex);
  while(true)
  {
	int parent = nodes[vertex].parent;

	if(parent > vertex)
	{
	  throw runtime_error("Error : Linking Invariant Compromised, Lesser Linked to Greater!!");
	}

	if(parent == vertex)
	{
	  unlock(vertex);

	  // Perform some path compression before returning.
	  path_compress(vertex_initial, vertex);
	  return vertex;
	}

	// Parent < vertex.

	// Hand over hand transition.
	lock(parent);
	unlock(vertex);

	vertex = parent;
  }
}

// Path compresses the path from vertex to root.
// Stops when it reaches the root or a point where the path leads to a node less than the root.
void UF_HAND_OVER_HAND_LOCKING::path_compress(int vertex, int root)
{
  lock(vertex);
  while(nodes[vertex].parent > root)
  {
	// Remember the parent.
	int parent = nodes[vertex].parent;

	// Compress the parent.
	nodes[vertex].parent = root;

	// Reached a rootnode.
	if(parent == vertex)
	{
	  unlock(parent);
	  return;
	}

	// Continue on our journey.
	lock(parent);
	unlock(vertex);
	vertex = parent;
  }

  // The path has either ended at the 'root' or has been path compressed by another call.
  unlock(vertex);
  return;
}

/*
 * Union by parents less than children.
 * Returns true if the link succeeded.
 * Links can only work between two distinct root nodes.
 */
bool UF_HAND_OVER_HAND_LOCKING::link(int v1, int v2)
{

    // Same vertices, already linked.
    if(v1 == v2)
	{
		return false;
	}

    int min = std::min(v1, v2);
	int max = std::max(v1, v2);

	lock(max);
	lock(min);

    // Link greater --> lesser greater is still a root node.
	if(nodes[max].parent == max)
	{
	  nodes[max].parent = min;
	  unlock(max);
	  unlock(min);
	  return true;
	}


	// -- Greater node is no londer a root node,
	// so we can not yet perform a link.

	unlock(max);
	unlock(min);

	return false;
}


// Lock management code.

void UF_HAND_OVER_HAND_LOCKING::lock(int vert)
{
  nodes[vert].lock.lock();
}

void UF_HAND_OVER_HAND_LOCKING::unlock(int vert)
{
  nodes[vert].lock.unlock();
}


