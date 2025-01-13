#include "mish_builtin.h"

t_status	__alias(char **argv, t_info *info)
{

	char	**envp;
	if (!info->alias)
	{
		
	}

	if (!argv[1])
	envp = ft_list_to_strs(info->alias);
	ft_putstrs_fd(envp, "\n", STDOUT_FILENO);
	ft_putendl_fd("", STDIN_FILENO);
	ft_strs_clear(envp);
	return (E_NONE);
}



