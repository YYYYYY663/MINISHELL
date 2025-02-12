/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lexer.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymizukam <ymizukam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 16:44:20 by teando            #+#    #+#             */
/*   Updated: 2025/02/12 19:06:49 by ymizukam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LEXER_H
# define FT_LEXER_H

# include "ft_system.h"
# include "ft_token.h"
# include "xunistd.h"

typedef struct s_lexer
{
	const char	*input;
	size_t		pos;
}				t_lexer;

/* <---------------- 外部インターフェース ----------------> */
t_status		launch_lexer(t_info *info);

void			debug_print_token(t_list *list);

const char		*type_to_str(t_token_type t);

#endif