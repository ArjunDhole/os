#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>

sem_t RW_mutex;
sem_t mutex;
int numreader = 0;
int balance = 10000;
int r_no, w_no;
int func[50];
int amt[20];

void *creditWriter() {   
    int amt_credit, cur_bal_c;
    
    sem_wait(&RW_mutex);
    
    printf("Writer is writing\n");
    // updateBalance();
    printf("Enter the amount to credit: ");
    scanf("%d", &amt_credit);
    cur_bal_c = balance;
    cur_bal_c += amt_credit;
    balance = cur_bal_c;
    printf("Balance: %d\n", balance);

    sem_post(&RW_mutex);

}

void *debitWriter() {   
    int amt_debit, cur_bal_d;
    sem_wait(&RW_mutex);
    
    printf("Writer is writing\nReader count is %d\n", numreader);
    // updateBalance();
    printf("Enter the amount to debit: ");
    scanf("%d", &amt_debit);
    cur_bal_d = balance;
    cur_bal_d -= amt_debit;
    balance = cur_bal_d;
    printf("Balance: %d\n", balance);

    sem_post(&RW_mutex);

}

void *reader() {   
    sem_wait(&mutex);
    numreader++;
    if(numreader == 1) {
        sem_wait(&RW_mutex);
    }
    sem_post(&mutex);
    // Reading Section
    printf("Reading\nReader count is  %d\n", numreader);

    sem_wait(&mutex);
    numreader--;
    // printf("Reader exited\n");
    if(numreader == 0) {
        sem_post(&RW_mutex); 
    }
    sem_post(&mutex);
}

int main() {   
    printf("Enter the number of readers: ");
    scanf("%d", &r_no);
    printf("Enter the number of writers: ");
    scanf("%d", &w_no);
    for(int i = 0; i < w_no; i++) {
        printf("Enter the function of writer %d(1 for credit/2 for debit): ", i+1);
        scanf("%d", &func[i]);
    }
    pthread_t read[r_no],write[w_no];
    sem_init(&mutex, 0, 1);
    sem_init(&RW_mutex,0,1);
    
    for(int i = 0; i < r_no; i++) {
        pthread_create(&read[i], NULL, reader, NULL);
    }

    for(int i = 0; i < w_no; i++) {
        if(func[i] == 1) {
            pthread_create(&write[i], NULL, creditWriter, NULL);
        }
        else if(func[i] == 2) {
            pthread_create(&write[i], NULL, debitWriter, NULL);
        }
    }

    for(int i = 0; i < r_no; i++) {
        pthread_join(read[i], NULL);
    }
    for(int i = 0; i < w_no; i++) {
        pthread_join(write[i], NULL);
    }

    sem_destroy(&mutex);
    sem_destroy(&RW_mutex);

    return 0;
    
}