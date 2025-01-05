/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_dispacher.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymizukam <ymizukam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/04 22:16:47 by ymizukam          #+#    #+#             */
/*   Updated: 2025/01/05 21:54:52 by ymizukam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_env.h"
#include "ft_lexer.h"
#include "ft_redirect.h"
#include "xunistd.h"

t_status	redirect_dipacher(t_list *list, int *in, int *out, t_info *info)
{
	t_token	*token;

	while (list != NULL)
	{
		token = list->data;
		if (token->type == TT_HEREDOC)
			heredoc(token->value, in, info);
		if (token->type == TT_REDIR_IN)
			redirect_in(token->type, token->value, in);
		if (token->type == TT_REDIR_OUT || token->type == TT_APPEND)
			redirect_out(token->type, token->value, out);
		if (*in == -1 || *out == -1)
		{
			ft_dprintf(2, "minishell: %s: %s\n", token->value, strerror(errno));
			xclose(out);
			xclose(in);
			return (E_FILE);
		}
		list = list->next;
	}
	return (E_NONE);
}
