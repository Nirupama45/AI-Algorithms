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

void bfs_h(int start, int dest){
    bool visited[n] = {false};
    int queue[n];
    int parent[n];
    int front = 0, rear = 0;
    
    for(int i=0; i<n; i++){
        parent[i]=-1;
    }
    visited[start] = true;
    queue[rear++] = start;
    
    while (front < rear){
        int node = queue[front++];
        if (node == dest) {
            int path[n];
            int c = 0;
            for(int i = dest; i!= -1; i = parent[i]){
                path[c++] = i;
            }
            for(int i= c-1 ;i >= 0; i--){
                printf("%d ", path[i]);
            }
        return;
        }
        for(int i=0; i<n; i++){
            if(g[node][i] == 1 && !visited[i]){
                visited[i] = true;
                parent[i] = node;
                queue[rear++] = i;
            }
        }
    }
    printf("No path found");
}

int main(){
    printf("Path: ");
    bfs_h(0,6);
    return 0;
}
