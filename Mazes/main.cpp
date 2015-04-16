#include <iostream>
#include <set>
#include "include/Maze.h"
#include "include/Graph.h"
#include "include/UF.h"

using namespace std;

void maze_serial()
{
    //Maze_ADT maze = Maze_2dLattice();
    Maze_2dLattice maze = Maze_2dLattice();

    UF_Serial UF = UF_Serial(maze.getNumberOfVertices());

    EdgeList edges = maze.populateEdgeList();

    // Randomize the set of edges.
    edges.shuffle();

    map<Edge, EdgeList> conflict_map;

    // Create a new set to track the edges that may not be added to the maze.
    std::set<Edge> forbidden;

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

            for(Edge e2 : conflicts)
            {
                forbidden.insert(e2);
            }
        }
    }
}

int main()
{

    maze_serial();

    return 0;
}
