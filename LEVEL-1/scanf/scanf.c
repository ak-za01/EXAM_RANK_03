/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scanf.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anktiri <anktiri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 06:17:46 by anktiri           #+#    #+#             */
/*   Updated: 2025/05/21 06:41:21 by anktiri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdarg.h>
#include <stdio.h>
#include <ctype.h>

int match_space(FILE *f)
{
	int	a;
	
	while (isspace(a = fgetc(f)) && a != EOF)
		;
	if (a == -1)
		return -1;
	ungetc(a, f);
    return (0);
}

int match_char(FILE *f, char c)
{
	int	a;

	a = fgetc(f);

	if (a == EOF)
		return -1;
	if (a != c)
	{
		ungetc(a, f);
		return 0;
	}
    return (1);
}

int scan_char(FILE *f, va_list ap)
{
	char	*r = va_arg(ap, char *);
	int		c;

	c = fgetc(f);
	if (c == EOF)
		return -1;
	*r = (char)c;
    return (1);
}

int scan_int(FILE *f, va_list ap)
{
	int	flag;
	int	res;
	int	*ar;
	int	a;

	while ((a = fgetc(f)) != EOF)
	{
		if (isdigit(a))
		{
			res = res * 10 + (a - '0');
			flag = 1;
		}
		else
		{
			ungetc(a, f);
			break;
		}
	}
	if (!flag)
		return 1;
	ar = va_arg(ap, int *);
	*ar = res;
    return (0);
}

int scan_string(FILE *f, va_list ap)
{
	char	*str = va_arg(ap, char *);
	int		a;
	int		b = 0;
	
	while ((a = fgetc(f)) != EOF && !isspace(a))
		str[b++] = a;
	str[b] = '\0';
	if (b == 0)
		return 1;
	if (a != EOF)
		ungetc(a, f);
    return (0);
}


int	match_conv(FILE *f, const char **format, va_list ap)
{
	switch (**format)
	{
		case 'c':
			return scan_char(f, ap);
		case 'd':
			match_space(f);
			return scan_int(f, ap);
		case 's':
			match_space(f);
			return scan_string(f, ap);
		case EOF:
			return -1;
		default:
			return -1;
	}
}

int ft_vfscanf(FILE *f, const char *format, va_list ap)
{
	int nconv = 0;

	int c = fgetc(f);
	if (c == EOF)
		return EOF;
	ungetc(c, f);

	while (*format)
	{
		if (*format == '%')
		{
			format++;
			if (match_conv(f, &format, ap) != 1)
				break;
			else
				nconv++;
		}
		else if (isspace(*format))
		{
			if (match_space(f) == -1)
				break;
		}
		else if (match_char(f, *format) != 1)
			break;
		format++;
	}
	if (ferror(f))
		return EOF;
	return nconv;
}


int ft_scanf(const char *format, ...)
{
	va_list	ap;
	va_start(ap, format);
	int ret = ft_vfscanf(stdin, format, ap);
	va_end(ap);
	return ret;
}

int main()
{
	int n;
	
	int i=0;
	char c='!';
	char t[100];
		
	n=ft_scanf("%s a%d", t, &i);
	
	printf("\n c : %c \n i : %d \n s : %s\n",c , i , t);
	printf("\t> R : %d<\n", n);
}