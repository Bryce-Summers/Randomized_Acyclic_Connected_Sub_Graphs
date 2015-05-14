#Randomized Parrallel Maze Generation
(Also known as randomized spanning tree generation)

A Final project for the 15-418 class at Carnegie Mellon University.

![alt text](https://github.com/Bryce-Summers/Bryce-Summers.github.io/blob/master/Project_Pages/418FinalProject/Lattice2.png "Example Output Maze from a 2d Lattice")

Description
-------

This code parrallelizes and achieves a speedup for an algorithm for constructing mazes using a union find structure.

We have implemented many parrallel friendly Union find structures. Of particular note, please see our 3 implementations of lock free union find structures, where each one uses a different path compression strategy.

Detailed Info
-----

Please see the following webpage for detailed information about this project, including a proudly and thoroughly written paper.

http://bryce-summers.github.io/Project_Pages/418Project2



Visualization Tool
-----------------

To visualize the outputs of this program, one may feed a list of integers representing the edges output by this program
as the input to the Graph Renderer program at https://github.com/Bryce-Summers/JavaCode/tree/master/GraphRenderer

We have not yet made this proccess very user friendly.
