#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include<string.h>
int main(int argc   , char *argv[])
{
pid_t pid;
pid = fork();
if (pid < 0)
{
fprintf(stderr, "Fork error\n");
exit(1);
}
else if (pid == 0)
{
if (strcmp(argv[1], "cp") == 0)
{
execl("/bin/cp", "cp", argv[2], argv[3], NULL);
}
else if (strcmp(argv[1], "grep") == 0)
{
execl("/bin/grep", "grep", argv[2], argv[3], NULL);
}
else if (strcmp(argv[1], "ls") == 0)
{
execl("/bin/ls", "ls", "-l", NULL);
}
else
{
fprintf(stderr, "Wrong command\n");
exit(1);
}
}
else
{
int status;
wait(&status);
if (strcmp(argv[1], "grep") == 0)
{
if (WEXITSTATUS(status) != 0)
{
fprintf(stderr, "grep did not find the string\n");
exit(1);
}
}
// printf("Child process exited with status %d\n", WEXITSTATUS(status));
// printf("Parent process (pid %d) exiting\n", getpid());
exit(0);
}
return 0;
}