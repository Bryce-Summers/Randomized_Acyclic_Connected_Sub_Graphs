#ifndef EDGELIST_H
#define EDGELIST_H

#include <vector>
#include "Edge.h"
#include <stdlib.h>     /* srand, rand */

class EdgeList
{
    public:
        EdgeList();
        virtual ~EdgeList();

        // Stores a list of vertex1, vertex2 pairs.
        std::vector<int> vertex1;
        std::vector<int> vertex2;

        // Explicit edge objects.
        std::vector<Edge> edges;


        void addEdge(int v1, int v2);

        // Randomizes the order of the edge list.
		// SERIAL.
        void shuffle();

        unsigned int getSize()
        {
            return vertex1.size();
        }

        std::vector<Edge> getEdges()
        {
            return edges;
        }


		void swap(int index1, int index2, std::vector<int>& vec);

    protected:
    private:
};

#endif // EDGELIST_H
