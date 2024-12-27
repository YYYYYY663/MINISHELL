


#include "ft_system.h"
#include "ft_env.h"

int	main(int argc, char **argv, char **envp)
{
    (void)argc;
    (void)argv;
	t_info	*info;
	info = system_init(envp);

    // printf("PATH: %s\n",env_get("PATH",info));
    env_unset("HOME",info);
    printf("after unset: %s\n",env_get("HOME",info));
    env_export("NEW_KEY=gokigennikaga!!",info);
     printf("export: %s\n",env_get("NEW_KEY",info));
    



	system_exit(info, 0);
}
