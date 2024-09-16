#include "../inc/libft.h"

int	ft_isblank(int c)
{
	if (c == 11 || c == 13 || c == 32)
		return (c);
	return (0);
}
