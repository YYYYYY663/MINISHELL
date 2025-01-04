/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymizukam <ymizukam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 16:45:19 by teando            #+#    #+#             */
/*   Updated: 2025/01/04 23:56:28 by ymizukam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_color.h"
#include "minishell.h"

extern void	init_signals(void);

// void	shell_loop(t_info *info)
// {
// 	while (1)
// 	{
// 		info->source_line = read_line_until_balanced(PROMPT);
// 		if (!info->source_line)
// 		{
// 			ft_dprintf(STDOUT_FILENO, "exit\n");
// 			break ;
// 		}
// 		if (xlexer(info) == E_NONE)
// 		{
// 			debug_print_token_list(info->token_list);
// 			token_list_free(&info->token_list);
// 		}
// 		free(info->source_line);
// 		info->source_line = NULL;
// 	}
// }

void	shell_loop(t_info *info)
{
	while (1)
	{
		printf(BG_GREEN WHITE "%s", info->cwd);
		printf(RESET " $ ");
		fflush(stdout);
		// ft_dprintf(1, BG_GREEN WHITE);
		// info->source_line = read_line_until_balanced(info->cwd);
		// ft_dprintf(1, RESET " $ ");
		info->source_line = get_next_line(0);
		launch_lexer(info);
		// debug_print_token_list(info->token_list);
		launch_parser(info);
		// debug_print_ast(info->ast, 0);
		launch_executor(info);
		line_init(info);
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_info	*info;

	(void)argc;
	(void)argv;
	info = system_init(envp);
	shell_loop(info);
	system_exit(info, 0);
}
