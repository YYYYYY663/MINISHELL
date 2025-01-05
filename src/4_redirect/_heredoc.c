/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _heredoc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymizukam <ymizukam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/04 22:17:00 by ymizukam          #+#    #+#             */
/*   Updated: 2025/01/05 21:54:45 by ymizukam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_redirect.h"
#include "xunistd.h"

// ctrol Dでも終了
// ctrol C
void	heredoc(const char *delimiter, int *in, t_info *info)
{
	int		pipefds[2];
	char	*line;

	xclose(in);
	xpipe(pipefds, info);
	while (1)
	{
		printf(">");
		fflush(stdout);
		line = get_next_line(STDIN_FILENO);
		if (ft_strncmp(line, delimiter, ft_strlen(line) - 1) == 0)
		{
			free(line);
			break ;
		}
		write(pipefds[1], line, ft_strlen(line));
		free(line);
	}
	xclose(&pipefds[1]);
	*in = pipefds[0];
}
