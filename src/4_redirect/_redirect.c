/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _redirect.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymizukam <ymizukam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/05 03:30:18 by ymizukam          #+#    #+#             */
/*   Updated: 2025/01/05 21:54:50 by ymizukam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_redirect.h"
#include "xunistd.h"

void	redirect_out(t_token_type type, char *file, int *out)
{
	xclose(out);
	if (type == TT_REDIR_OUT)
	{
		*out = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	}
	if (type == TT_APPEND)
	{
		*out = open(file, O_WRONLY | O_CREAT | O_APPEND, 0644);
	}
}

void	redirect_in(t_token_type type, char *file, int *in)
{
	xclose(in);
	if (type == TT_REDIR_IN)
	{
		*in = open(file, O_RDONLY);
	}
}
