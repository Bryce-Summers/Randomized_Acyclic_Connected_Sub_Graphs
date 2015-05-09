#include "../include/Maze_Dense.h"

Maze_Dense::Maze_Dense(int size)
{
  this -> size = size;
}

Maze_Dense::~Maze_Dense()
{
    //dtor
}

/* This should return the number "nodes" in the maze.
 */
int Maze_Dense::getNumberOfVertices()
{
  return size;
}

// Returns the characteristic Edge List containing all possible edges.
// Returns a complete graph on size vertices for Maze_Dense.
EdgeList * Maze_Dense::populateEdgeList()
{
  EdgeList * output = new EdgeList();

  // Add an edge for every pair of edges.

  for(int a = 0; a < size; a++)
  for(int b = a + 1; b < size; b++)
  {
	output->addEdge(a, b);
  }

  return output;
}

/*
 * This method returns a pointer to a map from Edges to those Edges that intersect it.
 *
 * FIXME : Implement actual conlicts if they are desired.
 */
std::map<Edge, EdgeList *> * Maze_Dense::getConflicts()
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
