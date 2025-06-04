/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rip.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anktiri <anktiri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 04:11:34 by anktiri           #+#    #+#             */
/*   Updated: 2025/06/04 04:11:36 by anktiri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void	min_removals(char *input, size_t inputLen, size_t *rem_l, size_t *rem_r)
{
	size_t balance = 0;
	size_t i = 0;

	while (i < inputLen)
	{
		if (input[i] == '(')
			balance++;
		else if (input[i] == ')')
		{
			if (balance == 0)
				(*rem_r)++;
			else
				balance--;
		}
		i++;
	}
	*rem_l = balance;
}

void	rip(char *input, size_t i, char *result, size_t resultLen, size_t rem_l, size_t rem_r, int open)
{
	// finish
	if (input[i] == '\0')
	{
		if (rem_l == 0 && rem_r == 0 && open == 0)
		{
			result[resultLen] = '\0';
			printf("%s\n", result);
		}
		return ;
	}
	// not a para
	if (input[i] != '(' && input[i] != ')')
	{
		result[resultLen] = input[i];
		rip(input, i + 1, result, resultLen + 1, rem_l, rem_r, open);
		return ;
	}
	// remove
	if (input[i] == '(' && rem_l > 0)
	{
		result[resultLen] = '_';
		rip(input, i + 1, result, resultLen + 1, rem_l - 1, rem_r, open);
	}
	if (input[i] == ')' && rem_r > 0)
	{
		result[resultLen] = '_';
		rip(input, i + 1, result, resultLen + 1, rem_l, rem_r - 1, open);
	}
	// keep
	if (input[i] == '(')
	{
		result[resultLen] = '(';
		rip(input, i + 1, result, resultLen + 1, rem_l, rem_r, open + 1);
	}
	if (input[i] == ')' && open > 0)
	{
		result[resultLen] = ')';
		rip(input, i + 1, result, resultLen + 1, rem_l, rem_r, open - 1);
	}
}

int main(int ac, char *av[])
{
	if (ac != 2)
		return 1;
	char *input = av[1];
	size_t inputLen = strlen(input);
	char result[255] = {0};
	size_t resultLen = 0;
	size_t rem_l = 0;
	size_t rem_r = 0;

	min_removals(input, inputLen, &rem_l, &rem_r);

	rip(input, 0, result, resultLen, rem_l, rem_r, 0);
}
