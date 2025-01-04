/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_system.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymizukam <ymizukam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 16:53:59 by teando            #+#    #+#             */
/*   Updated: 2025/01/05 04:16:59 by ymizukam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_SYSTEM_H
# define FT_SYSTEM_H

# include "ft_token.h"
# include "libft.h"
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <unistd.h>

// # define MAX_FD 1024

typedef enum e_status
{
	E_NONE = 0,
	E_ALLOCATE = 1,
	E_ENV_KEY = 1,
	E_SYNTAX = 1,
	E_PIPE = 1,
	E_FILE,
	E_ARGUMENT,
	E_NOT_BUITIN_CMD = -2,
	E_COMMAND_NOT_FOUND = 127,
	E_SIGINT = 130,
	E_SIGQUIT = 131,
}				t_status;

typedef struct s_info
{
	char		*source_line;
	t_list		*token_list;
	t_ast		*ast;
	t_list		*env_map;
	char		*env_spc[128];
	int			stdin_backup;
	int			stdout_backup;
	char		cwd[PATH_MAX];
	t_status	status;
}				t_info;

void			token_clear(void *ptr);
void			ast_clear(t_ast *node);
t_info			*system_init(char **envp);

void			line_init(t_info *info);
void			system_exit(t_info *info, t_status status);

/**** **** **** **** READLINE **** **** **** ****/
char			*read_line_until_balanced(const char *prompt);

#endif
