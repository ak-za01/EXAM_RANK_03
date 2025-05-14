/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filter.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anktiri <anktiri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 15:37:04 by anktiri           #+#    #+#             */
/*   Updated: 2025/05/14 06:37:34 by anktiri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *ft_free(char **ptr)
{
    if (ptr && *ptr)
    {
        free(*ptr);
        *ptr = NULL;
    }
    return NULL;
}

char	*join(char *s1, char *s2)
{
	char	*result;
	size_t	i = 0;
	size_t	j = 0;

	if (!s1 || !s2)
		return (NULL);
	if (s1 && !s2)
		return (strdup(s1));
	if (!s1 && s2)
		return (strdup(s2));
	result = calloc(strlen(s1) + strlen(s2) + 1, 1);
	if (!result)
		return (fprintf(stderr, "malloc error\n"), NULL);
	while (s1[i])
	{
		result[i] = s1[i];
		i++;
	}
	while (s2[j])
	{
		result[i + j] = s2[j];
		j++;
	}
	return (result);
}

char	*redline(void)
{
	ssize_t bytes_in_buffer;
    char *buffer = NULL;
    char *line;
    
    bytes_in_buffer = 1;
    buffer = calloc(1, 1);
    if (!buffer)
        return NULL;
    line = calloc(51, 1);
    if (!line)
        return ft_free(&buffer);
    while (bytes_in_buffer > 0) // Removed the check for newline
    {
        bytes_in_buffer = read(0, line, 50);
        if (bytes_in_buffer == -1)
            return (ft_free(&line), ft_free(&buffer));
        line[bytes_in_buffer] = '\0';
        buffer = join(buffer, line);
        if (!buffer)
            return (ft_free(&line), NULL);
        if (bytes_in_buffer == 0) // If we read less than requested, we're at EOF
            break;
    }
    ft_free(&line);
    return buffer;
}

void search(char *str1, const char *str2)
{
	size_t	i;
	size_t	j;

	i = 0;
	if (!*str2)
		return;
	while (str1[i])
	{
		j = 0;
		while (str1[i + j] == str2[j] && str2[j])
			j++;
		if (!str2[j])
		{
			while (j--)
			{
				str1[i + j] = '*';
			}
		}
		i++;
	}
}

void ll(void)
{
	system("leaks ./a.out");
}

int main(int ac, char **av)
{
    char	*str;

	atexit(ll);
	if (ac == 2)
	{
		str = redline();
		search(str, av[1]);
		printf("%s", str);
		return (0);
	}
	return (1);
}
