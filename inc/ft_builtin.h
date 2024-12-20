/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_builtin.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: teando <teando@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 22:01:24 by teando            #+#    #+#             */
/*   Updated: 2024/12/17 22:40:29 by teando           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_BUILTIN_H
# define FT_BUILTIN_H

# include "ft_env.h"
# include "ft_system.h"

t_status			builtin_dispatcher(char *path, char **argv, t_info *info);

// wrapper関数の定義　関数ポインタ型の宣言
typedef t_status	(*t_builtin_func)(const char *path, char **argv,
		t_info *info);

// static char **builtin_path = {"echo","cd","pwd","export","unset","env","exit"};


/**** **** **** ** CALLBACK ** **** **** ****/
t_status			__pwd(const char *path, char **argv, t_info *info);
t_status			__cd(const char *path, char **argv, t_info *info);
t_status			__echo(const char *path, char **argv, t_info *info);
t_status			__export(const char *path, char **argv, t_info *info);
t_status			__unset(const char *path, char **argv, t_info *info);
t_status			__exit(const char *path, char **argv, t_info *info);
t_status			__env(const char *path, char **argv, t_info *info);
#endif