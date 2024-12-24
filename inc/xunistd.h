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

pid_t	xfork(t_info *info);
void	xpipe(int pipfds[], t_info *info);
void	xfree(void **ptr);
int		xclose(int *fd);

/**** **** **** ****ALLOCATE**** **** **** ****/
void	*xmalloc(size_t size, t_info *info);
t_list	*xlstnew(char *data, t_info *info);
t_list	*xlst_from_strs(char **strs, t_info *info);
char	**xlst_to_strs(t_list *lst, t_info *info);
char	**xsplit(char *str, char sep, t_info *info);

#endif