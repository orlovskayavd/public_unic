#include <stdio.h>

char	*ft_strcat(char *s1, const char *s2)
{
	char *ptr_s1 = s1;
	char *ptr_s2 = (char*)s2;

	while (*s1)
		s1++;
	while (*ptr_s2)
	{
		*s1 = *ptr_s2;
		s1++;
		ptr_s2++;
	}
	*s1 = 0;
	return (ptr_s1);
}

int		main() 
{
	char str1[20] = "asdf";
	char str2[10] = "ghji546";

	ft_strcat(str1, str2);
	printf("%s\n", str1);
	return 0;
}
