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
    int path[20];
    int path_len;
} Node;

int visited_in_path(Node s, int node) {
    for (int i = 0; i < s.path_len; i++)
        if (s.path[i] == node) return 1;
    return 0;
}

void copy_node(Node *dest, Node src) {
    dest->node = src.node;
    dest->cost = src.cost;
    dest->path_len = src.path_len;
    for (int i = 0; i < src.path_len; i++)
        dest->path[i] = src.path[i];
}

void beam_search(int start, int goal) {
    Node beam[50];
    int beam_size = 0;

    Node start_node = {start, 0, {start}, 1};
    beam[beam_size++] = start_node;

    while (beam_size > 0) {
        for (int i = 0; i < beam_size; i++) {
            if (beam[i].node == goal) {
                printf("Path: ");
                for (int j = 0; j < beam[i].path_len; j++)
                    printf("%d ", beam[i].path[j]);
                printf("\nTotal distance: %d\n", beam[i].cost);
                return;
            }
        }

        Node new_beam[50];
        int new_size = 0;

        for (int i = 0; i < beam_size; i++) {
            Node current = beam[i];
            for (int nb = 0; nb < n; nb++) {
                if (graph[current.node][nb] > 0 && !visited_in_path(current, nb)) {
                    Node child;
                    copy_node(&child, current);
                    child.node = nb;
                    child.cost += graph[current.node][nb];
                    child.path[child.path_len++] = nb;
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
        } else {
            beam_size = w;
        }    
        for (int i = 0; i < beam_size; i++)
            beam[i] = new_beam[i];
    }

    printf("Goal not found.\n");
}

int main() {
    beam_search(0, 6);
    return 0;
}
