#include "ft_builtin.h"
#include "ft_env.h"
#include "ft_system.h"
#include <stdio.h>
#include <unistd.h>
// #include <sys/types.h>
#include <errno.h>
#include <string.h>

static int _cd_home(char path[],char *arg, t_info *info);
static int _cd_oldpwd(char path[],char *arg, t_info *info);

t_status	__cd(const char *path, char **argv, t_info *info)
{
	char		absolute_path[PATH_MAX];
	(void)path;
	if (argv[1] == NULL || argv[1][0] == '~')
	{
		if(_cd_home(absolute_path, argv[1], info))
			return 1;
	}
	else if (strncmp(argv[1],"-",2) == 0)
	{
		if(_cd_oldpwd(absolute_path, argv[1], info))
			return 1;
	}
	else if (argv[1][0] == '.' || argv[1][0] == '/')
		path_dispacher(absolute_path, argv[1], F_OK, info);
	else
	{
		ft_strlcpy(absolute_path, info->cwd, PATH_MAX);
		ft_strlcat(absolute_path, "/", PATH_MAX);
		ft_strlcat(absolute_path, argv[1], PATH_MAX);
	}
	if (chdir(absolute_path) || access(absolute_path,F_OK))
	{
		// todo xperror
		printf("cd: %s: %s\n", argv[1], strerror(errno));
		return (1);
	}
	env_export_item("OLDPWD", info->cwd, info);
	ft_strlcpy(info->cwd, absolute_path, PATH_MAX);
	env_export_item("PWD", info->cwd, info);
	return (E_NONE);
}


static int _cd_home(char path[],char *arg, t_info *info)
{
	char *home = env_get("HOME",info);
	if (home[0] == '\0')
	{
		printf("cd: HOME not set\n");
		free(home);
		return (1);
	}
	free(home);
	if (arg == NULL)
		path_dispacher(path, "~", F_OK, info);
	else
		path_dispacher(path, arg, F_OK, info);
	return 0;
}

static int _cd_oldpwd(char path[],char *arg, t_info *info)
{

	(void)arg;
	char *oldpwd = env_get("OLDPWD",info);
	if (oldpwd[0] == '\0')
	{
		printf("cd: OLDPWD not set\n");
		free(oldpwd);
		return (1);
	}
	path_dispacher(path, oldpwd, F_OK, info);
	free(oldpwd);
	return 0;
}