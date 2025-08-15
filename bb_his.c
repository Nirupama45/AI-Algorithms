#include <stdio.h>
#include <stdbool.h>
#include <limits.h>

#define n 7

int g[n][n] = {
    {0,3,5,0,0,0,0},
    {3,0,4,0,0,5,0},
    {5,4,0,4,0,0,0},
    {0,0,4,0,6,0,0},
    {0,0,0,6,0,0,0},
    {0,5,0,0,0,0,3},
    {0,0,0,0,0,3,0}
};

int best = INT_MAX;
int best_path[n+1];
int path[n+1];
int len;

void b_and_b_his(int curr, int goal, int cost, int l, bool visited[]){
    path[l] = curr;
    visited[curr] = true;
    
    if(curr == goal){
        printf("Path explored: ");
        for(int i=0; i<=l; i++) {
            printf("%d ", path[i]);
        }
        printf("Cost: %d\n", cost);
        if(cost < best){
            best = cost;
            len = l+1;
            for(int i=0; i<len; i++){
                best_path[i] = path[i];
            }
        }
        visited[curr] = false;
        return;
    }
    for (int i = 0; i < n; i++) {
        if (g[curr][i] != 0 && !visited[i]) {
            b_and_b(i, goal, cost + g[curr][i], l + 1, visited);
        }
    }
    visited[curr] = false;
}

int main(){
    int start = 0;
    int goal = 6;
    bool visited[n] = {false};
    b_and_b_his(start,goal,0,0,visited);
    printf("Best path: ");
    if (best == INT_MAX) {
        printf("No path found.\n");
    } 
    else {
        for (int i = 0; i < len; i++) {
            printf("%d ", best_path[i]);
        }
        printf("\nCost: %d", best);
    }
}
