/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: teando <teando@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 16:45:19 by teando            #+#    #+#             */
/*   Updated: 2025/01/18 00:25:14 by teando           ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "ft_color.h"
#include "minishell.h"

extern volatile sig_atomic_t g_signal_status;

void shell_loop(t_info *info)
{
	while (1)
	{
		line_init(info);
		ft_dprintf(2, BG_GREEN WHITE "%s" RESET "\n", info->cwd);
		info->source_line = read_line_until_balanced(PROMPT);
		if (info->source_line == NULL)
			break;
		if (g_signal_status == SIGINT)
			continue;
		// if (g_signal_status == SIGQUIT)
		if (launch_lexer(info))
			continue;
		if (launch_parser(info))
			continue;
		if (launch_executor(info))
			continue;
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
// 		// info->source_line = read_line_until_balanced(info->cwd);
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

int main(int argc, char **argv, char **envp)
{
	t_info *info;

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
