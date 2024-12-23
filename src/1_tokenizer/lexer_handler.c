/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: teando <teando@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/23 14:07:53 by teando            #+#    #+#             */
/*   Updated: 2024/12/23 17:51:18 by teando           ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "ft_lexer.h"

/*
** ========= 1つのwordをパースしcmd_argvに追加 handle_word ===========
**
**   line: 1行の文字列
**   i: line[]の現在のインデックス
**   info: system_info
**   value: wordの文字列を格納するポインタ
**
**   1つのwordをパースしvalueに格納する
**   syntax errorが起きた場合はinfo->statusにE_SYNTAXを設定し、0を返す
**   それ以外は、(*i)++を行い1を返す
*/
int handle_word(const char *line, size_t *i, t_info *info, char **value)
{
	size_t start;

	(void)info;  // Suppress unused parameter warning
	start = *i;
	while (line[*i] && !ft_isspace(line[*i]))
	{
		/* 演算子にぶつかったらword終了 */
		if (get_two_char_op(&line[*i], NULL) != TT_ERROR || get_one_char_op(line[*i]) != TT_ERROR)
			break;
		(*i)++;
	}
	if ((*i - start) > 0)
		*value = ft_substr(line, start, (*i - start));
	else
		*value = ft_strdup("");
	return (*value != NULL);
}
