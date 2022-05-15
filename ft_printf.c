#include <stdarg.h>
#include <stdio.h>
#include <unistd.h>

int ft_strlen(char *s)
{
	int i;

	i = 0;
	while(s[i])
	{
		i++;
	}

	return i; 
}

int print_char(char c)
{
	write (1, &c ,1);
	return (1);
}

int print_hex(unsigned int num, char type )
{
	static int len;
	char *alpha;

	alpha = "0123456789abcdef";
	if (type == 'X')
		alpha = "0123456789ABCDEF";  
	if(num > 15)
		print_hex(num / 16, type);
	len += print_char(alpha[num % 16]);
	return (len);
}

int	print_string(char *s)
{
	int	i;

	i = 0;
	if (s == NULL)
	{
		write(1, "(null)", 6);
		return (6);
	}
	while (s[i])
	{
		print_char(s[i]);
		i++;
	}
	return (i);
}


int print_type(va_list args, char format)
{
	int len; 
	
	len = 0;
	if (format == 'c')
		len += print_char(va_arg(args, int));
	if (format == 's')
		len += print_string(va_arg(args, char *));	
	if (format == 'x' || format == 'X')
		len += print_hex(va_arg(args, unsigned int), format);



	return (len);
}

int ft_printf(const char *s, ...)
{
	int i;
	int len;

	va_list args;
	va_start(args, s);

	i = 0;
	len = 0;

	while (s[i])
	{
		if (s[i] == '%')
		{
			i++;
			len += print_type(args, s[i]);
		}
		else 
		{
			len += print_char(s[i]);
		}
		i++;
	}
	va_end(args);
	return (len);
}

int main ()
{
	int num = 1000;
	char *s = "aaaaaa";
	printf("\n%d \n", ft_printf("%x", num));
	printf("\n");
	printf("\n%d \n", printf("%x", num));
	printf("\n");
	return (0);
}