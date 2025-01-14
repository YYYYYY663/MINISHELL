#include "mish_alias.h"



t_status alias_update(const char *file, t_info *info)
{
    int fd;
    char absolute_path[PATH_MAX];
    char rcfile_path[PATH_MAX];
    path_dispacher(absolute_path)
    if (!ft_strcmp(file, RCFILE))
        fd = open(file, O_RDONLY | O_CREAT);
    else
        fd = open(file, O_RDONLY);
    if (fd == -1)
        return (ft_dprintf(2,"minishell: %s: %s\n",file,strerror(errno)), E_FILE);
    
    ft_lstclear(&info->alias, free);
    info->alias = parse_rcfile(fd);
}
