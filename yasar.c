#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
int main()
{
    int pipe1[2];
    int pipe2[2];
    if (pipe(pipe1) == -1 || pipe(pipe2) == -1)
        perror("pipe err");
    pid_t pid1 = fork();
    if (pid1 == -1)
        perror("pid1 err");
    else if (pid1 == 0)
    {
        close(pipe1[0]);
        dup2(pipe1[1], STDOUT_FILENO);
        close (pipe1[1]);
        char *ls_arg[] = {"ls", NULL};
        execve("/bin/ls", ls_arg, NULL);
        perror("exec1 err");
    }
    close(pipe1[1]);
    pid_t   pid2 = fork();
    if (pid2 == -1)
        perror("pid2 err");
    else if (pid2 == 0)
    {
        dup2(pipe1[0], STDIN_FILENO);
        close(pipe1[0]);
        close(pipe2[0]);
        dup2(pipe2[1], STDOUT_FILENO);
        close(pipe2[1]);
        char    *grep_arg[] = {"grep", ".c", NULL};
        execve("/usr/bin/grep", grep_arg, NULL);
        perror ("exec2 err");
    }
    close(pipe2[1]);
    close(pipe1[0]);
    pid_t   pid3 = fork();
    if (pid3 == -1)
        perror("pid3 err");
    else if(pid3 == 0)
    {
        dup2(pipe2[0], STDIN_FILENO);
        close(pipe2[0]);
        char *wc_arg[] = {"wc", "-l", NULL};
        execve("/usr/bin/wc", wc_arg, NULL);
        perror("exec3 err");
    }
    waitpid(pid1, NULL, 0);
    waitpid(pid2, NULL, 0);
    waitpid(pid3, NULL, 0);
    close(pipe2[0]);
}

//ls | grep ".c" | wc -l