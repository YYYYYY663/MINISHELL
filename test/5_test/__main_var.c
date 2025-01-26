

#include "ft_env.h"
#include "ft_system.h"

int	main(int argc, char **argv, char **envp)
{
	t_info	*info;

	(void)argc;
	(void)argv;
	info = system_init(envp);
	info->source_line = ft_strdup("$NOEXIST $EXIST");
	launch_lexer(info);
	debug_print_token_list(info->token_list);
	var_dispatcher(info->token_list, info);
	debug_print_token_list(info->token_list);
	system_exit(info, 0);
}
