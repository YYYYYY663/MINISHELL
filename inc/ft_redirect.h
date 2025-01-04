/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_redirect.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymizukam <ymizukam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 19:30:22 by teando            #+#    #+#             */
/*   Updated: 2025/01/05 03:31:55 by ymizukam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_REDIRECT_H
# define FT_REDIRECT_H

# include "ft_system.h"

void		heredoc(const char *delimiter, int *in, t_info *info);

void		redirect_out(t_token_type type, char *file, int *out);

void		redirect_in(t_token_type type, char *file, int *in);

t_status	redirect_dipacher(t_list *list, int *in, int *out, t_info *info);

#endif