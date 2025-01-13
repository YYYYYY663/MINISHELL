#include "ft_builtin.h"
#include "ft_env.h"
#include "ft_system.h"

t_status	__alias(char **argv, t_info *info)
{

	char	**envp;

	(void)argv;
	envp = ft_list_to_strs(info->alias);
	ft_putstrs_fd(envp, "\n", STDOUT_FILENO);
	ft_putendl_fd("", STDIN_FILENO);
	ft_strs_clear(envp);
	return (E_NONE);
}



