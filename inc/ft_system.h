/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_system.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymizukam <ymizukam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 16:53:59 by teando            #+#    #+#             */
/*   Updated: 2025/01/27 12:45:34 by ymizukam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_SYSTEM_H
# define FT_SYSTEM_H

# include "ft_token.h"
# include "libft.h"
# include <errno.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <unistd.h>

extern volatile sig_atomic_t	g_signal_status;
// # define MAX_FD 1024

typedef enum e_status
{
	E_NONE = 0,
	E_ALLOCATE = 1,
	E_ENV_KEY = 1,
	E_SYNTAX = 2,
	E_PIPE = 1,
	E_FILE,
	E_ARGUMENT,
	E_NOT_BUITIN_CMD = -2,
	E_COMMAND_NOT_FOUND = 127,
	E_SIGINT = 130,
	E_SIGQUIT = 131,
}								t_status;

typedef struct s_info
{
	char						*line;
	t_list						*token;
	t_ast						*ast;
	t_list						*env_map;
	char						*env_spc[128];
	// t_list						*alias_map;
	int							stdin_backup;
	int							stdout_backup;
	char						cwd[PATH_MAX];
	t_status					status;
}								t_info;

void							token_clear(void *ptr);
void							ast_clear(t_ast *node);
t_info							*system_init(char **envp);

void							line_init(t_info *info);
void							system_exit(t_info *info, t_status status);

/**** **** **** **** READLINE **** **** **** ****/
char							*launch_readline(const char *prompt);

#endif
