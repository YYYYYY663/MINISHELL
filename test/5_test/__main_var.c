

#include "ft_env.h"
#include "ft_system.h"

int	main(int argc, char **argv, char **envp)
{
	t_info	*info;

	(void)argc;
	(void)argv;
	info = system_init(envp);
	info->line = ft_strdup("$NOEXIST $EXIST");
	launch_lexer(info);
	debug_print_token(info->token);
	var_dispatcher(info->token, info);
	debug_print_token(info->token);
	system_exit(info, 0);
}
