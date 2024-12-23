/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lexer.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: teando <teando@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 16:44:20 by teando            #+#    #+#             */
/*   Updated: 2024/12/23 18:32:40 by teando           ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#ifndef FT_LEXER_H
#define FT_LEXER_H

#include "ft_system.h"
#include "ft_token.h"

typedef struct s_lexer
{
	const char *input;
	size_t pos;
} t_lexer;

/* <---------------- 外部インターフェース ----------------> */
t_status xlexer(t_info *info);
void token_list_free(t_list **token_list);
void debug_print_token_list(t_list *list);

/* <---------------- 内部用プロトタイプ ----------------> */

// lexer_handler.c
void skip_spaces(const char *line, size_t *pos);
char *read_word(const char *line, size_t *pos, t_info *info);

// lexer_cmds.c
int next_token(const char *line, size_t *pos, t_info *info);

// lexer_main_loop.c
int tokenize_line(t_info *info);

// allocate_token.c
t_token *create_token(t_token_type type, char *value, t_info *info);
int add_token(t_info *info, t_token *tok);

// token_type_identifier.c
t_token_type get_two_char_op(const char *s, size_t *len);
t_token_type get_one_char_op(char c);

// validate_syntax.c
int validate_syntax(t_info *info);

#endif