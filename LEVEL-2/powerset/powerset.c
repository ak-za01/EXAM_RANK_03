/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   powerset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anktiri <anktiri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 10:22:24 by anktiri           #+#    #+#             */
/*   Updated: 2025/06/04 10:29:05 by anktiri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>

void	subset(int target, int numbers, int *res, int *nums, int index, int size, int sum)
{
	if (index == numbers)
	{
		if (sum == target)
		{
			for (int i = 0; i < size; i++)
			{
				printf("%d", res[i]);
				if (i < size - 1)
					printf(" ");
			}
			printf("\n");
		}
		return ;
	}
	subset(target, numbers, res, nums, index + 1, size, sum);
	res[size] = nums[index];
	subset(target, numbers, res, nums, index + 1, size + 1, sum + nums[index]);
}


int main(int ac, char **av)
{
	if (ac < 2)
		return 1;
	int target = atoi(av[1]);
	int numbers = ac - 2;
	int *nums = malloc(numbers * sizeof(int));
	int *res = malloc(numbers * sizeof(int));
	if (!nums || !res)
		return 1;
	for (int i = 0; i < numbers; i++)
		nums[i] = atoi(av[i + 2]);
	subset(target, numbers, res, nums, 0, 0, 0);
	free(nums);
	free(res);
	return 0;	
}
