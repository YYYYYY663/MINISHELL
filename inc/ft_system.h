/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_system.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: teando <teando@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 16:53:59 by teando            #+#    #+#             */
/*   Updated: 2024/12/23 20:26:44 by teando           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_SYSTEM_H
# define FT_SYSTEM_H

# include "libft.h"
# include <limits.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <unistd.h>

# ifndef PATH_MAX
#  define PATH_MAX 2048
# endif
// # define MAX_FD 1024

typedef enum e_status
{
	E_NONE = 0,
	E_ALLOCATE = 1,
	E_ENV_KEY = 1,
	E_SYNTAX = 1,
	E_PIPE = 1,
	E_COMMAND_NOT_FOUND = 127,
	E_SIGINT = 130,
	E_SIGQUIT = 131,
}				t_status;

typedef struct s_info
{
	char		*source_line;
	t_list		*token_list;
	t_btree		*ast;
	t_list		*env_map;
	char		cwd[PATH_MAX];
	t_status	status;
}				t_info;

t_info			*system_init(char **envp);
void			system_deinit(t_info *info);

void			system_exit(t_info *info, t_status status);

/**** **** **** **** READLINE **** **** **** ****/
char			*read_line_until_balanced(const char *prompt);

/**** **** **** ****ALLOCATE**** **** **** ****/
void			*xmalloc(size_t size, t_info *info);
t_list			*xlstnew(char *data, t_info *info);
t_list			*xlst_from_strs(char **strs, t_info *info);
char			**xlst_to_strs(t_list *lst, t_info *info);

#endif
