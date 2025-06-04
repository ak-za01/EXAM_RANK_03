#include <stdlib.h>
#include <stdio.h>

void	find_subset(int target, int num, int *res, int *nums, int index, int size, int sum)
{
	if (index == num)
	{
		if (sum == target)
		{
			for (int i = 0; i < size; i++)
			{
				if (i > 0)
					printf(" ");
				printf("%d", res[i]);
			}
			printf("\n");
		}
		return ;
	}
	find_subset(target, num, res, nums, index + 1, size, sum);
	res[size] = nums[index];
	find_subset(target, num, res, nums, index + 1, size + 1, sum + nums[index]);
}

int main(int ac, char **av)
{
	if (ac < 2)
		return 1;
	int	target = atoi(av[1]);
	int	num = ac - 2;
	int	*nums = malloc(num * sizeof(int));
	int *res = malloc(num * sizeof(int));
	if (!nums || !res)
		return 1;
	for (int i = 0; i < num; i++)
		nums[i] = atoi(av[i + 2]);
	find_subset(target, num, res, nums, 0, 0, 0);
	free(nums);
	free(res);
}
