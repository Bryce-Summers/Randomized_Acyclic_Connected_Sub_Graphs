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
//#define VERBOSE

void println(std::string message)
{
#if defined(VERBOSE)
  cout << message << endl;
#endif
}

void test_maze_implementations(Tester * TEST)
{
  println("--Testing 2d Lattice");
  Maze_ADT * maze = new Maze_2dLattice();
  TEST -> test(maze);
  delete maze;

  /** Test other mazes when they are created.
  maze = Maze

  */

}

UF_ADT * create_UF_serial(int size)
{
  return new UF_Serial(size);
}

void test_UF_implementations(Tester * TEST)
{
  println("--Testing UF Serial");

  TEST -> test(&create_UF_serial);

}

void test_implementations(Tester * TEST)
{
  println("Testing maze implementations");
  test_maze_implementations(TEST);
  println("Testing UF implementations");
  test_UF_implementations(TEST);
}



void maze_serial(Tester * TEST)
{
    //Maze_ADT maze = Maze_2dLattice();
    Maze_2dLattice maze = Maze_2dLattice();
    UF_Serial UF = UF_Serial(maze.getNumberOfVertices());
    cout << "Correctness: " << TEST->test(maze, UF) << endl;
}

int main()
{

   println("Program has started.");


   Tester * TEST = new Tester();

#if defined(DEBUG)

   println("Testing the implementations");
   test_implementations(TEST);
   println("Implementations Passed Unit Tests.");
#endif



    println("Starting the maze testing.");

    clock_t a = clock();
    maze_serial(TEST);
	clock_t b = clock();
	cout << "Maze Time = " << (b - a) << " clockticks" << endl;

	println("Clean up.");

	// Clean up memory.
	delete TEST;


    cout<< "Exiting. Have a nice day." << endl;

    return 0;
}
