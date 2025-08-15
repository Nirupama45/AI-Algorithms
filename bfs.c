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

void bfs(int start, int dest){
    bool visited[n] = {false};
    int queue[n];
    int front = 0, rear = 0;
    
    visited[start] = true;
    queue[rear++] = start;
    
    while (front < rear){
        int node = queue[front++];
        printf("%d ", node);
        if (node == dest) 
            return; 
        for(int i=0;i<n;i++){
            if(g[node][i] == 1 && !visited[i]){
                visited[i] = true;
                queue[rear++] = i;
            }
        }
    }
}

int main(){
    printf("Path: ");
    bfs(0,6);
    return 0;
}
