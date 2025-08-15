#include <stdio.h>
#include <string.h>

#define N 7
#define INF 999999

int w[N][N] = {
    {0, 3, 5, INF, INF, INF, INF},
    {3, 0, 4, INF, INF, 5, INF},
    {5, 4, 0, 4, INF, INF, INF},
    {INF, INF, 4, 0, 6, INF, INF},
    {INF, INF, INF, 6, 0, INF, INF},
    {INF, 5, INF, INF, INF, 0, 3},
    {INF, INF, INF, INF, INF, 3, 0}
};

typedef struct {
    int nodes[32];
    int len;
    int cost;
} Path;

Path all[64];
int cnt = 0;

int visited[N];
int cur[32], cur_len = 0;

int lex_cmp(const Path *a, const Path *b) {
    int i = 0;
    while (i < a->len && i < b->len) {
        if (a->nodes[i] != b->nodes[i]) return a->nodes[i] - b->nodes[i];
        i++;
    }
    return (a->len - b->len);
}

void save_path(int cost) {
    all[cnt].len  = cur_len;
    all[cnt].cost = cost;
    for (int i = 0; i < cur_len; i++) all[cnt].nodes[i] = cur[i];
    cnt++;
}

void dfs(int u, int goal, int cost) {
    if (u == goal) { save_path(cost); return; }

    for (int v = 0; v < N; v++) {             
        if (w[u][v] != INF && !visited[v]) {
            visited[v] = 1;
            cur[cur_len++] = v;
            dfs(v, goal, cost + w[u][v]);
            cur_len--;
            visited[v] = 0;
        }
    }
}

int main(void) {
    memset(visited, 0, sizeof(visited));

    visited[0] = 1;
    cur[cur_len++] = 0;
    dfs(0, 6, 0);

    for (int i = 0; i < cnt - 1; i++) {
        for (int j = i + 1; j < cnt; j++) {
            int swap = 0;
            if (all[i].cost > all[j].cost) swap = 1;
            else if (all[i].cost == all[j].cost && lex_cmp(&all[i], &all[j]) > 0) swap = 1;
            if (swap) { Path t = all[i]; all[i] = all[j]; all[j] = t; }
        }
    }

    printf("All paths:\n");
    for (int i = 0; i < cnt; i++) {
        printf("R%d: ", i + 1);
        for (int k = 0; k < all[i].len; k++) {
            printf("%d", all[i].nodes[k]);
            if (k + 1 < all[i].len) printf("->");
        }
        printf("  Cost=%d\n", all[i].cost);
    }

    printf("\nGround truth (R  P  nodes  cost):\n");
    for (int i = 0; i < cnt; i++) {
        printf("R%d  P%d  %d  %d\n", i + 1, i + 1, all[i].len, all[i].cost);
    }
    return 0;
}
