/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   permutations.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anktiri <anktiri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 07:58:22 by anktiri           #+#    #+#             */
/*   Updated: 2025/05/14 08:24:24 by anktiri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include <string.h>

// Sort string using bubble sort
void sort_string(char *str, int len)
{
    for (int i = 0; i < len - 1; i++)
	{
        for (int j = 0; j < len - i - 1; j++)
		{
            if (str[j] > str[j + 1])
			{
                char temp = str[j];
                str[j] = str[j + 1];
                str[j + 1] = temp;
            }
        }
    }
}

// Generate all permutations using backtracking
void generate_perms(char *src, char *result, int *used, int len, int pos)
{
    if (pos == len)
	{
        write(1, result, len);
        write(1, "\n", 1);
        return;
    }
    
    for (int i = 0; i < len; i++)
	{
        if (!used[i])
		{
            used[i] = 1;
            result[pos] = src[i];
            generate_perms(src, result, used, len, pos + 1);
            used[i] = 0;
        }
    }
}

int main(int argc, char **argv)
{
    if (argc < 2)
        return 1;
    int len = strlen(argv[1]);
    if (len == 0)
        return 0;
    char *src = malloc(len + 1);
    char *result = malloc(len + 1);
    int *used = calloc(len, sizeof(int));
    if (!src || !result || !used)
        return 1;
    strcpy(src, argv[1]);
    result[len] = '\0';
    sort_string(src, len);
    generate_perms(src, result, used, len, 0);
    free(src);
    free(result);
    free(used);
    return 0;
}