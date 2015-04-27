#include <iostream>
#include <set>
#include "include/Maze.h"
#include "include/Graph.h"
#include "include/UF.h"
#include "include/Tester.h"



// Used for timing.
#include <ctime>
#include <unistd.h>


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

  cout << "Testing an implementation.";

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

   cout<< "Program has started." << endl;


   Tester * TEST = new Tester();

#if defined(DEBUG)

  cout<< "Testing the implementations" << endl;
  test_implementations(TEST);
  cout << "Implementations Passed Unit Tests." << endl;
#endif



	cout << "Starting the maze testing." << endl;

    clock_t a = clock();
    maze_serial(TEST);
	clock_t b = clock();
	cout << "Maze Time = " << (b - a) << endl;


	cout << "Clean up." << endl;

	// Clean up memory.
	delete TEST;


	cout<< "Exiting. Have a nice day." << endl;

    return 0;
}
