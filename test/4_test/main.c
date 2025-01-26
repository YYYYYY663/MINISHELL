/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymizukam <ymizukam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/04 22:17:15 by ymizukam          #+#    #+#             */
/*   Updated: 2025/01/27 06:05:35 by ymizukam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_lexer.h"
#include "ft_parser.h"
#include "ft_redirect.h"
#include <fcntl.h>
#include <stdio.h>

int	main(int argc, char **argv, char **env)
{
	t_info	*info;
	int		in_fd;
	int		out_fd;

	(void)argc;
	(void)argv;
	info = system_init(env);
	info->source_line = ft_strdup("< in >out");
	launch_lexer(info);
	in_fd = STDIN_FILENO;
	out_fd = STDOUT_FILENO;
	debug_print_token_list(info->token_list);
	redirect_dipatcher(info->token_list, &in_fd, &out_fd, info);
	printf("in %d   out %d\n", in_fd, out_fd);
	system_exit(info, 0);
}
