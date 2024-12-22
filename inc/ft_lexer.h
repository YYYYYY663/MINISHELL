/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lexer.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: teando <teando@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 16:44:20 by teando            #+#    #+#             */
/*   Updated: 2024/12/23 05:39:06 by teando           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LEXER_H
# define FT_LEXER_H

# include "ft_system.h"
# include "ft_token.h"

typedef struct s_lexer
{
	const char	*input;
	size_t		pos;
}				t_lexer;

/* <---------------- 外部インターフェース ----------------> */
t_status		xlexer(t_info *info);
void			token_list_free(t_list **token_list);
void			debug_print_token_list(t_list *list);

/* <---------------- 内部用プロトタイプ ----------------> */

// lexer_main_loop.c
int				tokenize_line(t_info *info);

// lexer_cmds.c
int				parse_one_command(const char *line, size_t *i, t_info *info);
t_token			*get_operator_token(const char *line, size_t *pos,
					t_info *info);

// lexer_quoted.c
int				handle_quoted(const char *line, size_t *i, t_info *info,
					char ***cmd_argv);

// lexer_redirect.c
t_token			*parse_redirect(const char *line, size_t *pos, t_info *info);
int				handle_redirect(const char *line, size_t *i, t_info *info,
					t_list **redir_list);
int				flush_redir_list(t_list **redir_list, t_info *info);

// allocate_token.c
t_token			*create_token(t_token_type type, char **value, t_info *info);
int				add_token(t_info *info, t_token *tok);

// lexer_utils.c
int				skip_spaces(const char *line, size_t *pos);
char			**strs_append(char **src, const char *newstr, t_info *info);

// token_type_identifier.c
int				is_cmd_delimiter(char c);
t_token_type	get_redirect_type(const char *s, size_t *len);
t_token_type	get_two_char_op(const char *s, size_t *len);
t_token_type	get_one_char_op(char c);

#endif