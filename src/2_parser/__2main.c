#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <time.h>
#include "ft_token.h"

#include <ft_parser.h>
#include "ft_lexer.h"


int main(int argc, char **argv, char **env) 
{
    (void)argc;
    (void)argv;
    t_info *info = system_init(env);

    // ft_putstrs_endl_fd(ft_list_to_strs(info->env_map), "\n",1);
    info->source_line = ft_strdup("HELLO Hi >am | < in KOTARO  desu | yoroshiku  || andand");
    launch_lexer(info);
    debug_print_token_list(info->token_list);
    
    launch_parser(info);

    debug_print_ast(info->ast, 0);

    system_deinit(info);

    return 0;
}