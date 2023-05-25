#include <iostream>
#include <string.h>
#include <vector>
#include<string>

using namespace std;

const int MAX_PROCESSES = 100;
const int MAX_RESOURCES = 100;

int allocated[MAX_PROCESSES][MAX_RESOURCES];
int max_need[MAX_PROCESSES][MAX_RESOURCES];
int need[MAX_PROCESSES][MAX_RESOURCES];
int available[MAX_RESOURCES];
int num_processes, num_resources;

vector<int> safe_sequence;

bool check_number(string str) {
   for (int i = 0; i < str.length(); i++)
   if (isdigit(str[i]) == false)
      return false;
      return true;
}


void print_safe_sequence() {
    for (int i = 0; i < safe_sequence.size(); i++) {
        cout << "P" << safe_sequence[i] << "  ";
		
    }
    cout << endl;
}

bool is_safe(int process_id) {
    for (int i = 0; i < num_resources; i++) {
        if (need[process_id][i] > available[i]) {
            return false;
        }
    }
    return true;
}

bool find_safe_sequence(bool marked[]) {
    bool found_safe_sequence = false;
    for (int i = 0; i < num_processes; i++) {
        if (!marked[i] && is_safe(i)) {
            marked[i] = true;
            for (int j = 0; j < num_resources; j++) {
                available[j] += allocated[i][j];
            }
            safe_sequence.push_back(i);
            if (find_safe_sequence(marked)) {
                found_safe_sequence = true;
            }
            safe_sequence.pop_back();
            for (int j = 0; j < num_resources; j++) {
                available[j] -= allocated[i][j];
            }
            marked[i] = false;
        }
    }
    if (!found_safe_sequence) {
        if (safe_sequence.size() == num_processes) {
            print_safe_sequence();
            return true;
        } else {
            return false;
        }
    }
    return true;
}

// Function to check if a request can be granted
bool is_request_grantable(int process_id, int request[]) {
    for (int i = 0; i < num_resources; i++) {
        if (request[i] > need[process_id][i] || request[i] > available[i]) {
            return false;
        }
    }
    return true;
}

// Function to grant a request
void grant_request(int process_id, int request[]) {
    for (int i = 0; i < num_resources; i++) {
        available[i] -= request[i];
        allocated[process_id][i] += request[i];
        need[process_id][i] -= request[i];
    }
}

int main() {
    string nprocesses ;
	xyz: 
    cout << "Enter the number of processes: ";
    cin >> nprocesses;
    if (!check_number(nprocesses))
    {
        cout << "Number of Processes can't be non integer\n\n";
        goto xyz;
    }

    num_processes=stoi(nprocesses);

    string nresources;

    abc:
    cout << "Enter the number of resources: ";
    cin >> nresources;
     if (!check_number(nresources))
    {
        cout << "Number of Resources can't be non integer\n\n";
        goto abc;
    }

    num_resources=stoi(nresources);

    cout << "Enter the allocation matrix:\n";
    for (int i = 0; i < num_processes; i++) {
        for (int j = 0; j < num_resources; j++) {
            cin >> allocated[i][j];
        }
    }

    cout << "Enter the maximum need matrix:\n";
    for (int i = 0; i < num_processes; i++) {
        for (int j = 0; j < num_resources; j++) {
            cin >> max_need[i][j];
            need[i][j] = max_need[i][j] - allocated[i][j];
        }
    }

    cout << "Enter the available resources:\n";
    for (int i = 0; i < num_resources; i++) {
        cin >> available[i];
    }
   
    // for(int j=0;j<num_resources;j++){
    //     if(max_need[1][j]-allocated[1][j]>available[j]){
    //         cout<<"Allocated should be less than available resources"<<endl;
    //         return 0;
    //     }
    // }

    bool marked[num_processes];
    memset(marked, false, sizeof(marked));

    cout << "\nSafe sequences are:\n\n";

    find_safe_sequence(marked);


    while (true) {
    // Get request from user
    int process_id;
    int request[MAX_RESOURCES];
    cout << "\nEnter process ID that is making the request: ";
    cin >> process_id;
    if (process_id >= num_processes) {
        cout << "Invalid process ID.\n";
        continue;
    }
    cout << "Enter the request: ";
    for (int i = 0; i < num_resources; i++) {
        cin >> request[i];
    }

    // Check if request can be granted
    if (is_request_grantable(process_id, request)) {
        // Grant request
        grant_request(process_id, request);

        // Check if system is still in a safe state
        bool marked[num_processes];
        memset(marked, false, sizeof(marked));
        if (find_safe_sequence(marked)) {
            cout << "\nRequest granted. Safe sequences are:\n\n";
            continue;
        } else {
            // Request cannot be granted, revert changes
            for (int i = 0; i < num_resources; i++) {
                available[i] += request[i];
                allocated[process_id][i] -= request[i];
                need[process_id][i] += request[i];
            }
            cout << "\nRequest cannot be granted without leading to an unsafe state.\n";
            continue;
        }
    } else {
        cout << "\nRequest cannot be granted as it exceeds the maximum need or available resources.\n";
        continue;
    }
}


    
    return 0;
}
