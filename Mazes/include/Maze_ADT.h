#ifndef MAZE_ADT_H
#define MAZE_ADT_H

/*
 * The Maze interface, written by Bryce Summers on 4/12/2015.
 *
 *
 * We need to provide a standardized way of describing nodes, edges, and the 2D embedding conflicts between edges.
 */

class Maze_ADT
{
    public:
        Maze_ADT();
        virtual ~Maze_ADT();

    protected:

        /* This should return the number "nodes" in the maze.
         */
        virtual int getNumberOfVertices();

        // Returns the characteristic Edge List containing all possible edges.
        virtual EdgeList populateEdgeList();

        /*
         * This method should return a list of the nodes representing
         *
         */
        virtual std::map<Edge, EdgeList> getConflicts();

    private:
};

#endif // MAZE_ADT_H
