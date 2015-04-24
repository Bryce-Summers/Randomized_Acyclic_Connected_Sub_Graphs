#include <iostream>
#include <set>
#include "include/Maze.h"
#include "include/Graph.h"
#include "include/UF.h"
#include "include/Tester.h"


using namespace std;


/* Random Spanning Tree Mazes project Main class.
 *
 * Written by Bryce Summers and Brandon Lum.
 * @BryceSummers on Git Hub.
 */


// DEBUG mode.
#define DEBUG

void test_maze_implementations(Tester * TEST)
{
  Maze_ADT * maze = new Maze_2dLattice();
  TEST -> test(maze);
  delete maze;

  /** Test other mazes when they are created.
  maze = Maze

  */


}

void test_UF_implementations(Tester * TEST)
{

}

void test_implementations(Tester * TEST)
{
  test_maze_implementations(TEST);
  test_UF_implementations(TEST);
}



void maze_serial(Tester * TEST)
{
    //Maze_ADT maze = Maze_2dLattice();
    Maze_2dLattice maze = Maze_2dLattice();
    UF_Serial UF = UF_Serial(maze.getNumberOfVertices());

    cout << TEST->test(maze, UF);
}



int main()
{

   Tester * TEST = new Tester();

#if defined(DEBUG)
  test_implementations(TEST);
#endif


    maze_serial(TEST);


	// Clean up memory.
	delete TEST;

    return 0;
}
