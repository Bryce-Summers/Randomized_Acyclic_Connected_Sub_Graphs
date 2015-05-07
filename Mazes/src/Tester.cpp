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
bool Tester::test(Maze_ADT * maze)
{

  int num_nodes = maze -> getNumberOfVertices();
  EdgeList * edges = maze -> populateEdgeList();

  // len - 1 edges required at a minnimum to allow for a spanning tree to exist.
  ASSERT(edges -> getSize() >= num_nodes - 1);

  // These are here mainly to make sure that the immplementation correctly sets
  // the edges array and does not segfault.
  ASSERT(edges -> getSize() > 0);
  ASSERT(edges -> getEdge(0).vertex_1 != edges -> getEdge(0).vertex_2);


  int size = edges -> getSize();

  edges -> shuffle();

  ASSERT(edges -> getSize() == size);

  // FIXME : Put in a test for the shuffling method?

  /*
	1. Make sure it is possible to construct a minnimum spanning tree.
	2. Make sure the invariants in the conflict graph are valid.
  */

  // Create a new set to track the edges that may not be added to the maze.

  // Ensure the possibility of constructing a minnnimum spanning tree.
  ASSERT(connected(edges, num_nodes));

  delete edges;

  return false;
}

/* @param connected_already, specifies whether it is expected that the two vertices
 * are connected at the instance of this function call.
 * Ensures, the two vertices will be union together and will be connected together.
 */
void Tester::test_then_union(UF_ADT * UF, int v1, int v2, bool connected_already)
{
    ASSERT(UF->connected(v1, v2) == connected_already);
    ASSERT(UF->connected(v2, v1) == connected_already); // Test symmetric.
    ASSERT((UF->op_find(v1) != UF->op_find(v2)) != connected_already);
    UF -> op_union(v1, v2);
    ASSERT(UF->connected(v1, v2));
    ASSERT(UF->connected(v2, v1));
    ASSERT(UF->op_find(v1) == UF->op_find(v2));
}

/*
 * Unit tests a union find structure serially.
 * Makes sure the the structure implementation fulfills all of the invariants of
 * the abstract data type.
 *
 * Takes a function that allows the function to create a Union find structure of a specific size.
 *
 * This function deletes the UF after it is done using it.
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

    test_then_union(UF, 0, 2, false);
    test_then_union(UF, 1, 2, false);
    test_then_union(UF, 2, 3, false);
    test_then_union(UF, 5, 4, false);
    test_then_union(UF, 0, 5, false);
    test_then_union(UF, 5, 2, true);

	// Free the memory after testing.
	delete UF;

	return true;
}


/* Returns true iff the given maze and union find structure
 * can be used to generate randomized spanning trees.
 * 4/19/2015 : Moved the Main maze generation code here.
 */
bool Tester::test(Maze_ADT &maze, UF_ADT &UF)
{

   EdgeList *edges = maze.populateEdgeList();

   EdgeList *output = new EdgeList();

   // Randomize the set of edges.
   edges->shuffle();

   std::map<Edge, EdgeList> conflict_map;

   // Create a new set to track the edges that may not be added to the maze.
   std::unordered_set<Edge> forbidden;

   // Try to add every edge to the maze.
   // Populate the output set of edges.
   int len = edges->getSize();
   for(int index = 0; index < len; index++)
   {

       Edge e = edges->edges[index];

       int v1 = e.vertex_1;
       int v2 = e.vertex_2;

       if((forbidden.find(e) == forbidden.end()) && !UF.connected(v1, v2))
       {
           // Connect sets spanned by the edge.
           UF.op_union(e.vertex_1, e.vertex_2);

		   output -> addEdge(e.vertex_1, e.vertex_2);

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

   bool result = connected_and_acyclic(output, maze.getNumberOfVertices(), true);

   delete edges;
   delete output;

   return result;
}

bool Tester::test_parallel(Maze_ADT &maze, UF_ADT &UF, int num_partitions)
{

   EdgeList *edges = maze.populateEdgeList();

   // Randomize the set of edges.
   edges->shuffle();

   EdgeList *output = new EdgeList();

   EdgeList ** partitions = edges -> split(num_partitions);

   std::thread * threads = (std::thread *)malloc(sizeof(std::thread*)*num_partitions);

   // Spawn all of the threads.
   for(int i = 0; i < num_partitions; i++)
   {
	 // Frees internal partitions.
	 EdgeList * partition = partitions[i];
	 threads[i] = std::thread(welder, partition, &UF);
   }

   // Join all of the threads.
   for(int i = 0; i < num_partitions; i++)
   {
	 threads[i].join();
   }

   // TODO : Determine whether we have produced correct results or not.

   delete edges;
   delete output;

   // Free malloced arrays.
   free(partitions);
   free(threads);


   bool result = false;
   return result;

}

// A worker thread for a parrallel computation.
void Tester::welder(EdgeList * edges, UF_ADT * UF)
{

   EdgeList *output = new EdgeList();

   //   std::map<Edge, EdgeList> conflict_map;

   // Create a new set to track the edges that may not be added to the maze.
   std::unordered_set<Edge> forbidden;

   // Try to add every edge to the maze.
   // Populate the output set of edges.
   int len = edges->getSize();
   for(int index = 0; index < len; index++)
   {

       Edge e = edges->edges[index];

       int v1 = e.vertex_1;
       int v2 = e.vertex_2;

       if((forbidden.find(e) == forbidden.end()) && !UF->connected(v1, v2))
       {
           // Connect sets spanned by the edge.
           UF->op_union(e.vertex_1, e.vertex_2);

		   output -> addEdge(e.vertex_1, e.vertex_2);

		   /*
           std::vector<Edge> conflicts = conflict_map[e].getEdges();

           // FIXME : Do we need to add e as well, or will it be in its own conflict map.
           forbidden.insert(e);

           int len = conflicts.size();
           for(int i = 0; i < len; i++)
           {
               Edge e2 = conflicts[i];
               forbidden.insert(e2);
           }
		   */
       }
   }//*/

   delete edges;
   delete output;
}

// Throws an error if it does not pass.
void Tester::ASSERT(bool predicate)
{
    if(!predicate)
    {
        throw std::runtime_error("ASSERTION FAILED!!");
    }
}

// Returns true iff the list of edges defines a subgraph on a graph with
// contiguous nodes labeled [0, num_nodes) is connected and acyclic.
// SERIAL.
// does not check acyclicness if acyclic = false.
bool Tester::connected_and_acyclic(EdgeList * edgeList, int num_nodes, bool acyclic)
{

    UF_Serial UF = UF_Serial(num_nodes);

    std::vector<int> v_list_1 = edgeList -> vertex1;
    std::vector<int> v_list_2 = edgeList -> vertex2;
    int len = edgeList->vertex1.size();

	if(len < num_nodes - 1)
	{
	  cout << "Not enough edges, num_nodes = " << num_nodes << ", len = " << len << endl;
	  ASSERT(false);
	  return false;
	}

    // Make all of the edge connections, while checking for acyclicness.
    for(int i = 0; i < len; i++)
    {
        int v1 = v_list_1[i];
        int v2 = v_list_2[i];

        // This edge would introduce a cycle.
        if(UF.connected(v1, v2) && acyclic)
        {
		  cout << "ERROR: Not Acyclic\n";
		  ASSERT(false);
          return false;
        }

        UF.op_union(v1, v2);
    }

    int root = UF.op_find(0);
    for(int i = 1 ; i < num_nodes; i++)
    {

        // Not connected.
        if(root != UF.op_find(i))
        {
		  cout <<"ERROR: Not Connected " << UF.op_find(i) << endl;
		  cout << "--Root " << root << endl;
		  cout << "--iteration " << i << endl;
		  ASSERT(false);
          return false;
        }
	}

    return true;


}
