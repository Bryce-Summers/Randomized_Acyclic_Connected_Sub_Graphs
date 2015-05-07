#ifndef TESTER_H
#define TESTER_H


#include <iostream>
using namespace std;


#include "Maze_ADT.h"
#include "UF_ADT.h"
#include <unordered_set>
#include <set>
#include "UF_Serial.h"
#include <stdexcept>

#include "EdgeList.h"
#include "Edge.h"

#include <thread>

class Tester
{
    public:
        Tester();
        virtual ~Tester();

        // Unit tests a maze implementation.
        // For instance, mazes must have possible edges such
        // that it is possible to connect all of the nodes.
        bool test(Maze_ADT *maze);

        /*
         * Unit tests a union find structure serially.
         * Makes sure the the structure implementation fulfills all of the invariants of the abstract data type.
         */
        bool test(UF_ADT * (*func_create)(int));

        // Returns true iff the given maze and union find structure can be used to generate randomized spanning trees.
        // FIXME : Move the main.cpp code here.
        bool test(Maze_ADT &maze, UF_ADT &UF, bool test_correctness);

		// Tests the given maze and Union find structure in a parrallel manner.
		bool test_parallel(Maze_ADT &maze, UF_ADT &UF, int num_partitions, bool test_correctness);

        // Returns true iff the list of edges is connected and acyclic.
        bool connected_and_acyclic(EdgeList * edgeList, int num_nodes, bool acyclic = true);

		bool connected(EdgeList * edgeList, int num_nodes)
		{
		  return connected_and_acyclic(edgeList, num_nodes, false);
		}

    protected:
    private:

        // Throws an error if it does not pass.
        void ASSERT(bool predicate);

        void test_then_union(UF_ADT * UF, int v1, int v2, bool connected_already);

		/* The worker thread functon for parrallel computations. Welds vertice together with
		 * edge paste.
		 * The Output is a list of all of the edges that this function has properly welded using
		 * the UF structure.
		 */
		void welder(EdgeList * edges, UF_ADT *UF, EdgeList * output);

};

#endif // TESTER_H
