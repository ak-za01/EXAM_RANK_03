/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   n_queens.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anktiri <anktiri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 05:05:45 by anktiri           #+#    #+#             */
/*   Updated: 2025/05/14 07:00:25 by anktiri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>

void	print_solution(int *board, int size)
{
	int	i;

	i = 0;
	while (i < size)
	{
		fprintf(stdout, "%d", board[i]);
		if (i < size - 1)
			fprintf(stdout, " ");
		i++;
	}
	fprintf(stdout, "\n");
}

int	valid(int *board, int row, int col)
{
	int	i;

	i = 0;
	while (i < row)
	{
		if (col == board[i] || (board[i] - col == i - row) || 
			(board[i] - col == row - i))
			return (0);
		i++;
	}
	return (1);
}

void	solve(int size, int *board, int row)
{
	int	col;

	if (row == size)
	{
		print_solution(board, size);
		return ;
	}
	col = 0;
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

int	main(int ac, char **ar)
{
	int		size;
	int		*board;
	int		i;

	if (ac < 2)
		return 1;
	i = 0;
	size = atoi(ar[1]);
	board = malloc(size * sizeof(int));
	if (!board)
		return 1;
	while (i < size)
	{
		board[i] = 0;
		i++;
	}
	solve(size, board, 0);
	free(board);
	return (0);
}
