/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: teando <teando@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/23 04:19:00 by teando            #+#    #+#             */
/*   Updated: 2024/12/23 04:38:43 by teando           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_lexer.h"

int	skip_spaces(const char *line, size_t *pos)
{
	while (ft_isspace(line[*pos]))
		(*pos)++;
	return (1);
}

/*
** Append a string `newstr` to the end of `src`, returning a new array.
** Freed `src` internally. Use ft_strdup
	/ ft_strs_clear from libft where possible.
*/
char	**strs_append(char **src, const char *newstr, t_info *info)
{
	size_t	i;
	char	**dst;

	if (!newstr)
		return (src);
	i = 0;
	while (src && src[i])
		i++;
	dst = xmalloc(sizeof(char *) * (i + 2), info);
	if (!dst)
		return (ft_strs_clear(src), NULL);
	i = 0;
	while (src && src[i])
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = ft_strdup(newstr);
	dst[i + 1] = NULL;
	free(src);
	return (dst);
}
