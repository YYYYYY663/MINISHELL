/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _env_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymizukam <ymizukam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 19:48:26 by ymizukam          #+#    #+#             */
/*   Updated: 2024/12/20 05:13:37 by ymizukam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_env.h"

int	_check_key(char *key)
{
	/*
	アルファベット（a-z, A-Z）またはアンダースコア（_）で始まる必要がある。
	2文字目以降は、アルファベット、数字（0-9）、またはアンダースコアが使える。
	空白や特殊記号（例: !, @, #, - など）は使用できない(chatGPT)
	*/
	// todo TEST=など
	return (0);
}
int	__cmp(void *data, void *key)
{
	char	uniq_key[PATH_MAX];

	ft_strlcpy(uniq_key, key, PATH_MAX);
	ft_strlcat(uniq_key, "=", PATH_MAX);
	return (ft_strncmp((char *)data, (char *)uniq_key,
			ft_strlen((char *)uniq_key)));
}
