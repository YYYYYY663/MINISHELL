/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_main_loop.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: teando <teando@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/23 04:58:51 by teando            #+#    #+#             */
/*   Updated: 2024/12/25 10:00:00 by teando           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_lexer.h"

int	tokenize_line(t_info *info)
{
	size_t		i;
	int			ret;
	const char	*line;

	line = info->source_line;
	info->status = E_NONE;
	i = 0;
	while (1)
	{
		ret = next_token(line, &i, info);
		if (ret == 0)
			break ;
		if (ret < 0)
		{
			if (info->status == E_NONE)
				info->status = E_SYNTAX;
			return (0);
		}
	}
	return (1);
}