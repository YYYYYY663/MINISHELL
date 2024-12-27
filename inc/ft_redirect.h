/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_redirect.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: teando <teando@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 19:30:22 by teando            #+#    #+#             */
/*   Updated: 2024/12/17 19:30:41 by teando           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_REDIRECT_H
# define FT_REDIRECT_H

# include "ft_system.h"


t_status redirect_dipacher(t_list *list, int *in_fd, int *out_fd, t_info *info);

#endif