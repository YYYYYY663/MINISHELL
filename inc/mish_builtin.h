/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_builtin.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymizukam <ymizukam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 22:01:24 by teando            #+#    #+#             */
/*   Updated: 2025/01/05 21:57:27 by ymizukam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MISH_BUILTIN_H
# define MISH_BUILTIN_H

#include "mish_util.h"

t_status			builtin_dispatcher(t_args *args, int *in_fd, int *out_fd,
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
t_status			__alias(char **argv, t_info *info);
t_status			__source(char **argv, t_info *info);


#endif /* MISH_BUILTIN_H */
