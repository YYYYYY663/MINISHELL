/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _env_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymizukam <ymizukam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 19:48:26 by ymizukam          #+#    #+#             */
/*   Updated: 2025/01/05 21:54:58 by ymizukam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_env.h"

int	_check_key(char *key)
{
	int	i;

	if (!ft_isalpha(key[0]) && key[0] != '_')
	{
		ft_dprintf(STDERR_FILENO,
			"minishell: export: `%s\': not a valid identifier\n", key);
		return (1);
	}
	i = 0;
	while (key[++i])
	{
		if (!ft_isalnum(key[i]) && key[i] != '_')
		{
			ft_dprintf(STDERR_FILENO,
				"minishell: export: `%s\': not a valid identifier\n", key);
			return (1);
		}
	}
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
