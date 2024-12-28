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

	// todo path -> absolute pathはこの関数の中で行う方が良いか
	// char cwd[MAX_WORD_LEN];
	(void)argv;
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
	else
	{
		path_dispacher(absolute_path, argv[1], F_OK, info);
	}
	
	//printf("absolute_path: %s\n", absolute_path);
	if (chdir(absolute_path))
	{
		printf("cd: %s: %s\n", argv[1], strerror(errno));
		info->status = errno;
		return (status);
	}
	//printf("prev %s\n", info->cwd);
	env_export_item("OLDPWD", info->cwd, info);
	//printf("OLDPWD %s\n",env_get("OLDPWD", info));
	ft_strlcpy(info->cwd, absolute_path, PATH_MAX);
	env_export_item("PWD", info->cwd, info);
	return (E_NONE);
}
