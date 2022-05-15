#include <stdarg.h>
#include <stdio.h>
#include <unistd.h>

int print_char(char c)
{	
	return (write (1, &c ,1));
}

int * print_unsigned_number(unsigned int n)
{
	int static	len;
	if (n == 0)
		len += print_char('0');
	else
	{
		if(n > 10)
		print_unsigned_number(n / 10);
		len += print_char(n % 10  + '0');
	}
	return (&len);
}

int * print_hex(unsigned int num, char type )
{
	static int len;
	char *alpha;

	alpha = "0123456789abcdef";
	if (type == 'X')
		alpha = "0123456789ABCDEF";  
	if(num > 15)
		print_hex(num / 16, type);
	len += print_char(alpha[num % 16]);
	return (&len);
}

int print_pointer(uintptr_t ptr){
	int len;
	int *templen;

	write(1, "0x" ,2);
	len = 2;
	templen = print_hex(ptr, 'x');
	len += *templen;
	*templen = 0;
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
	int *tempLen;

	len = 0;
	if (format == 'c')
		len += print_char(va_arg(args, int));
	else if (format == 's')
		len += print_string(va_arg(args, char *));	
	else if (format == 'x' || format == 'X')
	{
		tempLen = print_hex(va_arg(args, unsigned int), format);
		len += *tempLen;
		*tempLen = 0;  
	}
	else if (format == '%')
		len += print_char('%');
	else if (format == 'p')
		len += print_pointer(va_arg(args, uintptr_t));
	else if (format == 'u')
		tempLen = print_unsigned_number(va_arg(args, unsigned int));
		len += *tempLen;
		*tempLen = 0;  
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
	int a = 10;
	int *b = &a;
	char c = 'a';
	//printf("%p\n",b);
	//int cc = write (1, &c ,1);
	//ft_printf("%c", c);
	printf("\n%d \n", ft_printf("%u",20));
	return (0);
}