#include "minishell.h"

int	main(int argc, char **argv, char **env)
{
	t_info		*info;
	t_list		*head;
	t_cmd_token	*t;

	info = system_init();
	if (argc == 1)
		info->source_line = ft_strdup("echo a b c | env");
	else
		info->source_line = ft_strdup(argv[1]);
	info->env_map = ft_list_from_strs(env);
	xlexer(info);
	head = info->token_list;
	while (head)
	{
		t = head->data;
		if (t->type == TT_WORD)
			xbuiltin(t->path, t->args, info);
		head = head->next;
	}
	system_exit(info, 0);
}
