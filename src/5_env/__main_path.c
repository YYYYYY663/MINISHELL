

#include <fcntl.h>
#include "ft_system.h"
#include "ft_env.h"


// int	path_dispacher(char path[], char *src, int mode, t_info *info)
int	main(int argc, char **argv, char **envp)
{
    (void)argc;
    (void)argv;
	t_info	*info;
    char path[PATH_MAX];
	info = system_init(envp);

    // printf("PATH: %s\n",env_get("PATH",info));
    printf("%d: ",path_dispacher(path, "ls", X_OK, info));
    printf("%s\n",path);

    printf("%d: ",path_dispacher(path, "which", X_OK, info));
    printf("%s\n",path);

    printf("%d: ",path_dispacher(path, "./Makefile", F_OK, info));
    printf("%s\n",path);

    printf("%d: ",path_dispacher(path, "../0_system", F_OK, info));
    printf("%s\n",path);

    //相対パスでもopenできるらしい
    // if (open("../0_system/xalloc.c",O_RDONLY) == -1)
    //     perror("open");


    env_unset("PATH",info);
    printf("after PATH unset\n");
    printf("%d: ",path_dispacher(path, "ls", X_OK, info));
    printf("%s\n",path);
    perror("ls");

    
	system_exit(info,0);
}