/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: teando <teando@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/23 04:19:00 by teando            #+#    #+#             */
/*   Updated: 2024/12/23 04:22:26 by teando           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_lexer.h"

/************************************
 * 文字列配列操作のヘルパー
 ************************************/
/* --- 文字列配列の末尾に一要素追加した新配列を返す --- */
/* 要素数カウント -> 再alloc -> 代入  -> 古いsrcをfree*/
char	**strs_append(char **src, const char *newstr, t_info *info)
{
	size_t	i;
	char	**dst;

	if (!newstr)
		return (src);
	i = 0;
	if (src && src[i])
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
