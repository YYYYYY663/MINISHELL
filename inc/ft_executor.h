/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_executor.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymizukam <ymizukam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 19:28:38 by teando            #+#    #+#             */
/*   Updated: 2024/12/22 16:45:32 by ymizukam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_EXECUTOR_H
# define FT_EXECUTOR_H

#include "ft_system.h"

// # include "ft_builtin.h"
// # include "ft_redirect.h"
t_status launch_executor(t_info *info);

t_status	traverse_ast_nodes(t_ast *node, t_info *info);


t_status pipe_node(t_ast *node, int in_fd, int out_fd, t_info *info);
t_status cmd_node(t_ast *node, int in_fd, int out_fd, t_info *info);

#endif