//Implement paging simulation using LRU,Optimal algorithm

//C++ implementation of above algorithm
#include<bits/stdc++.h>
using namespace std;
// Function to find page faults using indexes
void LRU(int pages[], int n, int capacity)
{
set<int> s;
map<int, int> use_time;
int page_faults = 0;
cout<<"Find\t\t"<<"No Of Frames\t\t"<<"Result"<<endl;
for (int i=0; i<n; i++)
{
int temp = page_faults;
if (s.size() < capacity)
{
if (s.find(pages[i])==s.end())
{
s.insert(pages[i]);
page_faults++;
}
use_time[pages[i]] = i;
}
else
{
if (s.find(pages[i]) == s.end())
{
int lru = INT_MAX, val;
for (auto it=s.begin(); it!=s.end(); it++)
{
if (use_time[*it] < lru)
{
lru = use_time[*it];
val = *it;
}
}
s.erase(val);
s.insert(pages[i]);
page_faults++;
}
use_time[pages[i]] = i;
}
cout<<" "<<pages[i]<<"\t\t";
set<int>::iterator j;
for(j=s.begin();j!=s.end();j++){
cout<<*j<<" ";
}
for(int j=0;j<capacity-s.size();j++)
cout<<" ";
if(temp==page_faults) cout<<"\t\tHit";
else cout<<"\t\tMiss";
cout<<"\n";
}
cout<<"\nThe total no. of Page faults: "<<page_faults<<endl;
}
void Optimal(int pages[], int n, int capacity)
{
set<int> s;
vector<int> arr;
for(int i=0;i<n;i++){
arr.push_back(pages[i]);
}
map<int, int> indexes;
int page_faults = 0;
cout<<"Find\t\t"<<"Page Table\t\t"<<"Result"<<endl;
for (int i=0; i<n; i++)
{
int temp = page_faults;
if (s.size() < capacity)
{
if (s.find(pages[i])==s.end())
{
s.insert(pages[i]);
arr.erase(arr.begin());
page_faults++;
}
indexes[pages[i]] = i;
}
else
{
if (s.find(pages[i]) == s.end())
{
map<int,int> mp;
set<int>::iterator it = s.begin();
for(it=s.begin();it!=s.end();it++){
mp[*it]=-1;
}
for(int j=0;j<arr.size();j++){
if(mp[arr[j]]==-1){
mp[arr[j]]=j;
}
}
int toBeRemoved=-1, mx=INT_MIN;
for(auto it: mp){
if(it.second==-1){
toBeRemoved = it.first;
break;
}
else{
if(it.second> mx){
toBeRemoved = it.first;
mx = it.second;
}
}
}
s.erase(toBeRemoved);
s.insert(pages[i]);
page_faults++;
}
indexes[pages[i]] = i;
}
cout<<" "<<pages[i]<<"\t\t";
set<int>::iterator j;
for(j=s.begin();j!=s.end();j++){
cout<<*j<<" ";
}
for(int j=0;j<capacity-s.size();j++)
cout<<" ";
if(temp==page_faults) cout<<"\t\tHit";
else cout<<"\t\tMiss";
cout<<"\n";
}
cout<<"\nThe total no. of Page faults: "<<page_faults<<endl;
}
int main()
{
int n;
cout<<"Enter the number of Processes in sequence of arrival order: ";
cin>>n;
int pages[n];
cout<<"Enter each process ID: "<<endl;
for(int i=0;i<n;i++){
cin>>pages[i];
}
int capacity = 4;
cout<<"\n--------------- LRU -----------------\n\n";
LRU(pages, n, capacity);
cout<<"\n\n\n--------------- Optimal -----------------\n\n";
Optimal(pages, n, capacity);
return 0;
}