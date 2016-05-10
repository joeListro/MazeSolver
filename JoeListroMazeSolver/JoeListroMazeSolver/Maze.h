/* ***  Author:  Joe Listro
*  Last Update:  April 18, 2015
*     Filename:  Maze.h
*
*  Certification of Authenticity:
*     I certify that this assignment is entirely my own work.
**********************************************************************/

// Disable error C4996: 'std::_Copy_impl'
#define _SCL_SECURE_NO_WARNINGS

#include <string>
#include <sstream>
#include "bitmap_image.hpp"
#include "mazeHelper.h"
#include "timerSystem.h"

using namespace std;

class Maze
{
private:
	int mazeArray[3202][3202];
	mazeBlock start, end;
	bitmap_image *bMaze;
	unsigned int mazeWidth, mazeHeight;
	string saveFileName;
	TimerSystem timer;
	double timeToSolve;

	void load();
	bool recursiveSolve(mazeBlock &curBlock, Direction prevDir);
	bool isValidBlock(mazeBlock &curBlock, Direction prevDir);
	void visitBlock(mazeBlock &curBlock, Direction prevDir);
	void paintCorrectPath(mazeBlock &curBlock);
	void paintFalsePath(mazeBlock &curBlock);
	void paintStartLocation();
	void paintEndLocation();
public:
	Maze(string filename)
	{
		saveFileName = filename;
		load();
	};
	Maze()
	{
		cout << "What is the file name of the maze you wish to solve (exclude '.bmp'): \n";
		cin >> saveFileName;
		load();
	};
	~Maze()
	{
		delete bMaze;
	};
	void solveIt();
	void saveBMP();
};

void Maze::load()
{
	unsigned char red = 0, green = 0, blue = 0;
	stringstream filename;
	filename << ".\\Maze Images\\" << saveFileName << ".bmp";
	bMaze = new bitmap_image(filename.str());
	if (bMaze->width() == 0) { 
		filename.str("");
		filename << ".\\Sample Maze Images\\" << saveFileName << ".bmp";
		bMaze = new bitmap_image(filename.str());
		if (bMaze->width() == 0) {
			cout << "Unable to load image. File does not exist!\n";
			return;
		}
	}
	filename.str("");
	filename << ".\\Solved Maze Images\\" << saveFileName << "_solved.bmp";
	saveFileName = filename.str();
	mazeWidth = bMaze->width();
	mazeHeight = bMaze->height();

	for (unsigned int x = 0; x < mazeWidth; x++)
	{
		for (unsigned int y = 0; y < mazeHeight; y++)
		{
			bMaze->get_pixel(x, y, red, green, blue);
			if ((red == 255) && (green == 255) && (blue == 255))
			{
				mazeArray[x][y] = 0;
			}
			else if ((red == 0) && (green == 0) && (blue == 0))
			{
				mazeArray[x][y] = 1;
			}
			else
			{
				cout << "ERROR, ODD COLOR DETECTED!";
			}
		}
	}
	start.moveBlock(((mazeWidth / 2) - 15), 2);
	end.moveBlock(((mazeWidth / 2) + 1), (mazeHeight - 16));
	solveIt();
	return;
}

void Maze::solveIt()
{
	mazeBlock curBlock(start);
	curBlock.moveUp();
	visitBlock(curBlock, Up);
	curBlock.moveDown();
	timer.startClock();
	bool solved = recursiveSolve(curBlock, Down); 
	timeToSolve = timer.getTime();
	if (solved == true) { saveBMP(); }
	return;
}

bool Maze::recursiveSolve(mazeBlock &curBlock, Direction prevDir)
{
	if (curBlock == end) {
		return true; 
	}
	if (isValidBlock(curBlock, prevDir)) {
		visitBlock(curBlock, prevDir);
		curBlock.moveLeft();
		if (recursiveSolve(curBlock, Left)) { // Recalls function one to the left
			curBlock.moveRight();
			paintCorrectPath(curBlock);
			return true;
		}
		curBlock.moveRight();
		curBlock.moveRight();
		if (recursiveSolve(curBlock, Right)) { // Recalls function one to the right
			curBlock.moveLeft();
			paintCorrectPath(curBlock);
			return true;
		}
		curBlock.moveLeft();
		curBlock.moveUp();
		if (recursiveSolve(curBlock, Up)) { // Recalls function one up
			curBlock.moveDown();
			paintCorrectPath(curBlock);
			return true;
		}
		curBlock.moveDown();
		curBlock.moveDown();
		if (recursiveSolve(curBlock, Down)) { // Recalls function one down
			curBlock.moveUp();
			paintCorrectPath(curBlock);
			return true;
		}
		curBlock.moveUp();
	}
	if (false) // set to true to print dead ends and false recursions
	{
		paintFalsePath(curBlock);
	}
	return false;
}

bool Maze::isValidBlock(mazeBlock &curBlock, Direction prevDir)
{
	unsigned int x, y;
	switch (prevDir)
	{
	case Left:
		x = curBlock.xStart;
		for (y = curBlock.yStart; y <= curBlock.yEnd; y++)
		{
			if ((mazeArray[x][y] == wasHere) || (mazeArray[x][y] == Wall)) { 
				return false; 
			}
		}
		break;
	case Right:
		x = curBlock.xEnd;
		for (y = curBlock.yStart; y <= curBlock.yEnd; y++)
		{
			if ((mazeArray[x][y] == wasHere) || (mazeArray[x][y] == Wall)) { 
				return false; 
			}
		}
		break;
	case Up:
		y = curBlock.yStart;
		for (x = curBlock.xStart; x <= curBlock.xEnd; x++)
		{
			if ((mazeArray[x][y] == wasHere) || (mazeArray[x][y] == Wall)) { 
				return false; 
			}
		}
		break;
	case Down:
		y = curBlock.yEnd;
		for (x = curBlock.xStart; x <= curBlock.xEnd; x++)
		{
			if ((mazeArray[x][y] == wasHere) || (mazeArray[x][y] == Wall)) { 
				return false; 
			}
		}
		break;
	}
	return true;
}


void Maze::visitBlock(mazeBlock &curBlock, Direction prevDir)
{
	unsigned int x, y;
	switch (prevDir)
	{
	case Left:
		x = curBlock.xStart;
		for (y = curBlock.yStart; y <= curBlock.yEnd; y++)
		{
			mazeArray[x][y] = wasHere;
		}
		break;
	case Right:
		x = curBlock.xEnd;
		for (y = curBlock.yStart; y <= curBlock.yEnd; y++)
		{
			mazeArray[x][y] = wasHere;
		}
		break;
	case Up:
		y = curBlock.yStart;
		for (x = curBlock.xStart; x <= curBlock.xEnd; x++)
		{
			mazeArray[x][y] = wasHere;
		}
		break;
	case Down:
		y = curBlock.yEnd;
		for (x = curBlock.xStart; x <= curBlock.xEnd; x++)
		{
			mazeArray[x][y] = wasHere;
		}
		break;
	}
}

void Maze::paintCorrectPath(mazeBlock &curBlock)
{
	if (bMaze->set_region((curBlock.xStart + 5), (curBlock.yStart + 5), 4, 4, 0, 255, 0)) { return; } else {
		cout << "ERROR\n";
		return;
	}
}

void Maze::paintFalsePath(mazeBlock &curBlock)
{
	if (bMaze->set_region((curBlock.xStart + 5), (curBlock.yStart + 5), 4, 4, 255, 102, 0)) { return; }	else {
		cout << "ERROR\n";
		return;
	}
}

void Maze::saveBMP()
{
	//Paint Start and End
	paintStartLocation();
	paintEndLocation();

	// Save file
	bMaze->save_image(saveFileName);
	cout << "Maze was solved in " << timeToSolve << "seconds by Joe's Maze Solutions.\n";
	return;
}



void Maze::paintStartLocation()
{
	if (bMaze->set_region((start.xStart + 3), (start.yStart + 3), 8, 8, 0, 0, 255)) { return; } else {
		cout << "ERROR\n";
		return;
	}
}

void Maze::paintEndLocation()
{
	if (bMaze->set_region((end.xStart + 3), (end.yStart + 3), 8, 8, 255, 0, 0))	{ return; } else {
		cout << "ERROR\n";
		return;
	}
}