#include "ft_builtin.h"
#include "ft_env.h"
#include "ft_system.h"
#include <stdio.h>
#include <unistd.h>
// #include <sys/types.h>
#include <errno.h>
#include <string.h>

// static int	check_valid_dir(const char *absolute_path)
// {
// 	// todo
// 	//stat()
// 	return (0);
// }

t_status	__cd(const char *path, char **argv, t_info *info)
{
	t_status	status;
	char		absolute_path[PATH_MAX];

	if (argv[1] == NULL)
		path_dispacher(absolute_path, "~", F_OK, info);
	else if (strncmp(argv[1],"-",2) == 0)
	{
		char *oldpwd = env_get("OLDPWD",info);
		if (oldpwd[0] == '\0')
		{
            printf("cd: OLDPWD not set\n");
			free(oldpwd);
            return (1);
        }
		path_dispacher(absolute_path, oldpwd, F_OK, info);
		free(oldpwd);
	}
	else if (argv[1][0] == '.')
		path_dispacher(absolute_path, argv[1], F_OK, info);
	else
	{
		ft_strlcpy(absolute_path, info->cwd, PATH_MAX);
		ft_strlcat(absolute_path, "/", PATH_MAX);
		ft_strlcat(absolute_path, argv[1], PATH_MAX);
	}
	
	//printf("absolute_path: %s\n", absolute_path);
	if (chdir(absolute_path) || access(absolute_path,F_OK))
	{
		printf("cd: %s: %s\n", argv[1], strerror(errno));
		info->status = errno;
		return (status);
	}
	
	env_export_item("OLDPWD", info->cwd, info);
	ft_strlcpy(info->cwd, absolute_path, PATH_MAX);
	env_export_item("PWD", info->cwd, info);
	return (E_NONE);
}
