#include <stdio.h>

#define n 7
#define w 2

int graph[n][n] = {
    {0,3,5,0,0,0,0},
    {3,0,4,0,0,5,0},
    {5,4,0,4,0,0,0},
    {0,0,4,0,6,0,0},
    {0,0,0,6,0,0,0},
    {0,5,0,0,0,0,3},
    {0,0,0,0,0,3,0}
};

int h[] = {6, 7, 6, 7, 3, 4, 0};

typedef struct {
    int node;
    int cost;
    int parent;       
} Node;

int visited[n];       

void print_path(Node nodes[], int goal) {
    int path[20];
    int length = 0;
    int current = goal;
    while (current != -1) {
        path[length++] = current;
        current = nodes[current].parent;
    }
    printf("Path: ");
    for (int i = length - 1; i >= 0; i--) {
        printf("%d", path[i]);
        if (i > 0) printf(" ");
    }
    printf("\nCost: %d\n", nodes[goal].cost);
}

void beam_search(int start, int goal) {
    Node beam[50];
    int beam_size = 0;

    Node nodes[n];
    for (int i = 0; i < n; i++) {
        nodes[i].node = i;
        nodes[i].cost = 0;
        nodes[i].parent = -1; 
        visited[i] = 0;
    }

    nodes[start].cost = 0;
    beam[beam_size++] = nodes[start];

    while (beam_size > 0) {
        Node new_beam[50];
        int new_size = 0;

        for (int i = 0; i < beam_size; i++) {
            Node current = beam[i];
            visited[current.node] = 1;

            for (int nb = 0; nb < n; nb++) {
                if (graph[current.node][nb] > 0 && !visited[nb]) {
                    Node child;
                    child.node = nb;
                    child.cost = current.cost + graph[current.node][nb];
                    child.parent = current.node;

                    nodes[nb].cost = child.cost;
                    nodes[nb].parent = child.parent;

                    new_beam[new_size++] = child;
                }
            }
        }

        for (int i = 0; i < new_size - 1; i++) {
            for (int j = i + 1; j < new_size; j++) {
                if (h[new_beam[j].node] < h[new_beam[i].node]) {
                    Node temp = new_beam[i];
                    new_beam[i] = new_beam[j];
                    new_beam[j] = temp;
                }
            }
        }

        if (new_size < w) {
            beam_size = new_size;
        } 
        else {
            beam_size = w;
        }
        for (int i = 0; i < beam_size; i++)
            beam[i] = new_beam[i];

        for (int i = 0; i < beam_size; i++) {
            if (beam[i].node == goal) {
                print_path(nodes, goal);
                return;
            }
        }
    }

    printf("Goal not found.\n");
}

int main() {
    beam_search(0, 6);
    return 0;
}
