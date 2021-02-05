#include "player.h"


/*Initialise the player - set the position, direction to the provided values
* and set moves to 0.*/
void initialisePlayer(Player * player, Position * position, Direction direction)
{   /* TODO */
	player->position.y = position->y;
	player->position.x = position->x;

	player->direction = direction;

	player->moves = 0;
}


/*Turn the player's direction according to the direction of the player and the
* turn direction. */
void turnDirection(Player * player, TurnDirection turnDirection)
{   
	/*Turn right has the following sequence:
	* North -> East
	* East -> South
	* South -> West
	* West -> North */
	if (turnDirection == TURN_RIGHT)
	{
		if (player->direction == NORTH)
		{
			player->direction = EAST;
		}

		else if (player->direction == EAST)
		{
			player->direction = SOUTH;
		}

		else if (player->direction == SOUTH)
		{
			player->direction = WEST;
		}

		else if (player->direction == WEST)
		{
			player->direction = NORTH;
		}
	}

	/*Turn left has the following sequence:
	* North -> West
	* West -> South
	* South -> East
	* East -> North */
	else if (turnDirection == TURN_LEFT)
	{
		if (player->direction == NORTH)
		{
			player->direction = WEST;
		}

		else if (player->direction == WEST)
		{
			player->direction = SOUTH;
		}

		else if (player->direction == SOUTH)
		{
			player->direction = EAST;
		}

		else if (player->direction == EAST)
		{
			player->direction = NORTH;
		}
	}
}

/*Gets the new position as if the player moved forward from the player's
* current position and direction.*/
Position getNextForwardPosition(const Player * player)
{   /* TODO
	* Note the new position can be outside the bounds of the board and could be on
	* a blocked cell. Also note that you should not modify the current position of
	* the player.
	*/

	Position nextPosition;
	if (player->direction == NORTH)
	{
		nextPosition.y = player->position.y - 1;
		nextPosition.x = player->position.x;
	}

	else if (player->direction == EAST)
	{
		nextPosition.y = player->position.y;
		nextPosition.x = player->position.x + 1;
	}

	else if (player->direction == SOUTH)
	{
		nextPosition.y = player->position.y + 1;
		nextPosition.x = player->position.x;
	}

	else if (player->direction == WEST)
	{
		nextPosition.y = player->position.y;
		nextPosition.x = player->position.x - 1;
	}
	return nextPosition;
}

/*Set the player's position to the provided position. Also increment the
* moves count.*/
void updatePosition(Player * player, Position position)
{   /* TODO */
	player->position.y = position.y;
	player->position.x = position.x;

	player->moves++;
}

/*Prints the direction arrow to the console - based upon the direction set*/
void displayDirection(Direction direction)
{ 
	switch (direction)
	{
	case NORTH:
		printf("%s", DIRECTION_ARROW_OUTPUT_NORTH);
		break;

	case EAST:
		printf("%s", DIRECTION_ARROW_OUTPUT_EAST);
		break;

	case SOUTH:
		printf("%s", DIRECTION_ARROW_OUTPUT_SOUTH);
		break;

	case WEST:
		printf("%s", DIRECTION_ARROW_OUTPUT_WEST);
		break;

	default:
		printf("p");
	}
}
