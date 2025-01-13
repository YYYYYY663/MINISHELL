/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymizukam <ymizukam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 21:48:09 by ymizukam          #+#    #+#             */
/*   Updated: 2025/01/05 02:48:01 by ymizukam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_ENV_H
# define FT_ENV_H



/**** **** **** ****  VAR  **** **** **** ****/
int			var_dispacher(t_list **lst, t_info *info);

/**** **** **** **** PATH **** **** **** ****/
// todo accessは関数ポインタとして渡す、infoを渡す
int			path_dispacher(char path[], char *src, int mode, t_info *info);

int			_resolve_path_absolute(char path[], char *src, int mode,
				t_info *info);
int			_resolve_path_home(char path[], char *src, int mode, t_info *info);
int			_resolve_path_relative(char path[], char *src, int mode,
				t_info *info);

#endif