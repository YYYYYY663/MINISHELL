/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_executor.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymizukam <ymizukam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 19:28:38 by teando            #+#    #+#             */
/*   Updated: 2025/01/05 02:48:52 by ymizukam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_EXECUTOR_H
# define FT_EXECUTOR_H

# include "ft_system.h"

// # include "ft_builtin.h"
// # include "ft_redirect.h"
t_status	launch_executor(t_info *info);

t_status	traverse_ast_nodes(t_ast *node, t_info *info);

/**** **** **** **** NODE **** **** **** ****/

t_status	pipe_node(t_ast *node, int in_fd, int out_fd, t_info *info);

pid_t		cmd_node(t_ast *node, int in_fd, int out_fd, t_info *info);

/**** **** **** **** PIPELINE **** **** **** ****/

t_status	exec_pipeline(t_ast *node, t_info *info);

void		kill_pipeline(t_ast *node, t_info *info);

/**** **** **** **** UTILS **** **** **** ****/

int			setup_args(t_args *args, int *in_fd, int *out_fd, t_info *info);

#endif