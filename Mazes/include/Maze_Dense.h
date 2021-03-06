#ifndef MAZE_DENSE_H
#define MAZE_DENSE_H

#include "Maze_ADT.h"
#include "EdgeList.h"

class Maze_Dense : public Maze_ADT
{
    public:
        Maze_Dense(int size);
        virtual ~Maze_Dense();

        /* This should return the number "nodes" in the maze.
         */
        virtual int getNumberOfVertices();

        // Returns the characteristic Edge List containing all possible edges.
        virtual EdgeList *populateEdgeList();

        /*
         * This method should return a list of the nodes representing
         * all of the conflicts in the maze.
         */
        virtual std::map<Edge, EdgeList *> * getConflicts();

    protected:
    private:

        // 10 by 10 maze.
        int size = 100;

		// -- Helper functions.
		int getIndex(int x, int y);

};

#endif // MAZE_DENSE_H
