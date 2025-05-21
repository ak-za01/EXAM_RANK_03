#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <string.h>

#ifndef BUFFER_SIZE
# define BUFFER_SIZE 42
#endif

char	*ft_strdup(char *str)
{
	char	*result;
	int		a = -1;

	result = malloc(strlen(str) + 1);
	if (!result)
		return NULL;
	while (str[++a])
		result[a] = str[a];
	result[a] = '\0';
	return result;
}

char	*get_next_line(int fd)
{
	static char	buffer[BUFFER_SIZE];
	static int	bytes;
	static int	pos;
	char		line[500000];
	int			a = 0;

	while (1)
	{
		if (pos >= bytes)
		{
			bytes = read(fd, buffer, BUFFER_SIZE);
			pos = 0;
			if (bytes <= 0)
			{
				if (bytes < 0)
					return NULL;
				break ;
			}
		}
		line[a++] = buffer[pos++];
		if (buffer[pos - 1] == '\n')
			break;
	}
	line[a] = '\0';
	if (a == 0)
		return (NULL);
	return (ft_strdup(line));
}

int main()
{
	char *line;
	int	fd = open("test", O_RDWR);
	// for (int i = 0; (line = get_next_line(fd)) && i < 1; i++)
	// {
	// 	printf("line[%d]: %s", i, line);
	// }
	
	printf("___line 1____: %s", get_next_line(0));
	printf("___line 2____: %s", get_next_line(0));
}