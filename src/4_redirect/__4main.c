/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   __4main.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymizukam <ymizukam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/04 22:17:15 by ymizukam          #+#    #+#             */
/*   Updated: 2025/01/04 22:17:17 by ymizukam         ###   ########.fr       */
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
	t_args	*args;
	int		in_fd;
	int		out_fd;

	(void)argc;
	(void)argv;
	info = system_init(env);
	// ft_putstrs_endl_fd(ft_list_to_strs(info->env_map), "\n",1);
	info->source_line = ft_strdup("ls -l -a  << EOF << EIF < in");
	launch_lexer(info);
	args = consume_args(&info->token_list, info);
	// if(open("~/Desktop/MINISHELL/src/3_executor/Makefile", O_RDONLY)==-1)
	//     perror("open");
	in_fd = STDIN_FILENO;
	out_fd = STDOUT_FILENO;
	debug_print_token_list(args->argv);
	debug_print_token_list(args->redr);
	redirect_dipacher(args->redr, &in_fd, &out_fd, info);
	printf("in %d   out %d\n", in_fd, out_fd);
	system_exit(info, 0);
}
