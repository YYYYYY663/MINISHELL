#include "ft_lexer.h"
#include <stdio.h>

int	main(int argc, char **argv, char **env)
{
	t_info *info = system_init(env);

	// ft_putstrs_endl_fd(ft_list_to_strs(info->env_map), "\n",1);
	info->line = ft_strdup("(( ls -l | ( cat ) | grep exec )");
	launch_lexer(info);

	debug_print_token(info->token);
	system_exit(info, 0);

	return (0);
}