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
    return 100;
}

// Returns the characteristic Edge List containing all possible edges.
EdgeList * Maze_2dLattice::populateEdgeList()
{
    return new EdgeList();
}

/*
 * This method should return a list of the nodes representing
 *
 */
std::map<Edge, EdgeList> Maze_2dLattice::getConflicts()
{
    return std::map<Edge,EdgeList>();
}
