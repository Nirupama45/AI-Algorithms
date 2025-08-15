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

int h[n] = {7, 6, 4, 6, 3, 2, 0};

int best = INT_MAX;
int best_path[n+1];
int path[n+1];
int len;

void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

void sort_neighbors(int neighbors[], int count, int cost[]) {
    for(int i=0; i<count-1; i++) {
        for(int j=i+1; j<count; j++) {
            if(cost[i] + h[neighbors[i]] > cost[j] + h[neighbors[j]]) {
                swap(&neighbors[i], &neighbors[j]);
                swap(&cost[i], &cost[j]);
            }
        }
    }
}

void b_and_b_his_heuristic(int curr, int goal, int cost, int l, bool visited[]) {
    path[l] = curr;
    visited[curr] = true;

    if(curr == goal) {
        printf("Path explored: ");
        for(int i=0; i<=l; i++) {
            printf("%d ", path[i]);
        }
        printf(" | Cost: %d\n", cost);

        if(cost < best) {
            best = cost;
            len = l+1;
            for(int i=0; i<len; i++) {
                best_path[i] = path[i];
            }
        }

        visited[curr] = false;
        return;
    }

    int neighbors[n];
    int neighbor_costs[n];
    int count = 0;
    for(int i=0; i<n; i++) {
        if(g[curr][i] != 0 && !visited[i]) {
            neighbors[count] = i;
            neighbor_costs[count] = cost + g[curr][i];
            count++;
        }
    }

    sort_neighbors(neighbors, count, neighbor_costs);

    for(int i=0; i<count; i++) {
        if(neighbor_costs[i] < best) {
            b_and_b_his_heuristic(neighbors[i], goal, neighbor_costs[i], l+1, visited);
        }
    }

    visited[curr] = false;
}

int main() {
    int start = 0;
    int goal = 6;
    bool visited[n] = {false};

    b_and_b_his_heuristic(start, goal, 0, 0, visited);

    printf("\nBest path: ");
    if(best == INT_MAX) {
        printf("No path found.\n");
    } else {
        for(int i=0; i<len; i++) {
            printf("%d ", best_path[i]);
        }
        printf("\nCost: %d\n", best);
    }
}
