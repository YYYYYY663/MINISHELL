/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_builtin.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymizukam <ymizukam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 22:01:24 by teando            #+#    #+#             */
/*   Updated: 2025/01/29 19:45:54 by ymizukam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_BUILTIN_H
# define FT_BUILTIN_H

# include "ft_env.h"
# include "ft_system.h"

t_status			builtin_dispatcher(t_cmd *args, int *in_fd, int *out_fd,
						t_info *info);

// wrapper関数の定義　関数ポインタ型の宣言
typedef t_status	(*t_builtin_func)(char **argv, t_info *info);

/**** **** **** ** CALLBACK ** **** **** ****/
t_status			__pwd(char **argv, t_info *info);
t_status			__cd(char **argv, t_info *info);
t_status			__echo(char **argv, t_info *info);
t_status			__export(char **argv, t_info *info);
t_status			__unset(char **argv, t_info *info);
t_status			__exit(char **argv, t_info *info);
t_status			__env(char **argv, t_info *info);

#endif
