#include "ft_lexer.h"

#include <stdio.h>

int main(int argc, char **argv, char **env) 
{
    t_info *info = system_init(env);

    ft_putstrs_endl_fd(ft_list_to_strs(info->env_map), "\n",1);

    system_deinit(info);

    return 0;
}