//disk scheduling algorithms

#include<bits/stdc++.h>
using namespace std;
int disk_size;

void FCFS(vector<int> arr, int head){
    int cost = 0;
    for(int i=0;i<arr.size();i++){
        cost += abs(arr[i]-head);
        head = arr[i];
    }
    cout<<"The Total seek time for FCFS is:\t"<<cost<<endl;
}

void SSTF(vector<int> arr, int head){
    int cost = 0, n = arr.size();
    if(n==1){
        cout<<"The total seek time for SSTF is:\t"<<abs(head-arr[0])<<endl;
        return;
    }
    for(int i=0;i<n;i++){
        int curr, pos1=lower_bound(arr.begin(), arr.end(), head)-arr.begin()-1, pos2=upper_bound(arr.begin(), arr.end(), head)-arr.begin();
        if(head - arr[pos1] < arr[pos2] - head){
            curr = arr[pos1];
            arr.erase(arr.begin()+pos1);
            if(pos1 == 0){
                cost += head - curr;
                cost += arr[arr.size()-1]-curr;
                break;
            }
        }
        else{
            curr = arr[pos2];
            arr.erase(arr.begin()+pos2);
            if(curr == arr[arr.size()-1]){
                cost += curr - head;
                cost += curr - arr[0];
                break;
            }
        }
        cost += abs(curr - head);
        head = curr;
    }
    cout<<"The Total seek time for SSTF is:\t"<<cost<<endl;
}


void SCAN(vector<int> arr, int head ){
    int cost = 2*(disk_size-arr[0])-head+arr[0];
    cout<<"The Total seek time for SCAN is:\t"<<cost<<endl;
}

void CSCAN(vector<int> arr, int head){
    int cost = 2*disk_size - head + arr[lower_bound(arr.begin(), arr.end(), head)-arr.begin()-1];
    cout<<"The Total seek time for CSCAN is:\t"<<cost<<endl;
}

void LOOK(vector<int> arr, int head){
    int cost = 2*(arr[arr.size()-1]-arr[0])-head+arr[0];
    cout<<"The Total seek time for LOOK is:\t"<<abs(cost)<<endl;
}

void CLOOK(vector<int> arr, int head){
    int cost = 0;
    int pos = lower_bound(arr.begin(), arr.end(), head)-arr.begin()-1;
    cost += 2*(arr[arr.size()-1]-arr[0])-head+arr[pos];
    cout<<"The Total seek time for CLOOK is:\t"<<abs(cost)<<endl;
}

int main(){
    int n;
    cout<<"Enter the size of the disk: ";
    cin>>disk_size;
    disk_size--;
    cout<<"Enter the number of requests: ";
    cin>>n;
    
    vector<int> arr(n);
    for(int i=0;i<arr.size();i++){
        cin>>arr[i];
        while(arr[i]>disk_size || arr[i]<0){
            cout<<"wrong input!! try again. "<<endl;
        }
    }
    for(int i=0;i<arr.size();i++){
        if(i<arr.size()-1 && arr[i]==arr[i+1]){
            arr.erase(arr.begin()+i);
            i--;
        } 
    }
    // cout<<"Enter the the starting position of head: ";
    int head;
    cin>>head;
    FCFS(arr, head);
    sort(arr.begin(),arr.end());
    SSTF(arr, head);
    SCAN(arr, head);
    CSCAN(arr, head);
    LOOK(arr, head);
    CLOOK(arr, head);
    
    
}
