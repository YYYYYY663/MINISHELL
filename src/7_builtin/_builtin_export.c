#include "ft_builtin.h"
#include "ft_env.h"
#include "ft_system.h"

t_status	__export(const char *path, char **argv, t_info *info)
{
	int	i;

	#ifdef FUNC_OUT
	    printf("%s\n",__func__);
		ft_putstrs_endl_fd(argv,"  ",1);
    #endif
	i = 1;
	while (argv[i])
	{
	
		env_export(argv[i++],info);
	}
	return (E_NONE);
}
