/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymizukam <ymizukam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 18:20:59 by teando            #+#    #+#             */
/*   Updated: 2025/01/14 12:28:22 by ymizukam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKEN_H
# define TOKEN_H

# include "libft.h"
# include "lmap.h"
# include "sys.h"

typedef int			t_token_type;

# define WORD_ID 0xF000 // WORD TYPE
/* -------------------------------------------------------------------------- */
# define CMD_ARG 0x1000
# define CONNECT 0x2000
# define PIPE 0x3000
# define PRIORITY 0x4000

# define ARG_ID 0xF00 // COMMAND ARG TYPE
/* -------------------------------------------------------------------------- */
# define WORD 0x100
# define REDIRECT 0x200

# define QUOTE_ID 0xF0 // coffee "coffee" 'coffee' only if WORDTYPE = CMD_ARG
/* -------------------------------------------------------------------------- */
# define NO_QUOTE 0x00
# define SINGLE_QUOTE 0x10
# define DOUBLE_QUOTE 0x20

// # define TT_WORD 0x1101

# define REDIRECT_ID 0xFF0F // + QUOTE TYPE
/* -------------------------------------------------------------------------- */
# define TT_REDIR_IN 0x1201
# define TT_APPEND 0x1202
# define TT_REDIR_OUT 0x1203
# define TT_HEREDOC 0x1204

# define CONNECT_ID 0xFFFF
/* -------------------------------------------------------------------------- */
# define TT_AND_AND 0x2001
# define TT_OR_OR 0x2002
# define TT_SEMICOLON 0x2003
# define TT_EOF 0x2004
# define TT_ERROR 0xFFFF

# define PRIORITY_ID 0xFFFF
/* -------------------------------------------------------------------------- */
# define TT_LPAREN 0x4001
# define TT_RPAREN 0x4002

/* -------------------------------------------------------------------------- */
/*                                   STRUCT                                   */
/* -------------------------------------------------------------------------- */

typedef struct s_token
{
	t_token_type	type;
	char			*value;
}					t_token;

/* -------------------------------------------------------------------------- */
/*                                   FUNCS                                    */
/* -------------------------------------------------------------------------- */

int					consume(t_token_type type, t_list **lst);
void				expect(t_token_type type, t_list **lst);

void				token_clear(void *ptr);
t_token				*create_token(t_token_type type, char *value, t_info *info);
int					add_token(t_info *info, t_token *tok);

#endif