#include<stdio.h>
#include<conio.h>
#include<stdlib.h>
typedef struct process
{
int pid,st,ft,prior;
int wt,tat,bt;
int flag;
}pr;
int n;
pr p[10];
void accept(int);
void fcfs();
void disp_gantt();
void sjf_sort();
void priority_sort();
void clrscr() {
    system("clear");  // for Linux and macOS
    // system("cls");  // for Windows
}


void main()
{
int ch,tq;
clrscr();

do
{
printf(" Scheduling Algorithms ");
printf("\n\t1. FCFS\n\t2. SJF\n\t3. Priority\n\t4. Exit");
printf("\n\t Enter your choice: ");
scanf("%d",&ch);
switch(ch)
{
case 1:
accept(ch);
fcfs();
break;
case 2:
accept(ch);
sjf_sort();
fcfs();
break;
case 3:
accept(ch);
priority_sort();
fcfs();
break;

case 4:
exit(0);
break;
default:
printf("\nInvalid Choice…..!");
}
printf("\nPress any key to continue………");
getch();
clrscr();
}while(ch!=5);
getch();
}


void accept(int ch)
{
int i;
printf("\nEnter number of processes: ");
scanf("%d",&n);
if(ch==1 || ch==2)
{
for(i=0;i<n;i++)
{
printf("\nEnter the Burst Time of process p%d:",i);
scanf("%d",&p[i].bt);
p[i].pid=i;
}
}
if(ch==3)
{
for(i=0;i<n;i++)
{
printf("\nEnter the Burst Time & Priority of process p%d:",i);
scanf("%d%d", &p[i].bt, &p[i].prior);
p[i].pid=i;
}
}
if(ch==4)
{
for(i=0;i<n;i++)
{
printf("\nEnter the Burst Time of process p%d:",i);
scanf("%d",&p[i].bt);
p[i].pid=i;
}
}
}
void fcfs()
{
int i;
float avgtat=0,avgwt=0;
for(i=0;i<n;i++)
{
if(i==0)
{
p[i].st=i;
p[i].wt=p[i].st;
p[i].tat=p[i].wt+p[i].bt;
p[i].ft=p[i].st+p[i].bt;
}
else
{
p[i].st=p[i-1].ft;
p[i].wt=p[i].st;
p[i].tat=p[i].wt+p[i].bt;
p[i].ft=p[i].st+p[i].bt;
}
avgtat=avgtat+p[i].tat;
avgwt=avgwt+p[i].wt;
}
avgtat=avgtat/n;
avgwt=avgwt/n;
disp_gantt(n);
for(i=0;i<n;i++)
printf("\nWaiting Time(P%d):%dms\t Turnaround Time(P%d):%dms",p[i].pid,p[i].wt,p[i].pid,p[i].tat);
printf("\nAverage Turn Around Time:%fms",avgtat);
printf("\nAverage waiting time:%fms",avgwt);
}
void disp_gantt()
{
    int i;
    printf("\n\tGANTT CHART\n");
    for(i=0;i<n;i++)
        printf("| P%d ",p[i].pid);
    printf("|\n");
    for(i=0;i<n;i++)
        printf("%d ",p[i].st);
    printf("%d\n",p[n-1].ft);
}

void sjf_sort()
{
int i,j;
pr temp;
for(i=0;i<n;i++)
{
for(j=0;j<n-i-1;j++) { if(p[j].bt>p[j+1].bt)
{
temp=p[j];
p[j]=p[j+1];
p[j+1]=temp;
}
}
}
}
void priority_sort()
{
int i,j;
pr temp;
for(i=0;i<n;i++)
{
for(j=0;j<n-i-1;j++) { if(p[j].prior>p[j+1].prior)
{
temp=p[j];
p[j]=p[j+1];
p[j+1]=temp;
}
}
}
}
