

#include "ft_redirect.h"
#include "xunistd.h"

int heredoc(const char *delimiter, t_info *info)
{
    int pipefds[2];
    xpipe(pipefds, info);

    //ctrol Dでも終了
    //ctrol C
    printf(">");
    close(pipefds[1]);
    return (pipefds[0]);
}