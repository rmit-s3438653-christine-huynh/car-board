#include "board.h"
#include "player.h"

Cell BOARD_1[BOARD_HEIGHT][BOARD_WIDTH] =
{
	{ BLOCKED, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY },
	{ EMPTY, BLOCKED, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, BLOCKED, EMPTY, EMPTY },
	{ EMPTY, EMPTY, BLOCKED, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY },
	{ EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, BLOCKED, EMPTY, EMPTY },
	{ EMPTY, EMPTY, EMPTY, EMPTY, BLOCKED, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY },
	{ EMPTY, EMPTY, BLOCKED, EMPTY, EMPTY, BLOCKED, EMPTY, BLOCKED, EMPTY, EMPTY },
	{ EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, BLOCKED, EMPTY, EMPTY, EMPTY },
	{ EMPTY, EMPTY, BLOCKED, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY },
	{ EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY },
	{ EMPTY, EMPTY, BLOCKED, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, BLOCKED }
};

Cell BOARD_2[BOARD_HEIGHT][BOARD_WIDTH] =
{
	{ BLOCKED, BLOCKED, BLOCKED, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY },
	{ EMPTY, BLOCKED, BLOCKED, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY },
	{ EMPTY, BLOCKED, BLOCKED, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY },
	{ EMPTY, EMPTY, EMPTY, EMPTY, BLOCKED, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY },
	{ EMPTY, EMPTY, EMPTY, EMPTY, BLOCKED, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY },
	{ EMPTY, BLOCKED, BLOCKED, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY },
	{ EMPTY, EMPTY, EMPTY, EMPTY, BLOCKED, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY },
	{ EMPTY, BLOCKED, BLOCKED, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY },
	{ EMPTY, BLOCKED, BLOCKED, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY },
	{ EMPTY, BLOCKED, BLOCKED, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY }
};

/*Initialise the board - set all the cells in the board to EMPTY.*/
void initialiseBoard(Cell board[BOARD_HEIGHT][BOARD_WIDTH])
{
	int h, w = 0;

	for (h = 0; h < BOARD_HEIGHT; h++)
	{
		for (w = 0; w < BOARD_WIDTH; w++)
		{
			board[h][w] = EMPTY;
		}
	}
}

/*Load the board - set all the cells in board to those present in boardToLoad.*/
void loadBoard(Cell board[BOARD_HEIGHT][BOARD_WIDTH],
	Cell boardToLoad[BOARD_HEIGHT][BOARD_WIDTH])
{
	int h, w = 0;
	for (h = 0; h < BOARD_HEIGHT; h++)
	{
		for (w = 0; w < BOARD_WIDTH; w++)
		{
			if (boardToLoad[h][w] == EMPTY)
			{
				board[h][w] = EMPTY;
			}

			else if (boardToLoad[h][w] == BLOCKED)
			{
				board[h][w] = BLOCKED;
			}
			else if (boardToLoad[h][w] == PLAYER)
			{
				board[h][w] = PLAYER;
			}
			else
			{
				/*Unknown error.*/
			}
		}
	}
}

/*Try to place the PLAYER cell at the provided position.*/
Boolean placePlayer(Cell board[BOARD_HEIGHT][BOARD_WIDTH], Position position)
{
	/*If the position is outside the bounds of the max value of x,y axis of board*/
	if (position.y > BOARD_HEIGHT || position.x > BOARD_WIDTH)
	{
		return FALSE;
	}
	/*If the provided position is BLOCKED*/
	else if (board[position.y][position.x] == BLOCKED)
	{
		return FALSE;
	}
	/*If the provided position is EMPTY*/
	else if (board[position.y][position.x] == EMPTY)
	{
		return TRUE;
	}

	else
	{
		return FALSE;
	}
}

/*Try to move the player forward
- note the player has a current direction and position.*/
PlayerMove movePlayerForward(Cell board[BOARD_HEIGHT][BOARD_WIDTH],
	Player * player)
{
	/*Get the position as if the player did move*/
	Position playerPosition = getNextForwardPosition(player);

	/*If this new position is outside the bounds of the board return
	* OUTSIDE_BOUNDS.*/
	if (playerPosition.x >= BOARD_WIDTH || playerPosition.x < 0)
	{
		return OUTSIDE_BOUNDS;
	}
	else if(playerPosition.y >= BOARD_HEIGHT || playerPosition.y < 0)
	{
		return OUTSIDE_BOUNDS;
	}

	/*If the new position is on-top of a BLOCKED cell then
	* return CELL_BLOCKED.*/
	else if (board[playerPosition.y][playerPosition.x] == BLOCKED)
	{
		return CELL_BLOCKED;
	}

	/*if the new position is EMPTY then remove PLAYER from the current
	* player's position on the board (set cell to EMPTY) and set the new position
	* to PLAYER. And call "updatePosition(...)" to update the player's position
	* then return PLAYER_MOVED*/
	else if (board[playerPosition.y][playerPosition.x] == EMPTY)
	{
		board[player->position.y][player->position.x] = EMPTY;
		updatePosition(player, playerPosition);
		board[player->position.y][player->position.x] = PLAYER;
		return PLAYER_MOVED;
	}

	else 
	{
		return CELL_BLOCKED;
	}

}

/* Display the board according to the specification.*/
void displayBoard(Cell board[BOARD_HEIGHT][BOARD_WIDTH], Player * player)
{
	int h, w = 0;
	printf("| |0|1|2|3|4|5|6|7|8|9|\n");
	for (h = 0; h < BOARD_HEIGHT; h++)
	{
		for (w = 0; w < BOARD_WIDTH; w++)
		{
			if (w == 0)
			{
				printf("|%d|", h);
			}

			if (board[h][w] == EMPTY)
			{
				printf(" "); /*EMPTY_OUTPUT)*/
			}

			else if (board[h][w] == BLOCKED)
			{
				printf("*");/*BLOCKED_OUTPUT*/
			}
			else if (board[h][w] == PLAYER)
			{
				displayDirection(player->direction);
			}
			printf("|");
		}
		printf("\n");
	}
	printf("\n");
}
