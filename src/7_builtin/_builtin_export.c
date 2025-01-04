/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _builtin_export.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymizukam <ymizukam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/04 22:06:41 by ymizukam          #+#    #+#             */
/*   Updated: 2025/01/05 02:42:06 by ymizukam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_builtin.h"
#include "ft_env.h"
#include "ft_system.h"

static void	_display_sorted_env_line(const char *entity);
static void	_display_sorted_env(t_info *info);

t_status	__export(char **argv, t_info *info)
{
	int	i;

	i = 1;
	if (!argv[1])
	{
		_display_sorted_env(info);
	}
	while (argv[i])
	{
		env_export(argv[i++], info);
	}
	return (E_NONE);
}

static void	_swap(char **a, char **b)
{
	char	*tmp;

	tmp = *a;
	*a = *b;
	*b = tmp;
}

static void	_display_sorted_env(t_info *info)
{
	char	**envp;
	int		len;
	int		i;
	int		j;

	envp = ft_list_to_strs(info->env_map);
	len = ft_list_size(info->env_map);
	i = 0;
	while (i < len - 1)
	{
		j = i + 1;
		while (j < len)
		{
			if (ft_strcmp(envp[i], envp[j]) > 0)
			{
				_swap(&envp[i], &envp[j]);
			}
			j++;
		}
		_display_sorted_env_line(envp[i++]);
	}
	_display_sorted_env_line(envp[i]);
}

static void	_display_sorted_env_line(const char *entity)
{
	char	*key;
	char	*value;

	key = ft_substr_l(entity, '=');
	value = ft_substr_r(entity, '=');
	ft_putstr_fd("declare -x ", STDOUT_FILENO);
	ft_putstr_fd(key, STDOUT_FILENO);
	if (value[0])
	{
		ft_putstr_fd("=\"", STDOUT_FILENO);
		ft_putstr_fd(value, STDOUT_FILENO);
		ft_putstr_fd("\"", STDOUT_FILENO);
	}
	printf("\n");
	free(value);
	free(key);
}
