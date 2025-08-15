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
int goal;
bool found = false;

void dfs(int curr, bool visited[]){
    printf("%d ",curr);
        
    if (curr == goal) {
        found = true;
        return;
    }
    
    visited[curr] = true;
    for (int i = 0; i < n && !found; i++) {
        if (g[curr][i] == 1 && !visited[i]) {
            dfs(i,visited);
        }
    }
    visited[curr] = false;
}

int main() {
    bool visited[n] = {false};
    int start = 0;
    goal = 6;
    printf("Path: ");
    dfs(start,visited);
    return 0;
}
