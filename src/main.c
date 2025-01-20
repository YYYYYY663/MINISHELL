/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: teando <teando@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 16:45:19 by teando            #+#    #+#             */
/*   Updated: 2025/01/20 08:20:17 by teando           ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "ft_color.h"
#include "minishell.h"

extern volatile sig_atomic_t g_signal_status;

static void shell_loop(t_info *info)
{
	while (1)
	{
		line_init(info);

		ft_dprintf(2, BG_GREEN WHITE "%s" RESET "\n", info->cwd);
		info->source_line = launch_readline(PROMPT);
		if (info->source_line == NULL)
			system_exit(info, info->status);
		if (g_signal_status == SIGINT)
		{
			g_signal_status = 0;
			free(info->source_line);
			info->source_line = NULL;
			continue;
		}
		int status = launch_lexer(info) || launch_parser(info) || launch_executor(info);
		if (status != E_NONE)
			system_exit(info, status);
	}
}

int main(int argc, char **argv, char **envp)
{
	t_info *info;

	(void)argc;
	(void)argv;
	if (init_signals())
		return (ft_dprintf(2, "signal setup failure\n"), 1);
	info = system_init(envp);
	// alias_update(RCFILE, info);
	shell_loop(info);
	system_exit(info, info->status);
}
