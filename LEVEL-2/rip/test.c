#include <stdio.h>

int count_invalid(char *str)
{
    int unmatched_open = 0;
    int unmatched_close = 0;

    for(int current_pos = 0; str[current_pos] ; current_pos++)
    {
        if (str[current_pos] == '(')
            unmatched_open++;
        else if (str[current_pos] == ')')
        {
            if (unmatched_open > 0)
                unmatched_open--;
            else
                unmatched_close++;
        }
    }
    return (unmatched_open + unmatched_close);
}

void    generate_valid(char *str, int total_to_remove, int already_removed, int start_pos)
{
    char saved_char;

    if (total_to_remove == already_removed && !count_invalid(str))
    {
        puts(str);
        return ;
    }
    for (int index = start_pos; str[index]; index++)
    {
        if (str[index] == '(' || str[index] == ')')
        {
            saved_char = str[index];
            str[index] = '_';
            generate_valid(str, total_to_remove, already_removed + 1, index + 1);
            str[index] = saved_char;
        }
    }
}

int main(int argc, char **argv)
{
	int total_to_remove;

    if (argc != 2)
        return (1);
    total_to_remove = count_invalid(argv[1]);
    generate_valid(argv[1], total_to_remove, 0, 0);
    return (0);
}
