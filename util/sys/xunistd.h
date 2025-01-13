/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xunistd.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymizukam <ymizukam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/22 16:34:17 by ymizukam          #+#    #+#             */
/*   Updated: 2025/01/05 02:43:58 by ymizukam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef XUNISTD_H
# define XUNISTD_H

# include "sys.h"
# include <errno.h>
# include <fcntl.h>
# include <unistd.h>

void	xdup2(int fildes, int fildes2, t_info *info);
pid_t	xfork(t_info *info);
void	xpipe(int pipfds[], t_info *info);
void	xfree(void **ptr);
int		xclose(int *fd);

/**** **** **** ****ALLOCATE**** **** **** ****/
void	*xmalloc(size_t size, t_info *info);
t_list	*xlstnew(char *data, t_info *info);

#endif