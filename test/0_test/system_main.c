#include "ft_system.h"
#include <stdio.h>

int	main(int argc, char **argv, char **env)
{
	t_info	*info;

	(void)argc;
	(void)argv;
	info = system_init(env);
	printf("CWD: %s\n", info->cwd);
	printf("STATUS: %d\n", info->status);
	info->line = ft_strdup("a");
	line_init(info);
	info->ast = ast_node_new(1, NULL, NULL);
	system_exit(info, 0);
	return (0);
}
