#ifndef LMAP_H
#define LMAP_H

#include <limits.h>

#ifndef PATH_MAX
#define PATH_MAX 2048
#endif


#include "libft.h"
typedef t_list t_lmap;

void	lmap_export(char *key, char *value, t_lmap *lmap, int (*cmp)(void *,void *));
int default_cmp(void *data, void *key);
void	lmap_unset(char *key, t_lmap *lmap, int (*cmp)(void *,void *));
char	*lmap_get(char *key, t_lmap *lmap, int (*cmp)(void *,void *));


#endif