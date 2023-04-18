#include <stdio.h>
#include<stdlib.h>
#include <dirent.h>
struct dirent *dptr;
int main(int argc, char *argv[]){
 char buff[100];
 DIR *dirp;
 printf("Enter the directory name\n");
 scanf("%s",buff);
 if((dirp=opendir(buff))==NULL){
 printf("file does not exit !!!!!!!!!!");
 exit(1);
 }
 while(dptr = readdir(dirp)){
 printf("%s\n",dptr->d_name);
 }
 closedir(dirp);
}
 