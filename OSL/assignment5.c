#include<unistd.h>
#include<stdio.h>
#include<string.h>


int main()
{
    int pid;
    int pipefds1[2], pipefds2[2];
    int returnstatus1;
    int returnstatus2;
    returnstatus1 = pipe(pipefds1);
    if(returnstatus1==-1)
    {
        printf("Unable to create pipe");
        return 1;
    }
    returnstatus2 = pipe(pipefds2);
    if(returnstatus2==-1)
    {
        printf("Unable to create pipe");
        return 1;
    }
    char writemsg1[20];
    char readmsg[20];
    char writemsg2[20];
    int i=0;

    pid = fork();
    if(pid != 0)
    //parent process
    {
        close(pipefds1[0]);
        close(pipefds2[1]);
        //parent process sends message
        printf("Enter the message1 to send from Parent Process: ");
        fgets(writemsg1, 20, stdin);
        write(pipefds1[1],writemsg1,sizeof(writemsg1));
        //parent process reads msg
        read(pipefds2[0],readmsg,sizeof(readmsg));
        printf("Parent process reads message2 from pipe2 as: %s", readmsg);
    }
    else{
        close(pipefds1[1]);
        close(pipefds2[0]);
        //child process reads msg
        read(pipefds1[0], readmsg, sizeof(readmsg));
        printf("Child process reads message1 from pipe1 as: %s", readmsg);
        //child process writes msg
        printf("Enter the message2 to send from child process: ");
        fgets(writemsg2, 20, stdin);
        write(pipefds2[1], writemsg2, sizeof(writemsg2) );
    }
}   
