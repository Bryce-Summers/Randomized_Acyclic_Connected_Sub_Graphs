#ifndef TESTER_H
#define TESTER_H

#include "Maze_ADT.h"
#include "UF_ADT.h"
#include <unordered_set>
#include <set>

class Tester
{
    public:
        Tester();
        virtual ~Tester();

        // Unit tests a maze implementation.
        // For instance, mazes must have possible edges such
        // that it is possible to connect all of the nodes.
        bool test(Maze_ADT &maze);

        /*
         * Unit tests a union find structure serially.
         * Makes sure the the structure implementation fulfills all of the invariants of the abstract data type.
         */
        bool test(UF_ADT * (*func_create)(int));

        // Returns true iff the given maze and union find structure can be used to generate randomized spanning trees.
        // FIXME : Move the main.cpp code here.
        bool test(Maze_ADT &maze, UF_ADT &UF);

        // Returns true iff the list of edges is connected and acyclic.
        bool connected_and_acyclic(EdgeList edgeList, int num_nodes);

    protected:
    private:

        // Throws an error if it does not pass.
        void ASSERT(bool predicate);

        void test_then_union(UF_ADT * UF, int v1, int v2);

};

#endif // TESTER_H
