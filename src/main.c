/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymizukam <ymizukam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 16:45:19 by teando            #+#    #+#             */
/*   Updated: 2025/01/12 22:57:16 by ymizukam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_color.h"
#include "minishell.h"

extern volatile sig_atomic_t	g_signal_status;

void	shell_loop(t_info *info)
{
	while (1)
	{
		line_init(info);
		ft_dprintf(2, BG_GREEN WHITE "%s" RESET "\n", info->cwd);
		info->source_line = launch_readline(PROMPT);
		if (g_signal_status == SIGINT)
		{
			dprintf(2, "Ctrl C while prompt\n");
			continue ;
		}
		if (info->source_line == NULL)
		{
			break ; /* (Ctrl-D) の場合 */
		}
		// if (g_signal_status == SIGINT)
		// {
		// 	g_signal_status = 0;
		// 	free(info->source_line);
		// 	info->source_line = NULL;
		// 	continue ;
		// }
		// else if (g_signal_status == SIGQUIT)
		// {
		// 	g_signal_status = 0; /* SIGQUITは無視 (bash互換) */
		// }
		if (launch_lexer(info))
			continue ;
		if (launch_parser(info))
			continue ;
		if (launch_executor(info))
			continue ;
	}
}

// void	shell_loop(t_info *info)
// {
// 	while (1)
// 	{
// 		printf(BG_GREEN WHITE "%s", info->cwd);
// 		printf(RESET " $ ");
// 		fflush(stdout);
// 		// ft_dprintf(1, BG_GREEN WHITE);
// 		// info->source_line = launch_readline(info->cwd);
// 		// ft_dprintf(1, RESET " $ ");
// 		info->source_line = get_next_line(0);
// 		launch_lexer(info);
// 		// debug_print_token_list(info->token_list);
// 		launch_parser(info);
// 		// debug_print_ast(info->ast, 0);
// 		launch_executor(info);
// 		line_init(info);
// 	}
// }

int	main(int argc, char **argv, char **envp)
{
	t_info	*info;

	(void)argc;
	(void)argv;
	if (!init_signals())
	{
		ft_dprintf(2, "signal setup failure\n");
		return (1);
	}
	info = system_init(envp);
	shell_loop(info);
	system_exit(info, 0);
}
