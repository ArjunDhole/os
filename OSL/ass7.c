#include <pthread.h>
#include <stdio.h>
#include <semaphore.h> 
 

sem_t wrt;
pthread_mutex_t mutex;
int cnt=1;
int numreader=0;
int amount=50000;
int debit;
int  credit;
int opts;


void *writer(void *wno){
    sem_wait(&wrt);
    printf("\nWriter %d Reader Count: %d\n",(*((int *)wno)),numreader);
    printf("Writer is in Shared Memory\n");

    printf("Select operation: 1.credit 2.debit \n ");
    scanf("%d",&opts);
    switch (opts)
    {
    case 1:
        printf("Enter amount to credit: ");
        scanf("%d",&credit);
        amount+=credit;
        break;
    case 2:
        printf("Enter amount to debit: ");
        scanf("%d",&debit);
        amount-=debit;
        break;
    
    }
    
    printf("Amount after writer:%d\n",amount);
    sem_post(&wrt);
}
void *reader(void *rno){
    pthread_mutex_lock(&mutex);
    numreader++;
    if(numreader==1){
        sem_wait(&wrt);
    }
    pthread_mutex_unlock(&mutex);
    printf("\nReader %d Reading the amount as:%d read count:  %d \n",*((int *)rno ),amount,numreader);
    // printf("Reader Reading the amount as:%d\n",amount);

    pthread_mutex_lock(&mutex);
    numreader--;
    if(numreader==0){
        sem_post(&wrt);
    }

    pthread_mutex_unlock(&mutex);
}

int main(){
    pthread_t read[1000],write[1000];
    pthread_mutex_init(&mutex,NULL);
    sem_init(&wrt,0,1);
    int num_of_readers;
    int num_of_writers;

    printf("Enter Number of readers: ");
    scanf("%d",&num_of_readers);
    printf("Enter Number of Writers:");
    scanf("%d",&num_of_writers);
    int a[1000];
    for (int i=0;i<num_of_readers;i++ ){
        a[i]=i+1;
    }
    
    

    for(int i=0;i<num_of_readers;i++){
        pthread_create(&read[i],NULL,(void *)reader,(void *)&a[i]);
    }

    for(int i=0;i<num_of_writers;i++){
        pthread_create(&write[i],NULL,(void *)writer,(void *)&a[i]);
    }
    for(int i=0;i<num_of_readers;i++){
        pthread_join(read[i],NULL);
    }
    for(int i=0;i<num_of_writers;i++){
        pthread_join(write[i],NULL);
    }

    pthread_mutex_destroy(&mutex);
    sem_destroy(&wrt);

    
    return 0;
}
