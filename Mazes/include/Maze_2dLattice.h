#ifndef MAZE_2DLATTICE_H
#define MAZE_2DLATTICE_H

#include "Maze_ADT.h"
#include "EdgeList.h"

class Maze_2dLattice : public Maze_ADT
{
    public:
        Maze_2dLattice();
        virtual ~Maze_2dLattice();

        /* This should return the number "nodes" in the maze.
         */
        virtual int getNumberOfVertices();

        // Returns the characteristic Edge List containing all possible edges.
        virtual EdgeList *populateEdgeList();

        /*
         * This method should return a list of the nodes representing
         *
         */
        virtual std::map<Edge, EdgeList *> * getConflicts();

    protected:
    private:

        // 10 by 10 maze.
        const static int size = 100;

		// -- Helper functions.
		int getIndex(int x, int y);

};

#endif // MAZE_2DLATTICE_H
