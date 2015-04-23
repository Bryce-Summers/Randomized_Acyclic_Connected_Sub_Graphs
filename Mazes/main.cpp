#include <iostream>
#include <set>
#include "include/Maze.h"
#include "include/Graph.h"
#include "include/UF.h"
#include "include/Tester.h"

using namespace std;

void maze_serial()
{
    //Maze_ADT maze = Maze_2dLattice();
    Maze_2dLattice maze = Maze_2dLattice();
    UF_Serial UF = UF_Serial(maze.getNumberOfVertices());

    Tester * TEST = new Tester();

    cout << TEST->test(maze, UF);
}

int main()
{

    maze_serial();

    return 0;
}
