//First fit best fit worst fit next fit

#include<stdio.h>
#include<stdbool.h>
#include<limits.h>
void print_allocation(int process_count, int block_and_holes[process_count][2], int 
processes[process_count]){
 printf("\nProcess ID \tProcess Size \tAllocated Block \tHole Created\n");
 for(int i=0; i<process_count; i++){
 if(block_and_holes[i][0] != -1)
 printf("\t%d \t\t %d \t\t %d \t\t %d \n\n", i, processes[i],block_and_holes[i][0], 
block_and_holes[i][1]);
 else
 printf("\t%d \t\t %d \t\t Not Allocated \t\t No Hole \n\n", i, processes[i]);
 }
}
void first_fit(int process_count, int block_count, int blocks[block_count], int 
processes[process_count], bool allocation[process_count], int block_and_holes[process_count][2]){
 for(int i=0; i<process_count; i++){
 for(int j=0; j<block_count; j++){
 printf("%d \n", blocks[j]);
 if(processes[i] <= blocks[j]){
 block_and_holes[i][0] = blocks[j];
 blocks[j] -= processes[i];
 block_and_holes[i][1] = blocks[j];
 break;
 }
 }
 }
 for(int j=0; j<block_count; j++){
 printf("%d \t", blocks[j]);
 }
 printf("\n");
 printf("\nThe Allocation using first fit: \n\n");
 print_allocation(process_count, block_and_holes, processes);
}
void best_fit(int process_count, int block_count, int blocks[block_count], int 
processes[process_count], bool allocation[process_count], int block_and_holes[process_count][2]){
 
 for(int i=0; i<process_count; i++){
 int least_diff = INT_MAX;
 int block_ind = 0;
 for(int j=0; j<block_count; j++){
 int diff = blocks[j] - processes[i];
 if(diff >= 0 && diff <= least_diff){
 least_diff = diff;
 block_ind = j;
 }
 }
 if(least_diff != INT_MAX){
 block_and_holes[i][0] = blocks[block_ind];
 blocks[block_ind] -= processes[i];
 block_and_holes[i][1] = blocks[block_ind];
 least_diff = INT_MAX;
 }
 for(int j=0; j<block_count; j++){
 printf("%d \t", blocks[j]);
 }
 printf("\n");
 }
 printf("\nThe Allocation using best fit: \n\n");
 print_allocation(process_count, block_and_holes, processes);
}
void worst_fit(int process_count, int block_count, int blocks[block_count], int 
processes[process_count], bool allocation[process_count], int block_and_holes[process_count][2]){
 
 for(int i=0; i<process_count; i++){
 int max_diff = INT_MIN;
 int block_ind = 0;
 for(int j=0; j<block_count; j++){
 int diff = blocks[j] - processes[i];
 if(diff >= 0 && diff >= max_diff){
 max_diff = diff;
 block_ind = j;
 }
 }
 if(max_diff != INT_MIN){
 block_and_holes[i][0] = blocks[block_ind];
 blocks[block_ind] -= processes[i];
 block_and_holes[i][1] = blocks[block_ind] ;
 max_diff = INT_MIN;
 }
 
 }
 for(int j=0; j<block_count; j++){
 printf("%d \t", blocks[j]);
 }
 printf("\n");
 printf("\nThe Allocation using worst fit: \n\n");
 print_allocation(process_count, block_and_holes, processes);
}
void next_fit(int process_count, int block_count, int blocks[block_count], int 
processes[process_count], bool allocation[process_count], int block_and_holes[process_count][2]){
 int j = 0;
 for(int i=0; i<process_count; i++){
 int count = 0;
 for(; count <= block_count; j++){
 count++;
 if(processes[i] <= blocks[j%block_count]){
 block_and_holes[i][0] = blocks[j%block_count];
 blocks[j%block_count] -= processes[i];
 block_and_holes[i][1] = blocks[j%block_count];
 break;
 }
 }
 count = 0;
 
 }
 for(int j=0; j<block_count; j++){
 printf("%d \t", blocks[j]);
 }
 printf("\n");
 printf("\nThe Allocation using next fit: \n\n");
 print_allocation(process_count, block_and_holes, processes);
}
int main(){
 int block_count;
 printf("Enter the number of blocks :");
 scanf("%d", &block_count);
 int blocks[block_count], blocks_const[block_count] ;
 printf("Enter the block sizes :");
 for(int i=0; i<block_count; i++){
 scanf("%d", &blocks[i]);
 blocks_const[i] = blocks[i];
 }
 int process_count;
 printf("Enter the number of processes :");
 scanf("%d", &process_count);
 int processes[process_count];
 printf("Enter the process sizes :");
 for(int i=0; i<process_count; i++){
 scanf("%d", &processes[i]);
 }
 bool allocation[block_count];
 for(int i=0; i<block_count; i++){
 allocation[i] = false;
 }
 int block_and_hole[process_count][2];
 int choice = 1;
 while(true){
 printf("\n\nSelect Any One Allocation Technique: \n1. First Fit\n2. Best Fit\n3. Worst Fit\n4.Next Fit\n5. Exit.\n\nEnter Your choice: ");
 scanf("%d", &choice);
 switch(choice){
 case 1: 
 for(int i=0; i<block_count; i++) allocation[i] = false;
 for(int i=0; i<process_count; i++) for(int j=0; j<2; j++) block_and_hole[i][j] = -1;
 for(int i=0; i<block_count;i++) blocks[i] = blocks_const[i];
 first_fit(process_count, block_count, blocks, processes, allocation, block_and_hole);
 break;
 case 2: 
 for(int i=0; i<block_count; i++) allocation[i] = false;
 for(int i=0; i<process_count; i++) for(int j=0; j<2; j++) block_and_hole[i][j] = -1;
 for(int i=0; i<block_count;i++) blocks[i] = blocks_const[i];
 best_fit(process_count, block_count, blocks, processes, allocation, block_and_hole);
 break;
 case 3: 
 for(int i=0; i<block_count; i++) allocation[i] = false;
 for(int i=0; i<process_count; i++) for(int j=0; j<2; j++) block_and_hole[i][j] = -1;
 for(int i=0; i<block_count;i++) blocks[i] = blocks_const[i];
 worst_fit(process_count, block_count, blocks, processes, allocation, block_and_hole);
 break;
 case 4:
 for(int i=0; i<block_count; i++) allocation[i] = false;
 for(int i=0; i<process_count; i++) for(int j=0; j<2; j++) block_and_hole[i][j] = -1;
 for(int i=0; i<block_count;i++) blocks[i] = blocks_const[i];
 next_fit(process_count, block_count, blocks, processes, allocation, block_and_hole); 
 break;
 case 5:
 printf("\n\n Exit");
 return 0;
 default: 
 printf("\n\nOoops!! You messed up!!!!!");
 break;
 }
 }
 return 0;
}