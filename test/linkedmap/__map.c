#include "lmap.h"
#include <stdio.h>
int	main(int argc, char **argv, char **envp)
{
	t_lmap	*lmap;
	char	*home;


	(void)argc;
	(void)argv;
    lmap = ft_list_from_strs(envp);
	home = lmap_get("HOME", lmap, NULL);
	printf("before unset: %s\n", home);
	free(home);
	lmap_unset("HOME", lmap ,NULL);
	home = lmap_get("HOME", lmap, NULL);
	printf("after  unset: %s\n", home);
	free(home);
	lmap_export("NEW_KEY", "gokigennikaga!!",lmap, NULL);
	printf("export: %s\n",lmap_get("NEW_KEY",lmap, NULL));
	// // env_export("KEY=",info);
	// // env_export("NOEQUAL",info);
	// // printf("export: %s\n",env_get("KEY",info));
	// // printf("NOEQUAL: %s\n",env_get("NOEQUAL",info));
	// // printf("NOTEXIST: %s\n",env_get("NOTEXIST",info));
	// env_export("KEY=a", info);
	// env_export("KEYERR =", info);
	// env_export("1KEYERR=", info);
	return 0;
}
