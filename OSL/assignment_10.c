#include<stdio.h>
#include<stdbool.h>
#include<limits.h>
void replace_page_lru(int page, int frame_count, bool reorder, bool frame_full,int max_page,int 
page_table[max_page], int buffer[frame_count], int frame[frame_count]){
 
 int copy[frame_count];
 for(int i=0; i<frame_count; i++){
 copy[i] = buffer[i];
 }
 if(!reorder){
 buffer[0] = page;
 for(int i=1; i<frame_count; i++){
 buffer[i] = copy[i-1];
 }
 if(frame_full){
 frame[page_table[copy[frame_count-1]]] = page;
 page_table[page] = page_table[copy[frame_count-1]];
 }
 if(copy[frame_count-1] != -1)
 page_table[copy[frame_count-1]] = -1;
 }
 else{
 int prev;
 for(int i=0; i<frame_count; i++){
 if(buffer[i] == page) prev = i;
 }
 buffer[0] = page;
 for(int i=0; i<prev; i++){
 buffer[i+1] = copy[i];
 }
 for(int j= prev+1; j < frame_count; j++){
 buffer[j] = copy[j];
 }
 }
}
void lru(int page_ref, int pages[page_ref], int frame_count,int max_page, int 
page_table[max_page]){
 int frames[frame_count], buffer[frame_count];
 for(int i=0; i<frame_count; i++){
 frames[i] = -1;
 buffer[i] = -1;
 }
 int hit = 0, miss = 0;
 for(int i=0; i<page_ref; i++){
 if(page_table[pages[i]] != -1){
 printf("\n\nPage ref %d found in frame no. %d. Page HIT", pages[i], page_table[pages[i]]);
 hit++;
 replace_page_lru(pages[i], frame_count, true,false, max_page, page_table, buffer, frames);
 }
 else{
printf("\n\nNo reference to page %d found in any frame. Page MISS\nReplacing page using LRU", pages[i]);

 miss++;
 int k = 0;
 for(; k<frame_count; k++){
 if(frames[k] == -1) {
 frames[k] = pages[i];
 page_table[pages[i]] = i;
 replace_page_lru(pages[i], frame_count, false,false, max_page, page_table, buffer, 
frames);
 break;
 }
 }
 if(k == frame_count){
 replace_page_lru(pages[i], frame_count, false,true, max_page, page_table, buffer, frames);
 }
 }
 }
 printf("\n\nPage hits: %d \t\t Hit Precentage: %d\n", hit, (hit*100/page_ref));
 printf("\n\nPage Miss: %d \t\t Miss Precentage: %d\n", miss, (miss*100/page_ref));
}
bool search_optimal_page(int page, int frame_count, int frames[frame_count]){
 for(int i=0; i<frame_count; i++){
 if(frames[i] == page) return true;
 }
 return false;
}
int predict_victim(int page_count, int frame_count,int pages[page_count], int frames[frame_count], 
int index){
 int result = -1, farthest = index;
 for(int i=0; i<frame_count; i++){
 int j;
 for(j=index; j<page_count; j++){
 if(frames[i] == pages[j]){
 if(j > farthest){
 farthest = j;
 result = i;
 }
 break;
 }
 }
 if(j == page_count) return i;
 }
 return (result == -1) ? 0 : result;
 
}
void optimality(int page_refs, int pages[page_refs], int frame_count){
 int frames[frame_count];
 for(int i=0; i<frame_count; i++){
 frames[i] = -1;
 }
 int hit = 0;
 for(int i=0; i< page_refs; i++){
 if(search_optimal_page(pages[i], frame_count, frames)){
 hit++;
 continue;
 }
 
 bool is_empty = false;
 for(int j=0; j<frame_count; j++){
 if(frames[j] == -1){ 
 frames[j] = pages[i];
 is_empty = true;
 break;
 }
 }
 if(!is_empty){
 int j = predict_victim(page_refs,frame_count, pages, frames, i+1);
 frames[j] = pages[i];
 }
 }
 printf("\n\nNumber of page hits: %d: ", hit);
 printf("\n\nNumber of page misses %d: ", page_refs - hit);
}
int main(){
 int page_ref;
 printf("Enter the number of page references: ");
 scanf("%d", &page_ref);
 printf("Enter the page references: ");
 int pages[page_ref];
 for(int i=0; i<page_ref; i++){
 scanf("%d", &pages[i]);
 }
 int max = INT_MIN;
 for(int i=0; i<page_ref; i++){
 if(max < pages[i]) max = pages[i];
 }
 int page_table[max+1];
 for(int i=0; i<max+1; i++) page_table[i] = -1;
 int frame_count = 0;
 printf("Enter the number of frames: ");
 scanf("%d", &frame_count);
 int frames[frame_count];
 int opt;
 while(true){
printf("\n\n\nEnter the page replacement Algorithm to be used:\n\n1. LRU\n2. Optimality\n3. Exit\n\nEnter option:");

 scanf("%d", &opt);
 switch(opt){
 case 1:
 lru(page_ref, pages, frame_count, max,page_table);
 break;
 case 2:
 optimality(page_ref,pages, frame_count);
 break;
 case 3: 
 printf("\n\nExiting ...");
 return 0;
 default:
 printf("\n\nI think you've made a mistake");
 break;
 }
 }
 return 0;
}
