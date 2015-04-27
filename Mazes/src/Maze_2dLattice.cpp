#include "../include/Maze_2dLattice.h"

Maze_2dLattice::Maze_2dLattice()
{
    //ctor
}

Maze_2dLattice::~Maze_2dLattice()
{
    //dtor
}

/* This should return the number "nodes" in the maze.
 */
int Maze_2dLattice::getNumberOfVertices()
{
  return size*size;
}

// Returns the characteristic Edge List containing all possible edges.
EdgeList * Maze_2dLattice::populateEdgeList()
{

  EdgeList * output = new EdgeList();


  for(int x = 0; x < size; x++)
  for(int y = 0; y < size; x++)
  {
    int v = getIndex(x, y);
    int v_right = getIndex(x + 1, y);
    int v_down  = getIndex(x, y + 1);

    if(x < size - 1)
    {
      output -> addEdge(v, v_right);
    }
    if(y < size - 1)
    {
      output -> addEdge(v, v_down);
    }

  }

  return output;

    

}

/*
 * This method should return a list of the nodes representing
 *
 */
std::map<Edge, EdgeList> Maze_2dLattice::getConflicts()
{
    return std::map<Edge,EdgeList>();
}

int Maze_2dLattice::getIndex(int x, int y)
{
    return y*size + x;
}
