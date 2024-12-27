#include "ft_redirect.h"
#include "ft_lexer.h"
#include "ft_parser.h"

#include <fcntl.h>
#include <stdio.h>

int main(int argc, char **argv, char **env) 
{
    (void)argc;
    (void)argv;
    t_info *info = system_init(env);

    // ft_putstrs_endl_fd(ft_list_to_strs(info->env_map), "\n",1);
    info->source_line = ft_strdup("ls -l -a  << EOF << EIF < in");
    launch_lexer(info);
    t_args *args = consume_args(&info->token_list, info);
    // if(open("~/Desktop/MINISHELL/src/3_executor/Makefile", O_RDONLY)==-1)
    //     perror("open");

    int in_fd = STDIN_FILENO;
    int out_fd = STDOUT_FILENO;

    debug_print_token_list(args->argv);
    debug_print_token_list(args->redr);

    redirect_dipacher(args->redr,&in_fd, &out_fd, info);

    printf("in %d   out %d\n",in_fd,out_fd);
    system_exit(info,0);
}