#include <stdio.h>
#include <stdbool.h>

#define n 7

int g[n][n] = {
    {0,1,1,0,0,0,0},
    {1,0,1,0,0,1,0},
    {1,1,0,1,0,0,0},
    {0,0,1,0,1,0,0},
    {0,0,0,1,0,0,0},
    {0,1,0,0,0,0,1},
    {0,0,0,0,0,1,0}
};

int h[n];

void compute_heuristic(int goal){
    int queue[n];
    int front = 0;
    int rear = 0;
    bool visited[n] = {false};
    
    for(int i=0; i<n; i++){
        h[i] = -1;
    }
    
    h[goal] = 0;
    visited[goal] = true;
    queue[rear++] = goal;
    
    while (front < rear){
        int i = queue[front++];
        for(int j =0; j<n; j++){
            if(g[i][j] && !visited[j]){
                visited[j] = true;
                h[j] = h[i] + 1;
                queue[rear++] = j;
            }
        }
    }
}

void hc(int start, int goal) {
    int curr = start;
    int history[n];
    int len = 0;

    while (true) {
        history[len++] = curr;

        if (curr == goal) {
            break;
        }

        int next = -1;
        int best_h = h[curr]; 

        for (int i = 0; i < n; i++) {
            if (g[curr][i] == 1) { 
                if (h[i] < best_h) { 
                    best_h = h[i];
                    next = i;
                }
            }
        }

        if (next == -1) { 
            printf("Can't move further.\n");
            return;
        }

        curr = next; 
    }
    for(int i=0; i<len; i++){
        printf("%d ",history[i]);
    }
    
}

int main() {
    int start = 0;
    int goal = 6;
    compute_heuristic(goal);
    printf("Path: ");
    hc(start, goal);
    return 0;
}
