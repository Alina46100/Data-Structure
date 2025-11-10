#include <stdio.h>
#include <stdlib.h>

#define MAXN 2000005
#define MAXM 2700005

static int parent[MAXN];
static unsigned char rankArr[MAXN];
static int u[MAXM], v[MAXM];
static int collapse[MAXM];
static char collapsed[MAXM];
static int result[MAXM];

//
static inline int find(int x) {
    while (x != parent[x]) {
        parent[x] = parent[parent[x]]; 
        x = parent[x];
    }
    return x;
}


static inline int unite(int a, int b) {
    a = find(a);
    b = find(b);
    if (a == b) return 0;
    if (rankArr[a] < rankArr[b])
        parent[a] = b;
    else if (rankArr[a] > rankArr[b])
        parent[b] = a;
    else {
        parent[b] = a;
        rankArr[a]++;
    }
    return 1;
}

int main() {
    int n, m, q;
    if (scanf("%d %d %d", &n, &m, &q) != 3) return 0;

    for (int i = 0; i < m; i++) scanf("%d %d", &u[i], &v[i]);
    for (int i = 0; i < q; i++) {
        scanf("%d", &collapse[i]);
        collapse[i]--;
        collapsed[collapse[i]] = 1;
    }


    for (int i = 0; i < n; i++) {
        parent[i] = i;
        rankArr[i] = 0;
    }

    int alliances = n;


    for (int i = 0; i < m; i++) {
        if (!collapsed[i]) {
            if (unite(u[i], v[i]))
                alliances--;
        }
    }

    int idx = 0;
    result[idx++] = alliances;

    for (int i = q - 1; i >= 0; i--) {
        int e = collapse[i];
        if (unite(u[e], v[e]))
            alliances--;
        result[idx++] = alliances;
    }


    for (int i = idx - 1; i >= 0; i--) {
        printf("%d\n", result[i]);
    }

    return 0;
}
