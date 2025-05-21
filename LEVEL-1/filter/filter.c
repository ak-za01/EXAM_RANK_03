/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   small_filter.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anktiri <anktiri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 06:10:08 by anktiri           #+#    #+#             */
/*   Updated: 2025/05/21 06:10:09 by anktiri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>

int	ft_strlen(char *str)
{
	int	a = 0;

	if (!str)
		return 0;
	while (str[a])
	{
		a++;
	}
	return (a);
}

char	*ft_strdup(char *str)
{
	char	*result;
	int		a = 0;

	result = malloc(ft_strlen(str));
	if (!result)
		return NULL;
	while (str[a])
	{
		result[a] = str[a];
		a++;
	}
	result[a] = '\0';
	return (result);
}

char	*getline()
{
	char	buffer[5000];
	char	line[5000];
	int		bytes = 0;
	int		pos = 0;
	int		a = 0;

	while (1)
	{
		if (pos >= bytes)
		{
			bytes = read(0, buffer, 5000);
			if (bytes <= 0)
			{
				if(bytes < 0)
					return NULL;
				break ;
			}
			pos = 0;
		}
		line[a++] = buffer[pos++];
	}
	line[a] = '\0';
	if (a == 0)
		return NULL;
	return (ft_strdup(line));
}

void	search(char *str, char *target)
{
	int	a = 0;
	int	b;

	if (!*target)
		return ;
	while (str[a])
	{
		b = 0;
		while (str[a + b] == target[b] && target[b])
			b++;
		if (!target[b])
		{
			while (b--)
			{
				str[a + b] = '*';
			}
		}
		a++;
	}
}

int main(int ac, char **av)
{
	char	*line;

	if (ac == 2)
	{
		line = getline();
		search(line, av[1]);
		write(1, line, ft_strlen(line));
	}
	write(1, "\n", 1);
}