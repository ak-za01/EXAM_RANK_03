/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   permutations.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anktiri <anktiri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 09:50:45 by anktiri           #+#    #+#             */
/*   Updated: 2025/06/04 09:58:42 by anktiri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>

void	sort(char *str, int len)
{
	for (int i = 0; i < len - 1; i++)
	{
		for (int j = i + 1; j < len; j++)
		{
			if (str[i] > str[j])
			{	
				char c = str[i];
				str[i] = str[j];
				str[j] = c;
			}
		}
	}
}

void	permute(char *str, char *res, int *use, int len, int depth)
{
	if (depth == len)
	{
		puts(res);
		return ;
	}
	for (int i = 0; i < len; i++)
	{
		if (use[i])
			continue;
		use[i] = 1;
		res[depth] = str[i];
		permute(str, res, use, len, depth + 1);
		use[i] = 0;
	}
	
}

int main(int ac, char **av)
{
	if (ac != 2)
		return 1;
	int len = 0;
	while (av[1][len])
		len++;
	int	*use = calloc(len, sizeof(int));
	char *res = malloc(len + 1);
	if (!use || !res)
		return 1;
	sort(av[1], len);
	permute(av[1], res, use, len, 0);
}
