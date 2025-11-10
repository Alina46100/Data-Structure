#include <stdio.h>
#include <stdlib.h>

#ifndef gc
# ifdef _WIN32
#  define gc getchar
# else
#  define gc getchar_unlocked
# endif
#endif

static inline int read_int() {
    int c = gc();
    while (c <= 32) c = gc();
    int sign = 1;
    if (c == '-') { sign = -1; c = gc(); }
    int x = 0;
    while (c > 32) {
        x = x * 10 + (c - '0');
        c = gc();
    }
    return x * sign;
}

int main() {
    int N = read_int();
    int D = read_int();

    // maloca
    int *head = (int*)malloc(sizeof(int) * N);
    if (!head) return 0;
    for (int i = 0; i < N; ++i) head[i] = -1;

    int *to = (int*)malloc(sizeof(int) * D);
    int *nxt = (int*)malloc(sizeof(int) * D);
    if (D > 0 && (!to || !nxt)) return 0;

    int *indeg = (int*)malloc(sizeof(int) * N);
    if (!indeg) return 0;
    for (int i = 0; i < N; ++i) indeg[i] = 0;

    // edges
    for (int i = 0; i < D; ++i) {
        int u = read_int();
        int v = read_int();
        to[i] = v;
        nxt[i] = head[u];
        head[u] = i;
        indeg[v]++; 
    }

    
    int *queue = (int*)malloc(sizeof(int) * N);
    if (!queue) return 0;
    int qh = 0, qt = 0;

    
    for (int i = 0; i < N; ++i) {
        if (indeg[i] == 0) {
            queue[qt++] = i;
        }
    }

    long long processed = 0;
    while (qh < qt) {
        int u = queue[qh++];
        processed++;
        for (int e = head[u]; e != -1; e = nxt[e]) {
            int v = to[e];
            indeg[v]--;
            if (indeg[v] == 0) {
                queue[qt++] = v;
            }
        }
    }

    if (processed == N) printf("0\n"); // ao6迴圈
    else printf("1\n"); //

 
    free(head);
    free(to);
    free(nxt);
    free(indeg);
    free(queue);

    return 0;
}
