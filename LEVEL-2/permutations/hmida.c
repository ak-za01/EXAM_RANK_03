#include <stdio.h>

int permute(char *perm, int n)
{
	int i = n - 1;
	int j = n;
	char tmp;

	while (i > 0 && perm[i] <= perm[i - 1])
		i--;
	if (i <= 0)
		return 0;
	while (j > i && perm[i - 1] >= perm[j - 1])
		j--;
	tmp = perm[i - 1];
	perm[i - 1] = perm[j - 1];
	perm[j - 1] = tmp;
	i++;
	j = n;
	while (j > i)
	{
		tmp = perm[i - 1];
		perm[i - 1] = perm[j - 1];
		perm[j - 1] = tmp;
		i++;
		j--;
	}
	return 1;
}

void sort(char *str, int len)
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

int main (int ac, char **av)
{
	if (ac != 2)
		return 0;
	char *perm = av[1];
	int i = 0;
	while (perm[i])
		i++;
	sort(perm, i);
	printf("%s\n", perm);
	while (permute(perm, i))
	{
		printf("%s\n", perm);
	}
}
