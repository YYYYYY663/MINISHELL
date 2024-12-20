#include "ft_builtin.h"
#include "ft_env.h"
#include "ft_system.h"

t_status	__unset(const char *path, char **argv, t_info *info)
{
	int	i;

	(void)path;
	i = 0;
	while (argv[i])
	{
		env_unset(info->env_map, argv[i++]);
	}
	return (E_NONE);
}
