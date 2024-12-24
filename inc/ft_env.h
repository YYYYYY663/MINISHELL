/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymizukam <ymizukam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 21:48:09 by ymizukam          #+#    #+#             */
/*   Updated: 2024/12/20 05:11:59 by ymizukam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_ENV_H
# define FT_ENV_H

# include "ft_system.h"

typedef struct s_map
{
	char * key;
	char * val;
	int opt;
} t_map;





/**** ENV ****/
// keyから値を取得、なかったらNULL
char		*env_get(t_list *env, char *key);
// entityを追加
t_status	env_export(t_list *env, char *ent);
// keyを削除
t_status	env_unset(t_list *env, char *key);

// todo accessは関数ポインタとして渡す、infoを渡す
t_status	xabsolute_path(char *dstpath, char *srcpath, t_list *env_map,
				int mode);

/**** **** **** **** UTILS **** **** **** ****/
int			_check_key(char *key);
int			__cmp(void *data, void *key);

#endif