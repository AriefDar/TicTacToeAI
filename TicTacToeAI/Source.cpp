#include <iostream>
#include <limits>
using namespace std;

#define POS_INFINITY INT_MAX
#define NEG_INFINITY INT_MIN

int winCount = 0;
int lostCount = 0;
int tieCount = 0;
int deepestDepth = 0;
int count = 0;
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
	::count++;
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
		best = NEG_INFINITY;
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
		best = POS_INFINITY;
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

int MinimaxAlphaBeta(char board[3][3], int depth, bool isComputerTurn, int alpha, int beta)
{
	::count++;
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
		best = NEG_INFINITY;
		bool cut = false;
		for (int i = 0; i < 3; i++)
		{
			for (int j = 0; j < 3; j++)
			{
				//Check Empty Cells
				if (board[i][j] == '.')
				{
					int eval = 0;
					board[i][j] = 'x';
					eval = MinimaxAlphaBeta(board, depth + 1, false, alpha, beta);
					board[i][j] = '.';
					best = Max(best, eval);
					alpha = Max(alpha, eval);
					if (beta <= alpha)
					{
						cut = true;
					}
				}
				if (cut)
				{
					break;
				}
			}
			if (cut)
			{
				break;
			}
		}
	}
	else			   //Minimizing
	{
		best = POS_INFINITY;
		bool cut = false;
		for (int i = 0; i < 3; i++)
		{
			for (int j = 0; j < 3; j++)
			{
				//Check Empty Cells
				if (board[i][j] == '.')
				{
					int eval = 0;
					board[i][j] = 'o';
					eval = Min(best, MinimaxAlphaBeta(board, depth + 1, true, alpha, beta));
					board[i][j] = '.';
					best = Min(best, eval);
					beta = Min(beta, eval);
					if (beta <= alpha)
					{
						cut = true;
					}
				}
				if (cut)
				{
					break;
				}
			}
			if (cut)
			{
				break;
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
		//cout << EvaluateBoard(board) << endl;
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
				
			}
			else
			{
				cout << "Invalid Move" << endl;
			}
			state = 1;
		}
		else if (state == 1)
		{
			cout << "Computer Turns" << endl;
			::count = 0;
			int moveValue = POS_INFINITY;
			int bestValue = NEG_INFINITY;
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
						//moveValue = Minimax(board, 1, false);
						moveValue = MinimaxAlphaBeta(board, 1, false, NEG_INFINITY, POS_INFINITY);
						board[i][j] = '.';
						
						//moveValue = moveValue + winCount - lostCount;
						cout << "Move Value: " << moveValue << " Row: " << i << " Col: " << j << endl;
						winCount = 0;
						lostCount = 0;
						tieCount = 0;
						//Find a best value
						if (moveValue > bestValue)
						{
							cout << "Move Value to Best: " << moveValue << endl;
							bestValue = moveValue;
							bestValue_row = i;
							bestValue_col = j;
						}
					}
					
					
				}
			}
			cout << "Global Count: " << ::count << endl;
			::count = 0;
			cout << "Computer Move: " << bestValue_row << " " << bestValue_col << endl;
			board[bestValue_row][bestValue_col] = 'x';
			state = 0;
		}
	}
	return 0;
}