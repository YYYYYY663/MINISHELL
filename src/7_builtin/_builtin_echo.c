/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: teando <teando@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 15:48:32 by teando            #+#    #+#             */
/*   Updated: 2024/12/17 23:36:48 by teando           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_builtin.h"
#include "ft_env.h"
#include "ft_system.h"



int _validate_option(char *arg);

t_status	__echo(const char *path, char **argv, t_info *info)
{
	int	is_option_n;


	(void)path;


	if (argv[1] == NULL)
	{
		ft_putendl_fd("", STDOUT_FILENO);
        return (E_NONE);
	}
	is_option_n = _validate_option(argv[1]);
	ft_putstrs_fd(&argv[1 + is_option_n], " ", STDOUT_FILENO);
	if (!is_option_n)
	    ft_putendl_fd("", STDOUT_FILENO);
	return (E_NONE);
}


int _validate_option(char *arg)
{
	if (arg[0]!= '-' || arg[1] == '\0')
        return (0);
    while (arg[1])
    {
        if (arg[1]!= 'n')
            return (0);
        arg++;
    }
    return (1);
}