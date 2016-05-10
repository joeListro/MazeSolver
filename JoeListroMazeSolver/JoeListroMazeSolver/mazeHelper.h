/* ***  Author:  Joe Listro
*  Last Update:  April 18, 2015
*     Filename:  Maze.h
*
*  Certification of Authenticity:
*     I certify that this assignment is entirely my own work.
**********************************************************************/

enum arrayValue { Path = 0, Wall = 1, correctPath = 2, wasHere = 3 };

enum Direction { Up = 0, Down = 1, Left = 2, Right = 3 };

struct mazeBlock
{
	unsigned int xStart, xEnd, yStart, yEnd;

	mazeBlock();
	mazeBlock(const mazeBlock &srcMazeBlock);
	mazeBlock(unsigned int xNew, unsigned int yNew);
	mazeBlock(unsigned int xStartNew, unsigned int xEndNew, unsigned int yStartNew, unsigned int yEndNew);

	void moveBlock(unsigned int xNew, unsigned int yNew);
	void paintCorrectPath(bitmap_image *bMaze);

	inline bool operator== (const mazeBlock &srcMazeBlock);

	void moveLeft();
	void moveRight();
	void moveUp();
	void moveDown();
};

mazeBlock::mazeBlock()
{
	xStart = xEnd = yStart = yEnd = 0;
}

mazeBlock::mazeBlock(const mazeBlock &srcMazeBlock)
{
	xStart = srcMazeBlock.xStart;
	xEnd = srcMazeBlock.xEnd;
	yStart = srcMazeBlock.yStart;
	yEnd = srcMazeBlock.yEnd;
}

mazeBlock::mazeBlock(unsigned int xNew, unsigned int yNew)
{
	xStart = xNew;
	xEnd = (xNew + 13);
	yStart = yNew;
	yEnd = (yNew + 13);
}

mazeBlock::mazeBlock(unsigned int xStartNew, unsigned int xEndNew, unsigned int yStartNew, unsigned int yEndNew)
{
	xStart = xStartNew;
	xEnd = xEndNew;
	yStart = yStartNew;
	yEnd = yEndNew;
}

void mazeBlock::moveBlock(unsigned int xNew, unsigned int yNew)
{
	xStart = xNew;
	xEnd = (xNew + 13);
	yStart = yNew;
	yEnd = (yNew + 13);
}

inline bool mazeBlock::operator== (const mazeBlock &srcMazeBlock)
{
	return ((xStart == srcMazeBlock.xStart) &&
			(yStart == srcMazeBlock.yStart));
}

void mazeBlock::moveLeft()
{
	xStart--, xEnd--;
	return;
}
void mazeBlock::moveRight()
{
	xStart++, xEnd++;
	return;
}
void mazeBlock::moveUp()
{
	yStart--, yEnd--;
	return;
}
void mazeBlock::moveDown()
{
	yStart++, yEnd++;
	return;
}