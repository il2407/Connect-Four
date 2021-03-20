#define _CRT_SECURE_NO_WARNINGS
#include "stdio.h"
#include "stdlib.h"
#include "stdbool.h"

/*************** Board ***************/

#define ROWS 6
#define COLS 7
char board[ROWS][COLS];

/*********** Declarations ************/

/// This function initializes the game board by assigning each cell
/// with ' ' (resulting with an empty game board).
void initBoard();
/// This function gets a row number and a column number (a cell),
/// and returns the character in that cell (could be 'X', 'O' or ' ').
/// For example:
/// char c = getCell(1, 1);
char getCell(int row, int col);
/// This function gets a row number, a column number and a sign,
/// and assigns the cell with the given sign.
/// For example:
/// setCell(1, 1, 'X');
void setCell(int row, int col, char sign);
/// This function clears the screen.
void clearScreen();

             /*   Ido Lev
              I.D:206282527   */

/******** New Declarations *********/

//This function prints the board every turn
void printBoard();

//This function gets the coloumn number , returns the first row at that coloumn that's free to have X or O .
int fullCol(int col);

//This function gets coloumn number and the relavant player sign , then make sure that the coloumn is legal 
//then it puts the sign at the right spot using fullCol and returns to legal coloumn
int playLegalTurn(int col, char sign);

//This function gets the coloumn number , returns true if there is a row win
bool checkRwin(int col);

//This function gets the coloumn number , returns true if there is a coloumn win
bool checkCwin(int col);

//This function gets the coloumn number , returns true if there is a right diagonal win
bool checkRDwin(int col);

//This function gets the coloumn number , returns true if there is a left diagonal win
bool checkLDwin(int col);

/*   Ido Lev
  I.D:206282527   */


/********** Main **********/

int main()
{
	printBoard();
	int turns, col , legalCol;
	printf("Hi ,Welcome to Connect Four! \nPlayer 1, Insert a column please(between 1 - 7) : \n");
	scanf("%d", &col);
	turns = 1;

	while (turns < 42) // As long as no one won or had a tie game , keep playing
	{
		if (turns % 2 == 0)
		{
			col=playLegalTurn(col, 'O');
		if (checkLDwin(col)|| checkRDwin(col)|| checkCwin(col)|| checkRwin(col) == true) turns = 50; 
		// Winning codition for player 2
		}
		else
		{
		
			col=playLegalTurn(col, 'X');
		if (checkLDwin(col) || checkRDwin(col) || checkCwin(col) || checkRwin(col) == true) turns = 51;
		// Winning codition for player 1
		}

		clearScreen();
		printBoard();

		if (turns != 50 && turns != 51) 
		// A condition to make sure that if one of the players won 
		//it will stay with the same winning mark number
		{
			if (turns % 2 == 0) printf("Player 1 , Insert a column please (between 1-7): \n");
			else printf("Player 2 , Insert a column please (between 1-7) : \n");
			scanf("%d", &col);
			turns++;
		}
		
	}
	if (turns == 42) printf("Oh my , It's a tie");
	if (turns == 51)  printf("Congratulations :) \nPlayer 1 is the winner");
	if (turns == 50 ) printf("Congratulations :) \nPlayer 2 is the winner");
}

/********** Implementations **********/

char getCell(int row, int col)
{
	return board[row - 1][col - 1];
}

void setCell(int row, int col, char sign)
{
	board[row - 1][col - 1] = sign;
}

void initBoard()
{
	int i, j;

	for (i = 0; i < ROWS; i++)
	{
		for (j = 0; j < COLS; j++)
		{
			setCell(i + 1, j + 1, ' ');
		}
	}
}

void clearScreen()
{
	system("cls");
}
  
/*             /*   Ido Lev
              I.D:206282527   */

/******* New Implementations *******/

//This function prints the board every turn
void printBoard()
{
	int col, row;
	char c;
	c = 'A';
	printf("    ");
	for (row = 7; row > 0; row--)
	{
		for (col = 0; col < 8; col++)
		{
			if (row == 7 && col < 7) printf("%d   ", col + 1);
			else
			{
				if (col == 0) { printf("%c   ", c); c++; }
				else { printf("%c   ", getCell(row, col)); }
			}

		}
		printf("\n\n");

	}
}

//This function gets the coloumn number , returns the first row at that coloumn that's free to have X or O 
int fullCol(int col)
{
	int row;
	row = 1;
	while ((getCell(row, col)) == 'X' || (getCell(row, col)) == 'O') //as long as function getCell 
	{                                                                //returns any value row keeps counting
		row++;
	}
	return row;
}

//This function gets coloumn number and the relavant player sign , then make sure that the coloumn is legal 
//then it puts the sign at the right spot using fullCol and returns to legal coloumn
int playLegalTurn(int col, char sign)
{
	while (fullCol(col) == 7 || col > 7 || col < 1)//as long as the col isn't valid for any reason
	{                                              //the function will keep ask for a new scan
		clearScreen();
		printBoard();
		if (col > 7 || col < 1) printf("Column isn't valid , Please enter a new one ( between 1-7 ): \n");
		else      printf("Column is full , Please enter a new one ( between 1-7 ): \n");

		scanf("%d", &col);
	}

	setCell(fullCol(col), col, sign); // if the value is valid the function 
									 //will use setCell to insert the relevant sign
	return col;

}
	 
//This function gets the coloumn number , returns true if there is a row win
bool checkRwin(int col)
{

	int counter, checkCol, row;
	char sign;
	sign = ' ';
	counter = 1;
	row = fullCol(col) - 1; // fullCol function is checking for the first open space at the coloumn 
	                        // at this function I want to have the top slot that has one of the signs 
	                        //so I can check only the relevant row
	for (checkCol = 1; checkCol < 8; checkCol++)
	{


		if (getCell(row, checkCol) == 'X' || getCell(row, checkCol) == 'O')//I want to prevent the situation where there are 4 
			                                                               //of the same sign in one row but with a ' ' in the middle
		{
			if (getCell(row, checkCol) == sign)
			{
				counter++;
			}
			else
			{
				sign = getCell(row, checkCol);
				counter = 1;
			}
		}
		else
		{
			sign = ' ';
			counter = 1;
		}

		if (counter == 4) return true;
	}
	return false;
}

//This function gets the coloumn number , returns true if there is a coloumn win
bool checkCwin(int col)
{
	int counter, row;
	char sign;
	sign = ' ';
	counter = 1;
	for (row = 1; row < 7; row++)
	{
		if (getCell(row, col) != 'X'&& getCell(row, col) != 'O')return false;//in a coloumn condition I know that if i find an
		                                                                     //empty slot it's the last relevant slot
		else if (getCell(row, col) == sign) counter++;
		else
		{
			sign = getCell(row, col);
			counter = 1;
		}
		

		if (counter == 4) return true;
	}
	return false;
}

//This function gets the coloumn number , returns true if there is a right diagonal win
bool checkRDwin(int col)

{
	int counter, row, checkCol;
	char sign;
	sign = ' ';
	counter = 1;
	checkCol = col;
	row = fullCol(col) - 1;

	while (row != 1 && checkCol != 1)//first I want to get to the beginning of the diagonal
		                             //that way I can scan only the relevant diagonal
	{
		row--;
		checkCol--;
	}
	while (row != 7)
	{
		if (getCell(row, checkCol) == 'X' || getCell(row, checkCol) == 'O')
		//same as the row function , I want to prevent a situation
		//where I keep counting for the same sign
		//even though I had ' ' at the middle of the row
		{
			if (getCell(row, checkCol) == sign)
			{
				counter++;
			}
			else
			{
				sign = getCell(row, checkCol);
				counter = 1;
			}
		}
		else
		{
			sign = ' ';
			counter = 1;
		}

		row++;
		checkCol++;
		if (counter == 4) return true;
	}
	return false;
}

//This function gets the coloumn number , returns true if there is a left diagonal win
bool checkLDwin(int col)
{
	int counter, row, checkCol;
	char sign;
	sign = ' ';
	counter = 1;
	checkCol = col;
	row = fullCol(col) - 1;
	;
	while (row != 1 && checkCol != 7)//first I want to get to the beginning of the diagonal
		                             //that way I can scan only the relevant diagonal
	{
		row--;
		checkCol++;

	}
	while (row < 8)
	{
		if (getCell(row, checkCol) == 'X' || getCell(row, checkCol) == 'O')
		//same as the row function , I want to prevent a situation
		//where I keep counting for the same sign
		//even though I had ' ' at the middle of the row
		{
			if (getCell(row, checkCol) == sign)
			{
				counter++;
			}
			else
			{
				sign = getCell(row, checkCol);
				counter = 1;
			}
		}
		else
		{
			sign = ' ';
			counter = 1;
		}

		row++;
		checkCol--;
		if (counter == 4) return true;
	}
	return false;
}
