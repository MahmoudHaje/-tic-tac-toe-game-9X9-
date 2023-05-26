#include <stdio.h>
#include <stdlib.h>
#define PLAYER1 2
#define PLAYER2 3
#define INVALID -1
#define MIN_INDEX 1
#define ERROR -2
#define N 9
#define TIE 1
#define EMPTY ' '
#define SUB_SIZE 3
#define NOBODY 0
#define SUB_NUM 3
#define ItIsTie 4

/*I used two arrays, first the BOARD[N][N], and the winner in sub_index in BOARD I transferd it to the ARR[SUB_SIZE][SUB_SIZE],
the winner in the game, is the winner in the ARR*/

void print_board_2(char board[N][N]);
// function lenght = 5
//this function convert the number of player to char
//player1 geT X, player2 get O
char player_to_char(int player)
{
	switch (player)
	{
	case PLAYER1:  return 'X';
	case PLAYER2:  return 'O';
	case EMPTY:  return ' ';
	case ItIsTie: return 't';
	}
	return '!';
}

//function lenght = 1
//function to get the first row in the sub_index
int get_sub_row(int sub_index)
{
	return ((sub_index - 1) / SUB_NUM) * SUB_SIZE;
}

//function lenght = 1
//function to get the first col in the sub_index
int get_sub_col(int sub_index)
{
	return ((sub_index - 1) % SUB_NUM) * SUB_SIZE;
}

//function lenght = 15
//function to check if the chosing postion is valid
int to_check_if_number_is_valid(char board[N][N], int safeChoise, int getROW, int getCol)
{
	char charSafechoise = safeChoise;
	while ((safeChoise>9 || safeChoise<1) ||
		(charSafechoise >= 'a' && charSafechoise <= 'z') || (charSafechoise >= 'A' && charSafechoise <= 'Z'))
	{
		if ((charSafechoise >= 'a' && charSafechoise <= 'z') || (charSafechoise >= 'A' && charSafechoise <= 'Z'))
		{
			printf("You entered a letter! You must enter a number!---GAME OVER");
			exit(0);
		}
		printf("Index out of range. Please enter a value between 1 and 9: \n");
		scanf("%d", &safeChoise);
		charSafechoise = safeChoise;
	}
	while (board[(safeChoise - 1) / 3 + getROW][(safeChoise - 1) % 3 + getCol] == 'O' ||
		board[(safeChoise - 1) / 3 + getROW][(safeChoise - 1) % 3 + getCol] == 'X')
	{
		printf("Position is taken, please choose another one: \n");
		scanf("%d", &safeChoise);
		charSafechoise = safeChoise;
		while ((safeChoise>9 || safeChoise<1) ||
			(charSafechoise >= 'a' && charSafechoise <= 'z') || (charSafechoise >= 'A' && charSafechoise <= 'Z'))
		{
			if ((charSafechoise >= 'a' && charSafechoise <= 'z') || (charSafechoise >= 'A' && charSafechoise <= 'Z'))
			{
				printf("You entered a letter! You must enter a number!---GAME OVER");
				exit(0);
			}
			printf("Index out of range. Please enter a value between 1 and 9: \n");
			scanf("%d", &safeChoise);
			charSafechoise = safeChoise;
		}
	}
	return safeChoise;
}

//function lenght = 8
//function to check if the wanted subbord if full(all postions are taken)
bool is_sub_board_full(char board[N][N], int sub_index)
{
	int sub_row = get_sub_row(sub_index);
	int sub_col = get_sub_col(sub_index);
	for (int i = sub_row; i<sub_row + SUB_SIZE; i++)
	{
		for (int j = sub_col; j<sub_col + SUB_SIZE; j++)
		{
			if (board[i][j] != 'X' && board[i][j] != 'O')
				return false;
		}
	}
	return true;
}

//function lenght = 7
//function that retrun true or flase if the the subbord postion are similar in Horizontal way
bool Horizontal_check(char board[N][N], int sub_index)
{
	int m = get_sub_row(sub_index);
	int n = get_sub_col(sub_index);
	for (int i = 0; i < SUB_NUM; i++)
	{
		if (board[m + i][n] == board[m + i][n + 1] &&
			board[m + i][n + 1] == board[m + i][n + 2] && board[m + i][n] == 'O')
			return true;
		if (board[m + i][n] == board[m + i][n + 1] &&
			board[m + i][n + 1] == board[m + i][n + 2] && board[m + i][n] == 'X')
			return true;
	}
	return false;
}

//function lenght = 7
//function that retrun true or flase if the the subbord postion are similar in Vertical way
bool Vertical_check(char board[N][N], int sub_index)
{
	int m = get_sub_row(sub_index);
	int n = get_sub_col(sub_index);
	for (int i = 0; i < SUB_NUM; i++)
	{
		if (board[m][n + i] == board[m + 1][n + i] &&
			board[m + 1][n + i] == board[m + 2][n + i] && board[m][n + i] == 'O')
			return true;
		if (board[m][n + i] == board[m + 1][n + i] &&
			board[m + 1][n + i] == board[m + 2][n + i] && board[m][n + i] == 'X')
			return true;
	}
	return false;
}

//function lenght = 5
//function that retrun true or flase if the the subbord postion are similar in Diagonal way
bool Diagonal_check(char board[N][N], int sub_index)
{
	int n = get_sub_col(sub_index);
	int m = get_sub_row(sub_index);
	if ((board[m][n] == board[m + 1][n + 1] && board[m + 1][n + 1] == board[m + 2][n + 2] && board[m][n] == 'X') ||
		(board[m][n + 2] == board[m + 1][n + 1] && board[m + 1][n + 1] == board[m + 2][n] && board[m][n + 2] == 'X')) {
		return true;
	}
	if ((board[m][n] == board[m + 1][n + 1] && board[m + 1][n + 1] == board[m + 2][n + 2] && board[m][n] == 'O') ||
		(board[m][n + 2] == board[m + 1][n + 1] && board[m + 1][n + 1] == board[m + 2][n] && board[m][n + 2] == 'O')) {
		return true;
	}
	return false;
}

//function lenght = 6
//function the number of the player that won in the subbord
int If_he_win_in_subboard(char board[N][N], int sub_index, int player)
{
	bool x, y, z;
	x = Horizontal_check(board, sub_index);
	y = Vertical_check(board, sub_index);
	z = Diagonal_check(board, sub_index);
	if (x == true || y == true || z == true)
		return player;
	return NOBODY;
}

//function lenght = 6
/*function that return true if the subbindex that is in BOARD is ending in 'X' winnig, or 'O' winning ,or tie.
that mean u cant play in that subboard*/
bool index_in_arr(char arr[SUB_SIZE][SUB_SIZE], int sub_index)
{
	int column = sub_index % 3;
	int row = sub_index / 3;
	if (column == 0)
	{
		column += 3;
		row -= 1;
	}
	if (arr[row][column - 1] == 'X' || arr[row][column - 1] == 'O')
		return true;
	return false;
} 

//function lenght = 5
//function that putting in arr the player who won in specif subbord
void scanning_on_arr(char arr[SUB_SIZE][SUB_SIZE], int win_sub, int player)
{
	int column = win_sub % 3;
	int row = win_sub / 3;
	if (column == 0)
	{
		column += 3;
		row -= 1;
	}
	arr[row][column - 1] = player_to_char(player);
}

//function lenght = 12
//function that put in BOARD 'X' or 'O' in the postion that the player chose 
int scanning_on_board(char board[N][N], int sub_index, int player, char arr[SUB_SIZE][SUB_SIZE])
{
	int getROW = get_sub_row(sub_index);
	int getCol = get_sub_col(sub_index);
	int safeChoise;
	printf("Please enter your choice\n");
	scanf("%d", &safeChoise);
	safeChoise = to_check_if_number_is_valid(board, safeChoise, getROW, getCol);
	board[(safeChoise - 1) / 3 + getROW][(safeChoise - 1) % 3 + getCol] = player_to_char(player);
	print_board_2(board);
	if (If_he_win_in_subboard(board, sub_index, player) == player)
	{
		scanning_on_arr(arr, sub_index, player);
		printf("player %c has won in subborad %d \n", player_to_char(player), sub_index);
	}
	else
		if (is_sub_board_full(board, sub_index) == true)
			scanning_on_arr(arr, sub_index, ItIsTie);
	return safeChoise;
}
//function lenght = 11
//function that checking if player 'O' can play in sub_index(valid index)
int player_O_chosing(char board[N][N], int sub_index, char arr[SUB_SIZE][SUB_SIZE])// PLAYERR 2 IS O
{
	while (is_sub_board_full(board, sub_index) == true || index_in_arr(arr, sub_index) == true)
	{
		if (index_in_arr(arr, sub_index) == true)
		{
				printf("player has won in this subboard (%d) plz chose onther subbord\n", sub_index);
			scanf("%d", &sub_index);
		}
		else
		{
			printf("Sub-board %d is full. Please choose another one:\n", sub_index);
			scanf("%d", &sub_index);
		}
		char charSub_index = sub_index;
		while ((sub_index>9 || sub_index<1) ||
			(charSub_index >= 'a' && charSub_index <= 'z') || (charSub_index >= 'A' && charSub_index <= 'Z'))
		{
			if ((charSub_index >= 'a' && charSub_index <= 'z') || (charSub_index >= 'A' && charSub_index <= 'Z'))
			{
				printf("You entered a letter! You must enter a number!---GAME OVER");
				exit(0);
			}
			printf("Index out of range. Please enter a value between 1 and 9: \n");
			scanf("%d", &sub_index);
			charSub_index = sub_index;
		}
	}
	return scanning_on_board(board, sub_index, PLAYER2, arr);
}

//function lenght = 11
//function that checking if player 'X' can play in sub_index(valid index)
int player_X_chosing(char board[N][N], int sub_index, char arr[SUB_SIZE][SUB_SIZE]) //PLAYERR 1 IS X
{
	while (is_sub_board_full(board, sub_index) == true || index_in_arr(arr, sub_index) == true)
	{
		if (index_in_arr(arr, sub_index) == true)
		{
			printf("player has won in this subboard plz (%d) chose onther subbord\n", sub_index);
			scanf("%d", &sub_index);
		}
		else
		{
			printf("Sub-board %d is full. Please choose another one:\n", sub_index);
			scanf("%d", &sub_index);
		}
		char charSub_index = sub_index;
		while ((sub_index>9 || sub_index<1) ||
			(charSub_index >= 'a' && charSub_index <= 'z') || (charSub_index >= 'A' && charSub_index <= 'Z'))
		{
			if ((charSub_index >= 'a' && charSub_index <= 'z') || (charSub_index >= 'A' && charSub_index <= 'Z'))
			{
				printf("You entered a letter! You must enter a number!---GAME OVER");
				exit(0);
			}
			printf("Index out of range. Please enter a value between 1 and 9: \n");
			scanf("%d", &sub_index);
			charSub_index = sub_index;
		}
	}
	return scanning_on_board(board, sub_index, PLAYER1, arr);
}
//function lenght = 3
//function that retrun true or flase if the the arr postion are similar in Horizontal way
bool HorizontalCheck_for_arr(char arr[SUB_SIZE][SUB_SIZE])
{
	for (int i = 0; i < SUB_SIZE; i++)
	{
		if (arr[i][0] == arr[i][1] && arr[i][1] == arr[i][2] && arr[i][0] == 'X')
			return true;
		if (arr[i][0] == arr[i][1] && arr[i][1] == arr[i][2] && arr[i][0] == 'O')
			return true;
	}
	return false;
}

//function lenght = 3
//function that retrun true or flase if the the arr postion are similar in  Vertical way
bool VerticalCheck_for_arr(char arr[SUB_SIZE][SUB_SIZE])
{
	for (int i = 0; i < SUB_SIZE; i++)
	{
		if (arr[0][i] == arr[1][i] && arr[1][i] == arr[2][i] && arr[0][i] == 'X')
			return true;
		if (arr[0][i] == arr[1][i] && arr[1][i] == arr[2][i] && arr[0][i] == 'O')
			return true;
	}
	return false;
}

//function lenght = 5
//function that return true if any player has won in tic tac toe game
bool If_he_win_in_all_the_game(char arr[SUB_SIZE][SUB_SIZE])
{
	bool x, y;
	x = HorizontalCheck_for_arr(arr);
	y = VerticalCheck_for_arr(arr);
	if (y == true || x == true)
		return true;
	return false;
}

//function lenght = 6
//function that return true if all the postion in BOARD are full(that mean game is full)
bool Game_is_full(char board[N][N])
{
	for (int i = 0; i<N; i++)
	{
		for (int j = 0; j<N; j++)
		{
			if (board[i][j] != 'X' && board[i][j] != 'O')
				return false;
		}
	}
	return true;
}

//function lenght = 1
//function that print welcom messge
void print_welcome_message()
{
	printf("Welcome to Ultimate Tic-Tac-Toe!\n");
}

// following 3 functions print the entire board
//function lenght = 8
void print_hor_border()
{
	printf(" ");
	for (int i = 1; i <= SUB_NUM; i++)
	{
		for (int j = 0; j < 2 * 2 + 3; j++)
		{
			printf("-");
		}
		printf(" ");
	}
	printf("\n");
}
//function lenght = 9
void print_numbers()
{
	printf(" ");
	for (int i = 1; i <= SUB_NUM; i++)
	{
		for (int j = 0; j < SUB_SIZE; j++)
		{
			if (j > 0) printf("  ");
			printf("%d", i);
		}
		printf(" ");
	}
	printf("\n");
}
//function lenght = 15
void print_board_2(char board[N][N])
{
	print_numbers();
	// print board line by line
	for (int i = 0; i < N; i++)
	{
		printf("%d", i - i % 3 + 1);
		for (int j = 0; j < SUB_NUM; j++)
		{
			for (int k = 0; k < SUB_SIZE; k++)
			{
				if (k > 0)
					printf("  ");
				if (board[i][j*SUB_SIZE + k] == 'X' || board[i][j*SUB_SIZE + k] == 'O')
					printf("%c", board[i][j*SUB_SIZE + k]);
				else
					printf(" ");
			}
			if (j < SUB_NUM)
				printf("|");
		}
		printf("%d\n", i - i % 3 + 3);
		if (i % 3 == 2 && i != 8)
			print_hor_border();
	}
	print_numbers();
}

//function lenght = 12
// fucntion that print who is the winner in the tic tac toe
void Declare_who_win(char arr[SUB_SIZE][SUB_SIZE], bool gameisfull)
{
	if (gameisfull == true)
	{
		printf(" THE GAME IN IN TIE");
		return;
	}
	for (int i = 0; i < SUB_SIZE; i++)
	{
		if (arr[i][0] == arr[i][1] && arr[i][1] == arr[i][2] && arr[i][0] == 'X')
		{
			printf("PLAYER X HAS WON THE GAME !\n");
			return;
		}
		if (arr[0][i] == arr[1][i] && arr[1][i] == arr[2][i] && arr[0][i] == 'X')
		{
			printf("PLAYER X HAS WON THE GAME !\n");
			return;
		}
		if (arr[i][0] == arr[i][1] && arr[i][1] == arr[i][2] && arr[i][0] == 'O')
		{
			printf("PLAYER O HAS WON THE GAME !\n");
			return;
		}
		if (arr[0][i] == arr[1][i] && arr[1][i] == arr[2][i] && arr[0][i] == 'O')
		{
			printf("PLAYER O HAS WON THE GAME !\n");
			return;
		}

	}
	printf("it is tie game over\n");
}

//function lenght = 11
/*function that ask the player x(player number 1 ) to chose the sub endex he want
, and the positon he want in that subbindex*/
int the_first_scan(char board[N][N], char arr[SUB_SIZE][SUB_SIZE])
{
	int subindex, chosie;
	printf("Player X, please enter the index of the wanted sub-board: \n");
	scanf("%d", &subindex);

	char charSub_index = subindex;
	while ((subindex>9 || subindex<1) ||
		(charSub_index >= 'a' && charSub_index <= 'z') || (charSub_index >= 'A' && charSub_index <= 'Z'))
	{
		if ((charSub_index >= 'a' && charSub_index <= 'z') || (charSub_index >= 'A' && charSub_index <= 'Z'))
		{
			printf("You entered a letter! You must enter a number!---GAME OVER");
			exit(0);
		}
		printf("Index out of range. Please enter a value between 1 and 9: \n");
		scanf("%d", &subindex);
		charSub_index = subindex;
	}
	printf(" Player X, please enter the wanted position in sub-board %d:\n", subindex);
	return scanning_on_board(board, subindex, PLAYER1, arr);
}

//function lenght
//functio ret true if arr is full(all positon are taken)
bool if_arr_full(char arr[SUB_SIZE][SUB_SIZE])
{
	for (int i = 0; i < SUB_SIZE; i++)
	{
		for (int k = 0; k < SUB_SIZE; k++)
			if (arr[i][k] != 'X' && arr[i][k] != 'O' && arr[i][k] != 't')
				return false;
	}
	return true;
}


int main()
{
	char board[N][N], arr[SUB_SIZE][SUB_SIZE] = { { '0', '0', '0' },{ '0', '0', '0' },{ '0', '0', '0' } };
	int m, n;
	print_welcome_message(); // printing welcome message
	print_board_2(board);  //printng the board
	m = the_first_scan(board, arr); // m got the position that player x want to choose
	while (Game_is_full(board) == false && If_he_win_in_all_the_game(arr) == false && if_arr_full(arr)==false)
	{
		n = player_O_chosing(board, m, arr); // n got the position that player o want to choose
		if (if_arr_full(arr) == true)
			break;
		if (If_he_win_in_all_the_game(arr) == true)
			break;
		if (Game_is_full(board) == true)
			break;
		m = player_X_chosing(board, n, arr); // m got the position that player x want to choose
	}
	Declare_who_win(arr, Game_is_full(board)); //declaring the winner in tic tac toe
	return 0;
}

