//ConsoleApplication4.cpp :
//
#include "pch.h"
#include <iostream>
#include "stdio.h"
//#include <unistd.h>
#include <conio.h>
//#include <time.h>
//#include <thread>
//#include <chrono>
//#include <cstdlib>
#include "windows.h"

using namespace std;

struct Position
{
	//position of x and y and the direction of each block at that position
	//as well as the length
	int x[50];
	int y[50];
	int dx[50];
	int dy[50];
	int length;
};
struct Apple
{
	//the positions of the apple
	int applePosX = 0;
	int applePosY = 0;
};


//function definitions
void drawBoard(int boardSize, Position *playerPointer, Apple *applePos);
Position *movement(Position *playerPointer, int boardSize);
void wrap(Position *playerPointer, int boardSizeWrap);
void appleUpdate(Apple *applePosPointer, int boardsize);
void eat(Position *player, Apple *apple, int boardSize);
bool isAlive(Position *playerPointer);
void title();
void isWin(Position *playerPointer);
void credits();

int main()
{
	Position player;
	Position *playerPointer;
	playerPointer = &player;

	for (int i = 0; i < 50; i++)
	{
		player.x[i] = '\0';
		player.y[i] = '\0';
	}
	for (int i = 0; i < 50; i++)
	{
		player.dx[i] = '\0';
		player.dy[i] = '\0';
	}

	player.x[0] = 10;
	player.y[0] = 10;
	player.dx[0] = 0;
	player.dy[0] = 0;

	player.length = 0;
	int boardSize = 25;

	Apple applePos;
	Apple *applePosPointer = &applePos;
	appleUpdate(applePosPointer, boardSize);

	title();

	while (isAlive(playerPointer))
	{
		Sleep(100);
		drawBoard(boardSize, movement(playerPointer, boardSize), applePosPointer);
		eat(playerPointer, applePosPointer, boardSize);
		isWin(playerPointer);
	}

	credits();

	return 0;
}

void isWin(Position *playerPointer)
{

	if ((*playerPointer).length >= 49)
	{
		printf("You Win!\n");
		printf("To Play Again enter any key (and hit enter)\n");
		(*playerPointer).length = 0;
		int x;
		scanf_s("%i", &x);
	}
}
void title()
{
	printf("Welcome to Snake, my way\n");
	printf("Use the WASD keys to move\n");
	printf("Press any key to continue (and hit enter)\n");
	int x;
	scanf_s("%i", &x);
}
void credits()
{
	for (int i = 0; i < 50; i++)
	{
		printf("You Lose\n");
	}
	Sleep(5000);
}

bool isAlive(Position *playerPointer)
{
	bool xSame = false;
	bool ySame = false;
	for (int i = 1; i <= (*playerPointer).length; i++)
	{
		if ((*playerPointer).x[0] == (*playerPointer).x[i])
		{
			xSame = true;
		}
		if ((*playerPointer).y[0] == (*playerPointer).y[i])
		{
			ySame = true;
		}

		if (xSame == true && ySame == true)
		{
			return false;
		}
	}

	return true;
}
void eat(Position *player, Apple *apple, int boardSize)
{
	if (((*player).x[0] == (*apple).applePosX) && ((*player).y[0] == (*apple).applePosY))
	{
		(*player).length++;
		appleUpdate(apple, boardSize);
	}
}

void appleUpdate(Apple *applePos, int boardsize)
{
	(*applePos).applePosX = (1 + (rand() % (boardsize - 2)));
	(*applePos).applePosY = (1 + (rand() % (boardsize - 2)));
}
//draws the trail(by far the most difficult part)
void trail(Position *playerTrail)
{
	//these increment the first characters by their directions, as everything else is draws off these
	(*playerTrail).x[0] += (*playerTrail).dx[0];
	(*playerTrail).y[0] += (*playerTrail).dy[0];

	//sets every position to the position before it minus that direction so it trails by one for each one
	if ((*playerTrail).length >= 1)
	{
		for (int i = 0; i < (*playerTrail).length; i++)
		{

			for (int j = 1; j <= (*playerTrail).length; j++)
			{
				(*playerTrail).x[j] = (*playerTrail).x[j - 1] - (*playerTrail).dx[j - 1];
				(*playerTrail).y[j] = (*playerTrail).y[j - 1] - (*playerTrail).dy[j - 1];
				//printf();
			}
		}
	}
	//increments every direction by one down the line of things
	for (int i = (*playerTrail).length; i > 0; i--)
	{
		(*playerTrail).dx[i] = (*playerTrail).dx[i - 1];
		(*playerTrail).dy[i] = (*playerTrail).dy[i - 1];
		//printf("In trail() first for loop: (*playerTrail).length = %x, i = %i, (*playerTrail).dx[i] = %i, (*playerTrail).dx[i - 1] = %i, (*playerTrail).dy[i] = %i, (*playerTrail).dy[i - 1] =%i\n" ,(*playerTrail).length, i, (*playerTrail).dx[i], (*playerTrail).dx[i - 1], (*playerTrail).dy[i], (*playerTrail).dy[i - 1]);
	}
}
//wraps the cursor or snake around to the other side of the play area
//this is kinda buggyish, when you loop your old self kinda dissapears 
void wrap(Position *playerPointer, int boardSizeWrap)
{

	if ((*playerPointer).y[0] <= 0)
	{
		(*playerPointer).y[0] = (boardSizeWrap - 1);
	}
	if ((*playerPointer).x[0] <= 0)
	{
		(*playerPointer).x[0] = (boardSizeWrap - 1);
	}
	if ((*playerPointer).y[0] >= boardSizeWrap)
	{
		(*playerPointer).y[0] = 1;
	}
	if ((*playerPointer).x[0] >= boardSizeWrap)
	{
		(*playerPointer).x[0] = 1;
	}
}
//gets input and sets the direction equal to that and also increments the cursor's position that direction one tile
Position *movement(Position *playerPointer, int boardSize)
{
	char key;
	if (_kbhit())
	{
		key = _getch();
		switch (key)
		{
		case 'w':
			(*playerPointer).dy[0] = -1;
			(*playerPointer).dx[0] = 0;
			break;
		case 'a':
			(*playerPointer).dx[0] = -1;
			(*playerPointer).dy[0] = 0;
			break;
		case 's':
			(*playerPointer).dy[0] = 1;
			(*playerPointer).dx[0] = 0;
			break;
		case 'd':
			(*playerPointer).dx[0] = 1;
			(*playerPointer).dy[0] = 0;
			break;
		}
	}
	wrap(playerPointer, boardSize);
	trail(playerPointer);
	return playerPointer;
}
//draws the board and the cursor in its position
void drawBoard(int boardSize, Position *playerPointer, Apple *applePos)
{
	int columns = 0;
	int rows = 0;
	system("cls");
	while (columns <= boardSize)
	{
		for (rows = 0; rows <= boardSize; rows++)
		{
			for (int g = 0; g <= (*playerPointer).length; g++)
			{
				if ((rows == (*playerPointer).x[g]) && (columns == (*playerPointer).y[g]))
				{
					printf("$");
					goto A;
				}
			}
			if (columns == 0 || columns == boardSize)
			{
				printf("%c", 219);
			}
			else if (rows == 0 || rows == boardSize)
			{
				printf("%c", 219);
			}
			else if ((rows == (*applePos).applePosX) && (columns == (*applePos).applePosY))
			{
				printf("A");
			}
			else if ((rows > 0) && (rows < boardSize))
			{
				printf(" ");
			}
		A:
			short x;
		}
		columns++;
		std::cout << endl;
	}
}