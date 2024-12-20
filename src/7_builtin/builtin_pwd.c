#include "ft_builtin.h"
#include "ft_env.h"
#include "ft_system.h"

/*
 *ref char * getcwd(char *buf, size_t size);
 */
t_status	__pwd(const char *path, char **argv, t_info *info)
{
	(void)path;
	(void)argv;
	printf("%s\n", info->cwd);
	return (E_NONE);
}
