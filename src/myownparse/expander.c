#include "../../inc/headers/minishell.h"


/*falta hacer esta parte para expandir las variables, 
* no se si desarrollar mas esta funcion o crear otras y dejar esta asi
*/
char	*expander_process(char *str, char **envp)
{
	char	*expanded_str;

	expanded_str = expander_tony(str, envp);
	free(str);
	return (expanded_str);
}