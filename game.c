#include <ctype.h>
#include "game.h"
#include "board.h"
#include "player.h"

Cell board[BOARD_HEIGHT][BOARD_WIDTH];
Player thePlayer;
Position aPosition;
char userInput2[LINE_LIMIT2 + MARGIN2];

/*Main menu option 1
- play the game as per the specification.*/
void printMenu()
{
	printf("You can use the following commands to play the game:\n");
	printf("load <g>\n");
	printf("   g: number of the game board to load\n");
	printf("init <x>,<y>,<direction>\n");
	printf("   x: horizontal position of the car on the board (between 0 & 9)\n");
	printf("   y: vertical position of the car on the board (between 0 & 9)\n");
	printf("   direction: direction of the car's movement (north, east, south, west)\n");
	printf("forward (or f)\n");
	printf("turn_left (or l)\n");
	printf("turn_right (or r)\n");
	printf("quit\n\n");
}

/*Displays board of choice to console*/
void loadGame()
{
	if (strstr(userInput2, "load"))
	{
		if (strstr(userInput2, "load 1") != NULL)
		{
			loadBoard(board, BOARD_1);
			displayBoard(board, &thePlayer);
		}

		else if (strstr(userInput2, "load 2") != NULL)
		{
			loadBoard(board, BOARD_2);
			displayBoard(board, &thePlayer);
		}
		else
		{
			printf("\nError: Invaild input (loadGame).\n\n");
		}
	}
}

/*Initialises and places player with direction on chosen board*/
void initGame()
{
	if ((strstr(userInput2, "init") != NULL) && ((strlen(userInput2) == 13) || (strlen(userInput2) == 14)))
	{
		if (isdigit(userInput2[5]) && isdigit(userInput2[7]))
		{
			aPosition.x = (int)(userInput2[5] - '0');
			aPosition.y = (int)(userInput2[7] - '0');

			if (placePlayer(board, aPosition))
			{
				board[aPosition.y][aPosition.x] = PLAYER;
			}
			else
			{
				printf("\nError: Cannot place player on a blocked cell.\n\n");
				readRestOfLine();
			}

		if (strstr(userInput2, "NORTH") != NULL || strstr(userInput2, "north") != NULL)
		{
			initialisePlayer(&thePlayer, &aPosition, NORTH);
		}

		else if (strstr(userInput2, "EAST") != NULL || strstr(userInput2, "east") != NULL)
		{
			initialisePlayer(&thePlayer, &aPosition, EAST);
		}

		else if (strstr(userInput2, "SOUTH") != NULL || strstr(userInput2, "south") != NULL)
		{
			initialisePlayer(&thePlayer, &aPosition, SOUTH);
		}

		else if (strstr(userInput2, "WEST") != NULL || strstr(userInput2, "west") != NULL)
		{
			initialisePlayer(&thePlayer, &aPosition, WEST);
		}

		startGame();

		}
		else
		{
			printf("Error: Invalid Input (initGame)\n\n");
			readRestOfLine();
		}
	}
}

/*Controls player movement on board*/
void playerMove()
{
	if (strstr(userInput2, "forward") != NULL || strstr(userInput2, "f") != NULL)
	{
		switch (movePlayerForward(board, &thePlayer))
		{
		case OUTSIDE_BOUNDS:
			printf("\nThe car is at the edge of the board and cannot move further in that direction.\n\n");
			break;

		case CELL_BLOCKED:
			printf("\nError: cannot move forward because the road is blocked.\n\n");
			break;

		default:
			break;
		}
	}

	else if (strstr(userInput2, "turn_left") != NULL || strstr(userInput2, "l") != NULL)
	{
		turnDirection(&thePlayer, TURN_LEFT);
	}

	else if (strstr(userInput2, "turn_right") != NULL || strstr(userInput2, "r") != NULL)
	{
		turnDirection(&thePlayer, TURN_RIGHT);
	}

	else if (strstr(userInput2, "quit") != NULL || strstr(userInput2, "q") != NULL)
	{
		/*Exit to menu*/
	}
	else
	{
		printf("Error: Invalid Input (playerMove)\n\n");
		readRestOfLine();
	}
}

/*Game menu prompts*/
int startGame()
{
	while (1)
	{
		/*displays board to show current player position*/
		displayBoard(board, &thePlayer);
		printf("forward (or f)\n");
		printf("turn_left (or l)\n");
		printf("turn_right (or r)\n");
		printf("quit\n\n");

		fgets(userInput2, LINE_LIMIT2 + MARGIN2, stdin);

		/* check for buffer overflow [sscanf_example.c@wk3 rmit]*/
		if (userInput2[strlen(userInput2) - 1] != '\n') /*user enter*/
		{
			printf("Error: Invalid Input (startGame)\n\n");
			readRestOfLine();
		}

		playerMove();

		if (strstr(userInput2, "quit") != NULL || strstr(userInput2, "q") != NULL)
		{
			printf("Total player moves: %d\n\n", thePlayer.moves);
			return EXIT_SUCCESS;
			/*Exit user from playGame to main menu*/
		}
	}
}

/*This function makes all the calls to board & player and handles interaction
* with the user*/
int playGame()
{
	initialiseBoard(board);
	displayBoard(board, NULL); /*newly added, re-compile to server 4/04*/

	while (1)
	{
		printMenu();

		fgets(userInput2, LINE_LIMIT2 + MARGIN2, stdin);
		/* check for buffer overflow [sscanf_example.c@wk3 rmit]*/
		if (userInput2[strlen(userInput2) - 1] != '\n') /*user enter*/
		{/*update*/
			printf("Error: Invalid Input.(playGame)\n\n");
			readRestOfLine();
		}
		/* remove newline [sscanf_example.c@wk3 rmit]*/
		userInput2[strlen(userInput2) - 1] = 0;

		loadGame();
		initGame();

		if (strstr(userInput2, "quit") != NULL || strstr(userInput2, "q") != NULL)
		{
			return EXIT_SUCCESS;
			/*Exit user from playGame to main menu*/
		}
	}
}
