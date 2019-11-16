#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

int		convert(char *str, int base)
{
	int		result = 0;

	str--;
	while (*(++str))
		result = result * base + (isdigit(*str) ? *str - '0' : tolower(*str) - 'a' + 10);
	return (result);
}

void	convert_in_base(int decimal, int base)
{
	int		size = 0;
	char	*str;
	char	*ptr;
	int		temp;

	temp = decimal;
	size = 1;
	while (decimal / base > 0)
	{
		decimal /= base;
		size++;
	}
	str = (char*)malloc(sizeof(char) * (size + 1));
	str[size] = 0;
	decimal = temp;
	str += size - 1;
	while(size > 0)
	{
		*str = (decimal % base > 9 ? 'A' + decimal % base - 10 : decimal % base + '0');
		str--;
		size--;
		decimal /= base;
	}
	printf("%s\n", str + 1);
	free(str);
}
int		main()
{
	int		base;
	char	str[32];
	int		max;
	int		temp;

	scanf("%d", &base);
	if (base < 0)
		return (0);
	scanf("%s", str);
	if (!strcmp(str, "stop"))
		return (0);
	max = convert(str, base);
	scanf("%s", str);
	while(strcmp(str, "stop"))
	{
		if (max < (temp = convert(str, base)))
			max = temp;
		if (max == -1)
			return (0);
		scanf("%s", str);
	}
	convert_in_base(max, 9);
	convert_in_base(max, 18);
	convert_in_base(max, 27);
	convert_in_base(max, 36);
}