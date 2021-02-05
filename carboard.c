#include "carboard.h"
#include "board.h"
#include "board.c"
#include "game.c"
#include "player.c"
#include "helpers.c"

int main()
{
	/*[sscanf_example.c@wk3 rmit]*/
	char userInput1[LINE_LIMIT + MARGIN];
	while (1)
	{
		/*Car board menu print*/
		printf("      Welcome to Car Board      \n");
		printf("--------------------------------\n");
		printf("1. Play game.\n2. Show student's information.\n3. Quit.\n\n");
		printf("Please enter your choice: \n");

		fgets(userInput1, LINE_LIMIT + MARGIN, stdin);

		/* check for buffer overflow [sscanf_example.c@wk3 rmit]*/
		if (userInput1[strlen(userInput1) - 1] != '\n')
		{
			printf("Error: Invalid Input\n\n");
			readRestOfLine();
		}

		else
		{
			/* remove newline [sscanf_example.c@wk3 rmit]*/
			userInput1[strlen(userInput1) - 1] = 0;

			/* Car board menu selection */
			switch (userInput1[0])
			{
			case '1':
				playGame();
				break;

			case '2':
				showStudentInformation();
				break;

			case '3':
				printf("You have chosen %c \n", userInput1[0]);
				printf("Good bye! \n\n");
				return EXIT_SUCCESS;
				break;

			default:
				printf("Error: Invalid input\n\n");
				readRestOfLine();
				break;
			}
		}
	}
}


/*Main menu option 2
- show your student information as per the specification.
* You should change the defines above related to student information and use
* them when printing.*/
void showStudentInformation()
{   /* TODO */
	printf("--------------------------------\n");
	printf("Name: %s\n", STUDENT_NAME);
	printf("No: %s\n", STUDENT_ID);
	printf("Email: %s\n", STUDENT_EMAIL);
	printf("--------------------------------\n\n");
}
