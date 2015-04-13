#include <iostream>

using namespace std;

void maze_serial()
{
    Maze_ADT maze = new Maze_2dLattice();

    UF_ADT UF = new UF_Serial(maze.getNumberOfVertices());

    EdgeList edges = maze.populateEdgeList();

    // Randomize the set of edges.
    edges.shuffle();

    map<Edge, EdgeList> conflict_map;

    // Create a new set to track the edges that may not be added to the maze.
    set<Edge> forbidden;

    // FIXME : Make sure this cpp code compiles and works.
    int len = edges.getSize();
    for(int index = 0; index < len; index++)
    {

        Edge e = edges.edges[index];

        int v1 = e.vertex_1;
        int v2 = e.vertex_2;

        if(!forbidden.contains(e) && !UF.connected(v1, v2))
        {
            // Connect sets spanned by the edge.
            UF.op_union(e.vertex_1, e.vertex_2);

            EdgeList conflicts = conflict_map[e];

            // FIXME : Do we need to add e as well, or will it be in its own conflict map.
            forbidden.add(e);

            for(Edge e2 : conflicts)
            {
                forbidden.add(e2);
            }
        }
    }
}

int main()
{

    maze_serial();

    return 0;
}
