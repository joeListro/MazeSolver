/* ***  Author:  Joe Listro
*  Last Update:  April 18, 2015
*     Filename:  main.cpp
*
*  Certification of Authenticity:
*     I certify that this assignment is entirely my own work.
**********************************************************************/

#include "Maze.h"

using namespace std;

int main() {
	cout << "Place all maze image files in ~\\JoeListroMazeSolver\\Maze Images\\\n";
	// Before running, move sample maze images from \Sample Maze Images\ to \Maze Images\ 
	bool play = true;
	char usrInput;
	Maze *tMaze = nullptr;
	do {
		tMaze = new Maze; 
		delete tMaze; 
		tMaze = nullptr;
		cout << "Would you like to solve another maze? Y / n\n";
		cin >> usrInput;
		if (usrInput == 'N' || usrInput == 'n') { play = false; }
		system("cls");
	} while (play);

	return 0;
}