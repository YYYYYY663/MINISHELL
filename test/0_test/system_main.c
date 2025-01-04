#include "ft_system.h"
#include <stdio.h>

int	main(int argc, char **argv, char **env)
{
	(void)argc;
	(void)argv;
	t_info *info = system_init(env);
	printf("CWD: %s\n", info->cwd);
	printf("STATUS: %d\n", info->status);
	info->source_line = ft_strdup("a");
	line_init(info);
	system_exit(info, 0);

	return (0);
}