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

	// -- Horizontal Edges.
    if(x < size - 1)
    {
      output -> addEdge(v, v_right);
    }

	// -- Vertical Edges.
    if(y < size - 1)
    {
      output -> addEdge(v, v_down);
    }

  }

  return output;

}

/*
 * This method returns a pointer to a map from Edges to those Edges that intersect it.
 *
 * There are not conflicting Edges in a 2D Lattice except edges with themselves.
 */
std::map<Edge, EdgeList *> * Maze_2dLattice::getConflicts()
{

	auto * output_map = new std::map<Edge, EdgeList *>();


	// Go Through all of the Edges in this lattice and set their conflict lists to only contain themselves.

    EdgeList * edges = populateEdgeList();
    std::vector<Edge> edge_vector = edges->edges;

	for(auto iter = edge_vector.begin(); iter != edge_vector.end(); ++iter)
	{
	  Edge edge = *iter;

	  EdgeList * edgeList = new EdgeList();

	  edgeList->addEdge(edge);
	  (*output_map)[edge] = edgeList;
	}


    return output_map;
}

int Maze_2dLattice::getIndex(int x, int y)
{
    return y*size + x;
}
