#include "../include/Tester.h"

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
bool Tester::test(Maze_ADT &maze)
{

}

void Tester::test_then_union(UF_ADT * UF, int v1, int v2)
{
    ASSERT(!UF->connected(v1, v2));
    ASSERT(!UF->connected(v2, v1)); // Test symmetric.
    ASSERT(UF->op_find(v1) != UF->op_find(v2));
    UF -> op_union(v1, v2);
    ASSERT(UF->connected(v1, v2));
    ASSERT(UF->connected(v2, v1));
    ASSERT(UF->op_find(v1) == UF->op_find(v2));
}

/*
 * Unit tests a union find structure serially.
 * Makes sure the the structure implementation fulfills all of the invariants of the abstract data type.
 *
 * Takes a function that allows the function to create a Union find structure of a specific size.
 */
bool Tester::test(UF_ADT * (*func_create)(int))
{
	UF_ADT * UF = func_create(10);

    for(int i = 0; i < 9; i++)
    {
        int root_1 = UF->op_find(i);
        int root_2 = UF->op_find(i + 1);
        ASSERT(root_1 != root_2);
        ASSERT(!UF->connected(i, i + 1));
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
 * 4/19/2015 : Moved the Main maze generation code here.
 */
bool Tester::test(Maze_ADT &maze, UF_ADT &UF)
{
    /* FIXME : I have not been able to properly specify a hash function for Edges.
   EdgeList edges = maze.populateEdgeList();

   // Randomize the set of edges.
   edges.shuffle();

   std::map<Edge, EdgeList> conflict_map;

   // Create a new set to track the edges that may not be added to the maze.
   std::unordered_set<Edge> forbidden;

   // FIXME : Make sure this cpp code compiles and works.
   int len = edges.getSize();
   for(int index = 0; index < len; index++)
   {

       Edge e = edges.edges[index];

       int v1 = e.vertex_1;
       int v2 = e.vertex_2;


       if((forbidden.find(e) != forbidden.end()) && !UF.connected(v1, v2))
       {
           // Connect sets spanned by the edge.
           UF.op_union(e.vertex_1, e.vertex_2);

           std::vector<Edge> conflicts = conflict_map[e].getEdges();

           // FIXME : Do we need to add e as well, or will it be in its own conflict map.
           forbidden.insert(e);

           int len = conflicts.size();
           for(int i = 0; i < len; i++)
           {
               Edge e2 = conflicts[i];
               forbidden.insert(e2);
           }
       }
   }//*/
}

// Throws an error if it does not pass.
void Tester::ASSERT(bool predicate)
{
    if(!predicate)
    {
        throw std::runtime_error("ASSERTION FAILED!!");
    }
}

// Returns true iff the list of edges is connected and acyclic.
bool Tester::connected_and_acyclic(EdgeList edgeList, int num_nodes)
{
    UF_Serial UF = UF_Serial(num_nodes);

    std::vector<int> v_list_1 = edgeList.vertex1;
    std::vector<int> v_list_2 = edgeList.vertex2;
    int len = edgeList.vertex1.size();

    // Make all of the edge connections, while checking for acyclicness.
    for(int i = 0; i < len; i++)
    {
        int v1 = v_list_1[i];
        int v2 = v_list_2[i];

        // This edge would introduce a cycle.
        if(UF->connected(v1, v2))
        {
            return false;
        }

        UF->op_union(v1[i], v2[i]);
    }

    int root = UF->op_find(0);
    for(int i = 1 ; i < num_nodes; i++)
    {
        // Not connected.
        if(root != UF->op_find(i))
        {
            return false;
        }
    }

    return true;

}
