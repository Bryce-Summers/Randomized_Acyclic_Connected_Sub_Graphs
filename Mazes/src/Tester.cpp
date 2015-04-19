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


/*
 * Unit tests a union find structure serially.
 * Makes sure the the structure implementation fulfills all of the invariants of the abstract data type.
 */
bool Tester::test(UF_ADT UF)
{
/*

    Here is some java unit testing code.

	private boolean test_UnionFind()
	{
		UnionFind<Integer> UF = new UnionFind<Integer>();

		for(int i = 0; i < 10; i++)
		{
			UF.makeset(i);
		}

		UF.union(1, 2);
		print(UF);

		UF.union(2, 3);
		print(UF);

		UF.union(5, 4);
		print(UF);

		UF.union(0, 5);
		print(UF);

		UF.union(5, 2);

		print(UF);

		return true;
	}

*/
}

// Returns true iff the given maze and union find structure can be used to generate randomized spanning trees.
// FIXME : Move the main.cpp code here.
bool Tester::test(Maze_ADT maze, UF_ADT UF)
{

}

// Throws an error if it does not pass.
void ASSERT(bool predicate)
{
    if(!predicate)
    {
        throw std::exception("ASSERTION FAILED!!");
    }
}

