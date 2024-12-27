/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xunistd.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymizukam <ymizukam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/22 16:34:17 by ymizukam          #+#    #+#             */
/*   Updated: 2024/12/22 16:40:15 by ymizukam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef XUNISTD_H
# define XUNISTD_H

# include <unistd.h>
# include "ft_system.h"
# include <errno.h>
#include <fcntl.h>

pid_t	xfork(t_info *info);
void	xpipe(int pipfds[], t_info *info);
void	xfree(void **ptr);
int		xclose(int *fd);

/**** **** **** ****ALLOCATE**** **** **** ****/
void	*xmalloc(size_t size, t_info *info);
t_list	*xlstnew(char *data, t_info *info);


#endif