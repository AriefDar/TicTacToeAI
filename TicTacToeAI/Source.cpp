#include <iostream>
using namespace std;

int winCount = 0;
int lostCount = 0;
int tieCount = 0;
int deepestDepth = 0;
bool MovesLeft(char board[3][3])
{
	int count = 0;
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			if (board[i][j] == '.')
			{
				count++;
			}
		}
	}
	if (count > 0)
	{
		return true;
	}
	return false;
}
void DisplayBoard(char board[3][3])
{
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			cout << board[i][j];
		}
		cout << endl;
	}
	cout << endl;
}
int EvaluateBoard(char board[3][3])
{
	//Check Horizontal
	for (int i = 0; i < 3; i++)
	{
		if (board[i][0] == 'x' && board[i][1] == 'x' && board[i][2] == 'x')
		{
			return 10;
		}
		else if (board[i][0] == 'o' && board[i][1] == 'o' && board[i][2] == 'o')
		{
			return -10;
		}
	}

	//Check Vertical
	for (int i = 0; i < 3; i++)
	{
		if (board[0][i] == 'x' && board[1][i] == 'x' && board[2][i] == 'x')
		{
			return 10;
		}
		else if (board[0][i] == 'o' && board[1][i] == 'o' && board[2][i] == 'o')
		{
			return -10;
		}
	}

	//Check Diagonal
	if (board[0][0] == 'x' && board[1][1] == 'x' && board[2][2] == 'x')
	{
		return 10;
	}
	else if (board[2][0] == 'x' && board[1][1] == 'x' && board[0][2] == 'x')
	{
		return 10;
	}
	else if (board[0][0] == 'o' && board[1][1] == 'o' && board[2][2] == 'o')
	{
		return -10;
	}
	else if (board[2][0] == 'o' && board[1][1] == 'o' && board[0][2] == 'o')
	{
		return -10;
	}

	//Nothing else
	return 0;
}
int Max(int a, int b)
{
	if (a > b)
	{
		return a;
	}
	return b;
}
int Min(int a, int b)
{
	if (a < b)
	{
		return a;
	}
	return b;
}
int Minimax(char board[3][3], int depth, bool isComputerTurn)
{
	//Check if there is available move
	int score = EvaluateBoard(board);

	//Computer Wins
	if (score == 10)
	{
		winCount++;
		//deepestDepth = Max(deepestDepth, depth);
		return score - depth;
	}

	//Human Wins
	if (score == -10)
	{
		lostCount++;
		//deepestDepth = Max(deepestDepth, depth);
		return score + depth;
	}

	//Check Available Moves
	if (!MovesLeft(board))
	{
		tieCount++;
		//deepestDepth = Max(deepestDepth, depth);
		return 0;
	}

	int best = 0;
	if (isComputerTurn)	//Maximizing 
	{
		best = -1000;
		for (int i = 0; i < 3; i++)
		{
			for (int j = 0; j < 3; j++)
			{
				//Check Empty Cells
				if (board[i][j] == '.')
				{
					board[i][j] = 'x';
					best = Max(best, Minimax(board, depth + 1, false));
					board[i][j] = '.';
				}
			}
		}
	}
	else			   //Minimizing
	{
		best = 1000;
		for (int i = 0; i < 3; i++)
		{
			for (int j = 0; j < 3; j++)
			{
				//Check Empty Cells
				if (board[i][j] == '.')
				{
					board[i][j] = 'o';
					best = Min(best, Minimax(board, depth + 1, true));
					board[i][j] = '.';
				}
			}
		}
	}
	return best;
}
int main()
{
	char board[3][3] = { {'.', '.', '.'},
						 {'.', '.', '.'},
						 {'.', '.', '.'} };

	int state = 0;		//0 = Human, 1 = Computer
	int row = 0;
	int col = 0;
	while (true)
	{
		cout << EvaluateBoard(board) << endl;
		if (EvaluateBoard(board) != 0 || !MovesLeft(board))
		{		
			DisplayBoard(board);
			break;
		}
		DisplayBoard(board);
		if (state == 0)
		{
			cout << "Row: "; cin >> row;
			cout << "Col: "; cin >> col;
			if (board[row][col] == '.')
			{
				board[row][col] = 'o';
				state = 1;
			}
			else
			{
				cout << "Invalid Move" << endl;
			}
		}
		else if (state == 1)
		{
			int moveValue = -999;
			int bestValue = -1000;
			int bestValue_row = -1;
			int bestValue_col = -1;
			for (int i = 0; i < 3; i++)
			{
				for (int j = 0; j < 3; j++)
				{
					//Check Empty Cells
					if (board[i][j] == '.')
					{
						board[i][j] = 'x';
						moveValue = Minimax(board, 1, false);
						board[i][j] = '.';
						
						/*cout << "Win: " << winCount << endl;
						cout << "Lost: " << lostCount << endl;
						cout << "Tie: " << tieCount << endl;*/
						moveValue = moveValue + winCount - lostCount;
						//cout << i << " " << j << " " << moveValue << endl;
						winCount = 0;
						lostCount = 0;
						tieCount = 0;
					}
					
					

					//Find a best value
					if (moveValue > bestValue)
					{
						bestValue = moveValue;
						bestValue_row = i;
						bestValue_col = j;
					}
				}
			}
			board[bestValue_row][bestValue_col] = 'x';
			state = 0;
			/*int i = 0;
			int j = 0;
			if (board[i][j] == '.')
			{
				board[i][j] = 'x';
				int moveValue = Minimax(board, 0, false);
				board[i][j] = '.';
				cout << i << " " << j << " " << moveValue << endl;
			}
			cout << "Deepest Depth: " << deepestDepth << endl;
			state = 0;*/
		}
	}
	return 0;
}