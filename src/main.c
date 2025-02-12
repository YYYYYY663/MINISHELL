/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymizukam <ymizukam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 16:45:19 by teando            #+#    #+#             */
/*   Updated: 2025/02/12 18:29:06 by ymizukam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_color.h"
#include "minishell.h"

extern volatile sig_atomic_t	g_signal_status;
void	prompt(t_info *info)
{
	line_init(info);
	info->line = launch_readline(info->cwd);
	if (g_signal_status == SIGINT)
		return ;
	if (info->line == NULL)
		system_exit(info, g_signal_status | 0x80);
	launch_lexer(info) || launch_parser(info) || launch_executor(info);
	// debug_print_token(info->token);
}

int	main(int argc, char **argv, char **envp)
{
	t_info	*info;

	(void)argc;
	(void)argv;
	if (init_signals())
		return (ft_dprintf(2, "signal setup failure\n"), 1);
	info = system_init(envp);
	// alias_update(RCFILE, info);
	while (1)
		prompt(info);
	system_exit(info, info->status);
}
