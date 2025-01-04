/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xunistd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymizukam <ymizukam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/22 16:36:47 by ymizukam          #+#    #+#             */
/*   Updated: 2025/01/04 22:58:10 by ymizukam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_system.h"
#include "xunistd.h"

void	xdup2(int fildes, int fildes2, t_info *info)
{
	if (dup2(fildes, fildes2) == -1)
	{
		perror("dup2");
		system_exit(info, errno);
	}
	xclose(&fildes);
}

pid_t	xfork(t_info *info)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
	{
		perror("fork");
		system_exit(info, errno);
	}
	return (pid);
}

void	xpipe(int pipfds[], t_info *info)
{
	if (pipe(pipfds))
	{
		perror("pipe");
		system_exit(info, errno);
	}
}

void	xfree(void **ptr)
{
	if (!ptr || *ptr == NULL)
	{
		return ;
	}
	free(*ptr);
	*ptr = NULL;
}

int	xclose(int *fd)
{
	int	ret;

	if (!fd || *fd < 3)
	{
		return (0);
	}
	ret = close(*fd);
	if (ret == -1)
	{
		perror("close");
	}
	*fd = -1;
	return (ret);
}
