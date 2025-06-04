#include <stdarg.h>
#include <stdio.h>
#include <ctype.h>

int match_space(FILE *f)
{
	int	cr;
	while (isspace(cr = fgetc(f)) && cr !=EOF)
	if (cr == EOF)
		return -1;
	ungetc(cr, f);
    return (0);
}

int match_char(FILE *f, char c)
{
	int	cr = fgetc(f);
	if (cr == EOF)
		return -1;
	if (cr != c)
	{
		ungetc(cr, f);
		return 0;
	}
    return (1);
}

int scan_char(FILE *f, va_list ap)
{
	int	cr = fgetc(f);
	if (cr == EOF)
		return -1;
	*va_arg(ap, char *) = cr;
    return (1);
}

int scan_int(FILE *f, va_list ap)
{
	int	*ptr = va_arg(ap, int *);
	int	res = 0;
	int flag = 0;
	int	sign = 1;
	int	cr;

	while (isspace(cr = fgetc(f)) && cr != EOF)
	if (cr == EOF)
		return -1;
	if (cr == '-' || cr == '+')
	{
		if (cr == '-')
			sign = -1;
		cr = fgetc(f);
	}
	if (cr == EOF)
		return -1;
	while (isdigit(cr))
	{
		res = res * 10 + (cr - '0');
		flag = 1;
		cr = fgetc(f);
	}
	if (cr != EOF)
		ungetc(cr, f);
	if (!flag)
		return 0;
	*ptr = res * sign;
    return (1);
}

int scan_string(FILE *f, va_list ap)
{
	char	*str = va_arg(ap, char *);
	int		cr;
	int		a = 0;

	while (isspace(cr = fgetc(f)) && cr != EOF)
	if (cr == EOF)
		return -1;
	while (cr != EOF && !isspace(cr))
	{
		str[a] = cr;
		cr = fgetc(f);
		a++;
	}
	str[a] = '\0';
	if (a != EOF)
		ungetc(cr, f);
	if (cr == 0)
		return 0;
    return (1);
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
		
	n = ft_scanf("%s hello%d%c", t, &i, &c);
	
	printf("\n c : %c \n i : %d \n s : %s\n",c , i , t);
	printf("\t> R : %d<\n", n);
}
