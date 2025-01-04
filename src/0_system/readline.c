/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymizukam <ymizukam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 23:59:46 by teando            #+#    #+#             */
/*   Updated: 2025/01/05 02:07:56 by ymizukam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_system.h"

static int	is_quotes_balanced(const char *line)
{
	int		single_open;
	int		double_open;
	size_t	i;

	single_open = 0;
	double_open = 0;
	i = 0;
	while (line[i])
	{
		if (line[i] == '\'' && !double_open)
			single_open = !single_open;
		else if (line[i] == '"' && !single_open)
			double_open = !double_open;
		i++;
	}
	if (!single_open && !double_open)
		return (1);
	return (0);
}

static char	*read_command_line(const char *prompt)
{
	char	*line;

	line = readline(prompt);
	if (line && *line)
	{
		add_history(line);
	}
	return (line);
}

char	*read_line_until_balanced(const char *prompt)
{
	char	*line;
	char	*tmp;
	char	*cont_line;

	line = read_command_line(prompt);
	if (!line)
		return (NULL);
	while (!is_quotes_balanced(line))
	{
		cont_line = read_command_line("> ");
		if (!cont_line)
			return (free(line), NULL);
		tmp = ft_strjoin(line, "\n");
		free(line);
		line = ft_strjoin(tmp, cont_line);
		free(tmp);
		free(cont_line);
		if (!line)
			return (NULL);
	}
	return (line);
}
