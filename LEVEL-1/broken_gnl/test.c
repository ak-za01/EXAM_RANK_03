#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>

#ifndef BUFFER_SIZE
# define BUFFER_SIZE 1337
#endif

char	*ft_strdup(char *str)
{
	char	*res;
	int		a = -1;

	res = malloc(strlen(str) + 1);
	if (!res)
		return NULL;
	while (str[++a])
		res[a] = str[a];
	res[a] = '\0';
	return res;
}

char	*get_next_line(int fd)
{
	static char	buffer[BUFFER_SIZE];
	static int	bytes;
	static int	pos;
	char			line[60000];
	int			a = 0;

	while (1)
	{
		if (pos >= bytes)
		{
			bytes = read(fd, buffer, BUFFER_SIZE);
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

#include <fcntl.h>
#include <stdio.h>

int main()
{
	char *line;
	int	fd = open("test", O_RDWR);
	for (int i = 0; (line = get_next_line(fd)); i++)
	{
		printf("line[%d]: %s", i, line);
	}
	
	// printf("___line 1____: %s", get_next_line(0));
	// printf("___line 2____: %s", get_next_line(0));
}
