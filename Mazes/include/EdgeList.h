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

		void addEdge(Edge e)
		{
		  addEdge(e.vertex_1, e.vertex_2);
		}

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

		Edge getEdge(int index)
		{
		  return edges[index];
		}


		void swap(int index1, int index2, std::vector<int>& vec);
		void swap(int index1, int index2, std::vector<Edge>& vec);

		// Splits this edge list into the input number of equal parts.
		// Caller is responsible for freeing the list and all component lists.
		EdgeList ** split(int parts);

		void append(EdgeList * other);

		int size();

		std::string edge_string(int index);


    protected:
    private:
};

#endif // EDGELIST_H
