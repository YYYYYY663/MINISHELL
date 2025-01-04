#include "ft_lexer.h"
#include "ft_parser.h"
#include "ft_token.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

int	main(int argc, char **argv, char **env)
{
	t_info	*info;

	(void)argc;
	(void)argv;
	info = system_init(env);
	// ft_putstrs_endl_fd(ft_list_to_strs(info->env_map), "\n",1);
	info->source_line = ft_strdup("ls -l && cat");
	launch_lexer(info);
	// debug_print_token_list(info->token_list);
	launch_parser(info);
	// debug_print_ast(info->ast, 0);
	system_exit(info, 0);
	return (0);
}
