

#include "ft_redirect.h"
#include "xunistd.h"

int heredoc(const char *delimiter, t_info *info)
{
    int pipefds[2];
    xpipe(pipefds, info);
    printf(">"); 
    printf("\n"); 

    //ctrol Dでも終了
    //ctrol C
    // while(1)
    // {
    //    delimiterまで読み込み
    //     ft_putstr_fd(line, pipefds[1])
    //     printf(">");
    // }
    close(pipefds[1]);
    return (pipefds[0]);
}