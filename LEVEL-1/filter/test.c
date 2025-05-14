#include <stdlib.h>
#include <string.h>
#include <unistd.h>

char	*readln()
{
	char buffer[4096];
    char *result = calloc(1, 1);
    char *temp;
    int bytes_read;

	result = calloc(1, 1);
	if (!result)
		return NULL;
	while ((bytes_read = read(0, buffer, 4095)) > 0)
	{
		buffer[bytes_read] = '\0';
		temp = result;
		result = malloc(strlen(temp) + bytes_read + 1);
		if (!result)
		{
			free(temp);
			return NULL;
		}
		strcpy(result, temp);
		strcat(result, buffer);
		free (temp);
	}
	return result;
}

void search(char *input, const char *str)
{
	int len2 = strlen(str);
	char *found;

	if (len2 == 0)
		return ;
	while ((found = strstr(input, str)))
	{
		memset(found, '*', len2);
		input = found + len2;
	}
}

int main(int ac, char **av)
{
	char *input;

	if (ac != 2)
		return 1;
	input = readln();
	search(input, av[1]);
	write(1, input, strlen(input));
	free(input);
	return (0);
}
