#ifndef FT_ALIAS_H
# define FT_ALIAS_H

# include "ft_system.h"
# include <fcntl.h>
# define RCFILE "~/.minishellrc"

t_status	alias_update(const char *file, t_info *info);
t_list		*parse_alias_file(int fd);

#endif