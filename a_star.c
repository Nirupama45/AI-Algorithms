#include <stdio.h>
#include <stdbool.h>
#include <math.h>

#define n 7

typedef struct{
    int id;
    int c; //cost so far
    int h; //heuristics
    int tot; //tot = c+h
    int parent;
} node;

int g[n][n] = {
        {0,3,5,0,0,0,0},
        {3,0,4,0,0,5,0},
        {5,4,0,4,0,0,0},
        {0,0,4,0,6,0,0},
        {0,0,0,6,0,0,0},
        {0,5,0,0,0,0,3},
        {0,0,0,0,0,3,0}
    };


int x_coord[n] = {0, 2, 2, 4, 6, 2, 4};
int y_coord[n] = {0, 0, 2, 2, 4, 4, 6};


int heuristic(int a, int b) {
    double dx = x_coord[a] - x_coord[b];
    double dy = y_coord[a] - y_coord[b];
    return (int)(sqrt(dx * dx + dy * dy) + 0.5); // round to nearest int
}

void a_star(int s, int goal){
    node nodes[n];
    bool closed[n] = {false};
    bool open[n] = {false};
    
    for(int i=0;i<n;i++){
        nodes[i].c = 100;
        nodes[i].h = heuristic(i,goal);
        nodes[i].tot = 100;
        nodes[i].parent = -1;
    }
    nodes[s].c = 0;
    nodes[s].tot = nodes[s].h;
    open[s] = true;
    
    while(true){
        int curr = -1;
        int min = 100;
        for(int i=0;i<n;i++){
            if(open[i] && nodes[i].tot < min){
                min = nodes[i].tot;
                curr = i;
            }
        }
        if (curr == -1){
            printf("No path found");
            return;
        }
        if (curr == goal){
            int path[n];
            int count = 0;
            int curr = goal;
            while (curr != -1){
                path[count++] = curr;
                curr = nodes[curr].parent;
            }
            for(int i = count - 1; i >= 0;i--){
                printf("%d ",path[i]);
            }
            printf("\nCost: %d", nodes[goal].c);
            return;
        }
        open[curr] = false;
        closed[curr] = true;
        for(int j = 0; j<n; j++){
            if(g[curr][j] == 0 || closed[j]) continue;
            int temp =  nodes[curr].c + g[curr][j];
            if(!open[j] || temp < nodes[j].c){
                nodes[j].parent = curr;
                nodes[j].c = temp;
                nodes[j].tot = temp + nodes[j].h;
                open[j] = true;
            }
        }
    }
}

int main(){
    int start = 0;
    int goal = 6;
    printf("Path: ");
    a_star(start,goal);
    return 0;
}

