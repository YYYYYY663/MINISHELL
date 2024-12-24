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

// # include "ft_builtin.h"
// # include "ft_redirect.h"
t_status launch_executor(t_info *info);

t_status	traverse_ast_nodes(t_btree *current_node, t_info *info);
#endif