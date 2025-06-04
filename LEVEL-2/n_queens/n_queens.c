#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int	valid(int *board, int row, int col)
{
	for (int i = 0; i < row; i++)
	{
		if (col == board[i] || (board[i] - col == i - row) || (board[i] - col == row - i))
			return 0;
	}
	return 1;
	
}

void	solve(int size, int *board, int row)
{
	int col = 0;

	if (row == size)
	{
		for (int i = 0; i < size; i++)
		{
			printf("%d", board[i]);
			if (i < size - 1)
				printf(" ");
		}
		printf("\n");
		return ;
	}
	while (col < size)
	{
		if (valid(board, row, col))
		{
			board[row] = col;
			solve(size, board, row + 1);
		}
		col++;
	}
}

int main(int ac, char **av)
{
	int size;
	int *board;

	if (ac != 2)
		return 1;
	size = atoi(av[1]);
	board = calloc(size, sizeof(int));
	if (!board)
		return 1;
	solve(size, board, 0);
	free(board);
	return 0;
}
