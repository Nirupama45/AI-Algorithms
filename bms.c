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
int path[100];
int goal;
    
void bms(int curr, bool visited[], int len){
    path[len++] = curr;
        
    if (curr == goal) {
        for (int i = 0; i < len; i++)
            printf("%d ", path[i]);
        printf("\n");
        return;
    }
    
    visited[curr] = true;
    for (int i = 0; i < n; i++) {
        if (g[curr][i] == 1 && !visited[i]) {
            bms(i,visited,len);
        }
    }
    visited[curr] = false;
}

int main() {
    bool visited[n] = {false};
    int start = 0;
    goal = 6;
    printf("Path: ");
    bms(start,visited,0);
    return 0;
}
