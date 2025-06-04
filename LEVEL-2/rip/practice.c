#include <unistd.h>
#include <string.h>
#include <stdio.h>

void	remove_calc(char *str, size_t len, size_t *rem_r, size_t *rem_l)
{
	size_t	balance = 0;

	for (int i = 0; i < len; i++)
	{
		if (str[i] == '(')
			balance++;
		else if (str[i] == ')')
		{
			if (balance == 0)
				(*rem_r)++;
			else
				balance--;
		}
	}
	*rem_l = balance;
	
}

void	generate(char *str, size_t i, char *res, size_t res_pos, size_t rem_r, size_t rem_l, size_t open_count)
{
	if (str[i] == '\0')
	{
		if (rem_l == 0 && rem_r == 0 && open_count == 0)
		{
			res[res_pos] = '\0';
			printf("%s\n", res);
		}
		return;
	}

	// current char is not a parenthesis - just copy it
	if (str[i] != '(' && str[i] != ')')
	{
		res[res_pos] = str[i];
		generate(str, i + 1, res, res_pos + 1, rem_r, rem_l, open_count);
		return ;
	}

	// try removing current parenthesis if we still need to remove some
	if (str[i] == '(' && rem_l > 0)
	{
		res[res_pos] = ' ';
		generate(str, i + 1, res, res_pos + 1, rem_r, rem_l - 1, open_count);
	}
	if (str[i] == ')' && rem_r > 0)
	{
		res[res_pos] = ' ';
		generate(str, i + 1, res, res_pos + 1, rem_r - 1, rem_l, open_count);
	}

	// try keeping current parenthesis
	if (str[i] == '(')
	{
		res[res_pos] = '(';
		generate(str, i + 1, res, res_pos + 1, rem_r, rem_l, open_count + 1);
	}
	if (str[i] == ')' && open_count > 0)
	{
		res[res_pos] = ')';
		generate(str, i + 1, res, res_pos + 1, rem_r, rem_l, open_count - 1);
	}
}

int main(int ac, char **av)
{
	if (ac != 2)
		return 1;
	char *str = av[1];
	char result[255] = {0};
	size_t rem_r = 0;
	size_t rem_l = 0;

	remove_calc(str, strlen(str), &rem_r, &rem_l);
	generate(str, 0, result, 0, rem_r, rem_l, 0);
}