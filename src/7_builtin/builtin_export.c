#include "ft_builtin.h"
#include "ft_env.h"
#include "ft_system.h"

t_status	__export(const char *path, char **argv, t_info *info)
{
	int	i;

	// printf("%s\n",env_get(info->env_map,"TEST"));
	// printf("%s\n",env_get(info->env_map,"PWDDDDDDD"));
	// env_export(info->env_map, argv[1]);
	i = 1;
	while (argv[i])
	{
		env_export(info->env_map, argv[i++]);
	}
	return (E_NONE);
}
