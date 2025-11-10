#include <stdio.h>
#include <stdlib.h>

#define MAXM 10005
#define MAXN 10005

typedef struct {
    int x, y, d;
} Node;

char maze[MAXM][MAXN + 1];
int M, N;
int visited[MAXM][MAXN];
int used[26];           // ifituseq
int px[26][2], py[26][2], pcount[26];

int dx[4] = {1, -1, 0, 0};
int dy[4] = {0, 0, 1, -1};

int main() {
    scanf("%d %d", &M, &N);

    int sx = -1, sy = -1;
    int ex = -1, ey = -1;

    for (int i = 0; i < M; i++) {
        scanf("%s", maze[i]);
        for (int j = 0; j < N; j++) {
            char c = maze[i][j];
            if (c == 'B') {
                sx = i; sy = j;
            } else if (c == 'E') {
                ex = i; ey = j;
            } else if (c >= 'A' && c <= 'Z') {
                int id = c - 'A';
                px[id][pcount[id]] = i;
                py[id][pcount[id]] = j;
                pcount[id]++;
            }
        }
    }

    Node *queue = (Node*)malloc(sizeof(Node) * M * N);
    int front = 0, rear = 0;
    queue[rear++] = (Node){sx, sy, 0};
    visited[sx][sy] = 1;

    while (front < rear) {
        Node cur = queue[front++];
        int x = cur.x, y = cur.y, d = cur.d;

        if (x == ex && y == ey) {
            printf("%d\n", d);
            free(queue);
            return 0;
        }

        // 四個方向移動
        for (int k = 0; k < 4; k++) {
            int nx = x + dx[k];
            int ny = y + dy[k];
            if (nx < 0 || ny < 0 || nx >= M || ny >= N) continue;
            if (maze[nx][ny] == '#' || visited[nx][ny]) continue;
            visited[nx][ny] = 1;
            queue[rear++] = (Node){nx, ny, d + 1};
        }

        // 傳送
        if (maze[x][y] >= 'A' && maze[x][y] <= 'Z') {
            int id = maze[x][y] - 'A';
            if (!used[id] && pcount[id] == 2) {
                used[id] = 1; // 傳送只用一次
                for (int t = 0; t < 2; t++) {
                    int nx = px[id][t];
                    int ny = py[id][t];
                    if (!visited[nx][ny]) {
                        visited[nx][ny] = 1;
                        queue[rear++] = (Node){nx, ny, d + 1};
                    }
                }
            }
        }
    }

    printf("-1\n");
    free(queue);
    return 0;
}
