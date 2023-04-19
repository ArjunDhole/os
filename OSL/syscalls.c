//Write a program to simulate the use of linux commands like cp,grep,ls with the usage of fork and exec system calls. Also show the usage of wait,getpid() and exit

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include<signal.h>

#define   MAX_COUNT  80


void func_fork(){
	pid_t  pid;
	int status;
	pid = fork();
	if (pid == 0){
	  
	  printf("I am the child process.\n");
	}
	else {
	  printf("I am the parent process.\n");
	  wait(&status);
	  printf("Child process ended\n");
	  exit(0);
	}
	
	sleep(2);
	return;
}

void func_exec(){
	pid_t pid = 0;
	int status;
        //fork();
        pid = fork();
        if (pid == 0) {
                printf("I am the child and my parent is %d.\n",getppid());
                execl("/bin/ls", "ls", "-l", "/home/pccoe", (char *) 0);
                execl("/bin/cp","cp", "syscalls.c","forky.c",NULL);
  		perror("In exec(): ");
        }
        if (pid > 0) {
                  printf("I am the parent, the child is %d.\n", pid);
                  wait(&status);
  		  printf("End of process %d\n", pid);
        }
        if (pid < 0) {
                perror("In fork():");

        }
}

void func_getpid(){
	printf("My process id is %d\n",getpid());
}

void func_wait(){
	pid_t pid = 0;
	int status;
        //fork();
        pid = fork();
        if (pid == 0) {
 
		 printf("I am the child process. I would help you compute the sum fo 2 numbers.\n\n");
        	 int a,b;
        	 printf("Enter the number 1: ");
        	 scanf("%d",&a);
        	 printf("Enter the number 2: ");
        	 scanf("%d",&b);
        	 printf("The sum of 2 numbers is: %d\n",a+b);
        	 exit(0);
        	 
        	 
        }
        if (pid > 0) {
                  printf("I am the parent process\n");
                  printf("Waiting for the child process to end....\n\n");
                  wait(&status);
  		  printf("End of child process %d\n", pid);
        }
        if (pid < 0) {
                perror("In fork():");

        }
}

void main(){
	int choice;
	int i=4;
	while(1){
	printf("***** A demo program on system calls. *****\n");
	
	printf("1. fork() \n");
	printf("2. exec() \n");
	printf("3. getpid() \n");
	printf("4. wait() \n");
	printf("5. exit()\n");
	
	printf("Choose one of the above system call.: ");
	scanf("%d",&choice);
	
	switch(choice){
		case 1:
			func_fork();
			break;
		case 2:
			func_exec();
			break;
		
		case 3:
			func_getpid();
			break;
		case 4:
			func_wait();
			break;
		
		case 5:
			exit(0);
			break;
			
		default:
			printf("Please enter a valid option");
			
	
	}
	i--;
	}
}
