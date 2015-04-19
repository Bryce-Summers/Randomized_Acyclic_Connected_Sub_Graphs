#include "../../include/Testing/Tester.h"

Tester::Tester()
{
    //ctor
}

Tester::~Tester()
{
    //dtor
}

/* Unit tests a maze implementation.
 * For instance, mazes must have possible edges such
 * that it is possible to connect all of the nodes.
 */
bool Tester::test(Maze_ADT maze)
{

}

void Tester::test_then_union(UF_ADT UF, int v1, int v2)
{
    ASSERT(!UF.connected(v1, v2));
    ASSERT(!UF.connected(v2, v1)); // Test symmetric.
    ASSERT(UF.op_find(v1) != UF.op_find(v2));
    UF.op_union(v1, v2);
    ASSERT(UF.connected(v1, v2));
    ASSERT(UF.connected(v2, v1));
    ASSERT(UF.op_find(v1) == UF.op_find(v2));
}

/*
 * Unit tests a union find structure serially.
 * Makes sure the the structure implementation fulfills all of the invariants of the abstract data type.
 *
 * Takes a function that allows the function to create a Union find structure of a specific size.
 */
bool Tester::test(UF_ADT (*func_create)(int))
{
	UF_ADT UF = func_create(10);

    for(int i = 0; i < 9; i++)
    {
        int root_1 = UF.op_find(i);
        int root_2 = UF.op_find(i + 1);
        ASSERT(root1 != root_2);
        ASSERT(!UF.connected(i, i + 1));
    }

    test_then_union(UF, 0, 2);

    test_then_union(UF, 1, 2);

    test_then_union(UF, 2, 3);

    test_then_union(UF, 5, 4);

    test_then_union(UF, 0, 5);

    test_then_union(UF, 5, 2);


	return true;
}


/* Returns true iff the given maze and union find structure
 * can be used to generate randomized spanning trees.
 * FIXME : Move the main.cpp code here.
 */
bool Tester::test(Maze_ADT maze, UF_ADT UF)
{

}

// Throws an error if it does not pass.
void Tester::ASSERT(bool predicate)
{
    if(!predicate)
    {
        throw std::exception("ASSERTION FAILED!!");
    }
}

