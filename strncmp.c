#include <stddef.h>
//#include <sys/types.h>

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t			i;
	unsigned char	*str1;
	unsigned char	*str2;

	str1 = (unsigned char *)s1;
	str2 = (unsigned char *)s2;
	i = 0;
	if (n == 0)
		return (0);
	while (str1[i] != '\0' || str2[i] != '\0')
	{
		if (i == n - 1 || str1[i] != str2[i])
			return (str1[i] - str2[i]);
		i++;
	}
	return (str1[i] - str2[i]);
}

int main()
{
	char *s1 = "aaa";
	char *s2 = "aa";
	size_t n = 5;
	printf("%d\n", ft_strncmp(s1, s2, strlen(s1) + strlen(s2) + 1));
	return 0;
}