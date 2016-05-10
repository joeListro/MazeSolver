Welcome to Joe Listro's 24-bit Bitmap Maze Solver!

Before running for the first time, either load your own maze images (in 24-bit bitmap format only!) or the 
program will check for images in /JoeListroMazeSolver/Maze Images/


In order to print tried and failed paths(like in /Sample Solved Maze Images/), 

	set line 146 of Maze.h from

		if (false)

	to

		if (true)