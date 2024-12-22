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
	char		absolute_path[MAX_PATH];

	// todo path -> absolute pathはこの関数の中で行う方が良いか
	// char cwd[MAX_WORD_LEN];
	(void)argv;
	if (argv[1] == NULL)
	{
		// 余裕があればROOTに移動
		return (E_NONE);
	}
	ft_strlcpy(absolute_path, argv[1], MAX_PATH);
	if (argv[1][0] != '/')
		xabsolute_path(absolute_path, argv[1], info->env_map, F_OK);
	status = chdir(absolute_path);
	printf("absolute_path: %s\n", absolute_path);
	if (errno)
	{
		printf("cd: %s: %s\n", argv[1], strerror(errno));
		info->status = errno;
		return (status);
	}
	ft_strlcpy(info->cwd, absolute_path, MAX_PATH);
	return (E_NONE);
}
