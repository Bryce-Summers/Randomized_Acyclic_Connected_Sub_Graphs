#ifndef MAZE_ADT_H
#define MAZE_ADT_H

#include "Graph.h"
#include <map>

/*
 * The Maze interface, written by Bryce Summers on 4/12/2015.
 *
 *
 * We need to provide a standardized way of describing nodes, edges,
 * and the 2D embedding conflicts between edges.
 */

class Maze_ADT
{
    public:
        Maze_ADT();
        virtual ~Maze_ADT();


        /* This should return the number "nodes" in the maze.
         */
        virtual int getNumberOfVertices() = 0;

        // Returns the characteristic Edge List containing all possible edges.
		// This List makes no gurantees about the ordering or lack therof of the edges.
		// FIXME : Should we not pass EdgeLists by value??
		// the caller of this function will own the memory and be responsible for freeing it.
        virtual EdgeList * populateEdgeList() = 0;

        /*
         * This method should return a list of the nodes representing
         *
         */
        virtual std::map<Edge, EdgeList *> * getConflicts() = 0;

    protected:
    private:
};

#endif // MAZE_ADT_H
