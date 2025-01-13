#include "mish_alias.h"


char *alias_dispacher(char *key, t_info *info)
{
    if (!info->alias)
        return NULL;
    value = lmap_get(key,info->alias,NULL);
    if (!value)
		return (NULL);
	return (value);
}