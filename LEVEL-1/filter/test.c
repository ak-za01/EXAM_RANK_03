#include <unistd.h>
#include <stdlib.h>

int	ft_strlen(char *str)
{
	int	i = 0;

	if (!str)
		return 0;
	while (str[i])
	{
		i++;
	}
	return i;
}

char	*ft_strdup(char *str)
{
	char	*res;
	int		a = -1;

	if (!str)
		return NULL;
	res = malloc(ft_strlen(str) + 1);
	if (!res)
		return NULL;
	while (str[++a])
	{
		res[a] = str[a];
	}
	res[a] = '\0';
	return res;
}

char	*redline()
{
	char	buffer[50000];
	char	line[50000];
	int		bytes = 0;
	int		pos = 0;
	int		a = 0;

	while (1)
	{
		if (pos >= bytes)
		{
			bytes = read(0, buffer, 50000);
			if (bytes <= 0)
			{
				if (bytes < 0)
					return NULL;
				break ;
			}
			pos = 0;
		}
		line[a++] = buffer[pos++];
		if (buffer[pos - 1] == '\n')
			break ;
	}
	line[a] = '\0';
	if (a == 0)
		return NULL;
	return ft_strdup(line);
}

void	search(char *str, char *target)
{
	int	b, a = 0;

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
		while ((line = redline())
		{
			search(line, av[1]);
			write(1, line, ft_strlen(line));
			free(line);
		}
		return (0);
	}
	write(1, "\n", 1);
}
