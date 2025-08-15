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

void bfsdfs(int start, int dest) {
    bool visited[n] = {false};
    int stack[n];  
    int queue[n];  
    int top = -1;
    int front = 0, rear = 0;

    stack[++top] = start;
    visited[start] = true;

    printf("Path: ");

    while (top >= 0) {
        int node = stack[top--];  
        printf("%d ", node);
        if (node == dest) return;

        for (int i = 0; i < n; i++) {
            if (g[node][i] == 1 && !visited[i]) {
                visited[i] = true;
                queue[rear++] = i;
            }
        }

        while (front < rear) {
            stack[++top] = queue[front++];
        }
    }
}

int main() {
    bfsdfs(0, 6);
    return 0;
}
