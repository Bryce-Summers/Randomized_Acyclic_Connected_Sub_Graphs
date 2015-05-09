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
 *
 *
 * Please do not remove the println statements, instead just comment out the verbose #define.
 */


// DEBUG mode.
#define DEBUG

// VERBOSE mode.
#define VERBOSE


const bool CHECK_CORRECTNESS = true;

// The problem size. Vertices = SIZE^2;
const int SIZE = 400;

void println(std::string message)
{
#if defined(VERBOSE)
  cout << message << endl;
#endif
}

void test_maze_implementations(Tester * TEST)
{
  println("--Testing 2d Lattice");
  Maze_ADT * maze = new Maze_2dLattice(SIZE);
  TEST -> test(maze);
  delete maze;

  /** Test other mazes when they are created.
  maze = Maze

  */

}

// UF creation Functions.
UF_ADT * create_UF_serial(int size)
{
  return new UF_Serial(size);
}


UF_ADT * create_UF_CAS_CPC(int size)
{
  return new UF_CAS_CPC(size);
}


UF_ADT * create_UF_CAS_FPC(int size)
{
  return new UF_CAS_FPC(size);
}


UF_ADT * create_UF_CAS_NPC(int size)
{
  return new UF_CAS_NPC(size);
}


UF_ADT * create_UF_FULL_LOCKING(int size)
{
  return new UF_FULL_LOCKING(size);
}


UF_ADT * create_UF_HAND_OVER_HAND_LOCKING(int size)
{
  return new UF_HAND_OVER_HAND_LOCKING(size);
}


// -- Unit testing functions.

void test_UF_implementations(Tester * TEST)
{
  println("--Testing UF Serial");
  TEST -> test(&create_UF_serial);

  println("--Skipping UF CAS Constrained Path compression, because it is not yet implemented.");
  //println("--Testing UF CAS Constrained Path compression.");
  //  TEST -> test(&create_UF_CAS_CPC);

  println("--Skipping UF CAS Full Path compression, because it is not yet implemented.");
  /*
  println("--Testing UF CAS Full Path Compression.");
  TEST -> test(&create_UF_CAS_FPC);
  */

  println("--Testing UF CAS No Path Compression.");
  TEST -> test(&create_UF_CAS_NPC);

  println("--Testing UF Full global locking.");
  TEST -> test(&create_UF_FULL_LOCKING);

  /*  println("--Skipping Hand over Hand locking.");
  /*/
  println("--Testing UF Hand over hand locking.");
  TEST -> test(&create_UF_HAND_OVER_HAND_LOCKING);
  //*/

}

void test_implementations(Tester * TEST)
{
  println("Unit Testing maze implementations");
  test_maze_implementations(TEST);
  println("Unit Testing UF implementations serially.");
  test_UF_implementations(TEST);
}


// runs the computations using UF_Serial in a serial fashion.
// Returns the total time in clock ticks.
clock_t maze_serial(Tester * TEST)
{

    clock_t a = clock();

    //Maze_ADT maze = Maze_2dLattice();
    Maze_2dLattice maze = Maze_2dLattice(SIZE);
    UF_Serial UF = UF_Serial(maze.getNumberOfVertices());
	bool correct = TEST->test(maze, UF, CHECK_CORRECTNESS);

	clock_t b = clock();

	if(CHECK_CORRECTNESS)
	  cout << "Correctness: " << correct << endl;
	cout << "UF_Serial Time = " << (b - a)/1000 << " kilo clockticks" << endl;

	return b - a;
}


clock_t maze_parrallel(Tester * TEST, UF_ADT * (*func_create)(int), int num_threads)
{

    clock_t a = clock();

    Maze_2dLattice maze = Maze_2dLattice(SIZE);
	UF_ADT * UF = func_create(maze.getNumberOfVertices());
	bool correct = TEST -> test_parallel(maze, *UF, num_threads, CHECK_CORRECTNESS);

	clock_t b = clock();

	if(CHECK_CORRECTNESS)
	  cout << "Correctness: " << correct << endl;

    return b - a;

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
	cout << "maze = 2D Lattice, size = " << SIZE << endl;

	clock_t time;
	time = maze_serial(TEST);
    //time = maze_parrallel(TEST, &create_UF_HAND_OVER_HAND_LOCKING, 4);
	//cout << "Parrallel 4-threads, Hand over hand Time = " << time << " clockticks" << endl;

	time = maze_parrallel(TEST, &create_UF_FULL_LOCKING, 4);
	cout << "Parrallel 4-threads, Full Locking Time = " << time/1000 << " kilo clockticks" << endl;

	time = maze_parrallel(TEST, &create_UF_CAS_NPC, 4);
	cout << "Parrallel 4-threads, CAS, No Path Compression = " << time/1000 << " kilo clockticks" << endl;

	time = maze_parrallel(TEST, &create_UF_HAND_OVER_HAND_LOCKING, 4);
	cout << "Parrallel 4-threads, HAND over HAND, No Path Compression = " << time/1000 << " kilo clockticks" << endl;


	// Clean up memory.
	println("Clean up.");
	delete TEST;

    cout<< "Exiting. Have a nice day." << endl;

    return 0;
}
