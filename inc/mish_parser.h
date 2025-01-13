/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parser.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymizukam <ymizukam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 19:27:53 by teando            #+#    #+#             */
/*   Updated: 2025/01/05 05:45:53 by ymizukam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MISH_PARSER_H
# define MISH_PARSER_H

#include "mish_util.h"
#include "mish_alias.h"

typedef struct s_lexer
{
	const char	*input;
	size_t		pos;
}				t_lexer;

/* <---------------- 外部インターフェース ----------------> */
t_status		launch_lexer(t_info *info);
t_status	launch_parser(t_info *info);



/* <---------------- 内部用プロトタイプ ----------------> */
int				validate_syntax(t_info *info);

int				tokenize_line(t_info *info);
void			skip_spaces(const char *line, size_t *pos);
char			*read_word(const char *line, size_t *pos, t_info *info);
t_token_type	get_two_char_op(const char *s, size_t *len);
t_token_type	get_one_char_op(char c);



t_ast		*primary(t_list **list, t_info *info);
t_ast		*pipeline(t_list **list, t_info *info);
t_ast		*expr(t_list **list, t_info *info);








#endif /* MISH_PARSER_H */