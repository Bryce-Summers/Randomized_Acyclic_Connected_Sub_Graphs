#include <iostream>
#include <set>
#include "include/Maze.h"
#include "include/Graph.h"
#include "include/UF.h"
#include "include/Tester.h"

#include "include/CycleTimer.h"

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
int SIZE = 2000;
//int SIZE = 10;

int THREAD_NUM = 8;

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

  println("--Testing Dense Maze");
  maze = new Maze_Dense(SIZE);
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
  // TEST -> test(&create_UF_CAS_CPC);

  //println("--Skipping UF CAS Full Path compression, because it is not yet implemented.");

  println("--Testing UF CAS Full Path Compression.");
  TEST -> test(&create_UF_CAS_FPC);

  println("--Testing UF Full global locking.");
  TEST -> test(&create_UF_FULL_LOCKING);

  /*  println("--Skipping Hand over Hand locking.");
  /*/
  println("--Testing UF Hand over hand locking.");
  TEST -> test(&create_UF_HAND_OVER_HAND_LOCKING);
  //*/

  println("--Testing UF CAS No Path Compression.");
  TEST -> test(&create_UF_CAS_NPC);

  println("--Testing UF CAS Full Path Compression.");
  TEST -> test(&create_UF_CAS_FPC);


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
double maze_serial(Tester * TEST, Maze_ADT &maze)
{

    double a = CycleTimer::currentSeconds();

    //Maze_ADT maze = Maze_2dLattice();
    UF_Serial UF = UF_Serial(maze.getNumberOfVertices());
	bool correct = TEST->test(maze, UF, CHECK_CORRECTNESS);

    double b = CycleTimer::currentSeconds();


	if(CHECK_CORRECTNESS)
	  cout << "--Correctness: " << correct << endl;

	return b - a;
}


double maze_parrallel(Tester * TEST, UF_ADT * (*func_create)(int), int num_threads, Maze_ADT &maze)
{

    double a = CycleTimer::currentSeconds();

	UF_ADT * UF = func_create(maze.getNumberOfVertices());
	bool correct = TEST -> test_parallel(maze, *UF, num_threads, CHECK_CORRECTNESS);

	double b = CycleTimer::currentSeconds();

	if(CHECK_CORRECTNESS)
	  cout << "--Correctness: " << correct << endl;

    return b - a;

}

void printParrallelDescription(string name)
{
    cout << "Parrallel " << THREAD_NUM <<"-threads, " << name << endl;
}

void printTotalTime(double time)
{
	cout << "--Total Time = " << time*1000 << "milli seconds" << endl;
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

	//*
	Maze_2dLattice maze = Maze_2dLattice(SIZE);
	cout << "maze = Lattice, size = " << SIZE << endl;
	//*/
	/*
	Maze_Dense maze = Maze_Dense(SIZE);
	cout << "maze = Dense, size = " << SIZE << endl;
	//*/

	double time;
	cout << "UF-Serial." << endl;
	time = maze_serial(TEST, maze);
	printTotalTime(time);

	printParrallelDescription("Full Locking.");
	time = maze_parrallel(TEST, &create_UF_FULL_LOCKING, THREAD_NUM, maze);
	printTotalTime(time);

	printParrallelDescription("HAND over HAND.");
	time = maze_parrallel(TEST, &create_UF_HAND_OVER_HAND_LOCKING, THREAD_NUM, maze);
	printTotalTime(time);

	printParrallelDescription("CAS, No Path Compression");
	time = maze_parrallel(TEST, &create_UF_CAS_NPC, THREAD_NUM, maze);
	printTotalTime(time);


	printParrallelDescription("CAS, Full Path Compression");
	time = maze_parrallel(TEST, &create_UF_CAS_FPC, THREAD_NUM, maze);
	printTotalTime(time);



	// Clean up memory.
	println("Clean up.");
	delete TEST;

    cout<< "Exiting. Have a nice day." << endl;

    return 0;
}
