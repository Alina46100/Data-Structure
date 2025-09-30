#include <stdio.h>
#include <stdlib.h>

#define MAXN 100000

int arrayA[MAXN];
int stack[MAXN];
int top = -1;
int queue[MAXN];
int front = 0, rear = 0;

int main() {
    int N;
    scanf("%d", &N);
    for (int i = 1; i <= N; i++) {
        scanf("%d", &arrayA[i]);
    }

    for (int i = 1; i <= N; i++) {
        while (top >= 0 && arrayA[stack[top]] >= arrayA[i]) {
            top--;
        }

        if (top >= 0) {
            int dist = i - stack[top];
            queue[rear++] = dist;
        } else {
        }

        // push index
        stack[++top] = i;
    }

    if (rear == 0) {
        printf("EMPTY\n");
    } else {
        for (int i = front; i < rear; i++) {
            printf("%d", queue[i]);
            if (i < rear - 1) printf(" ");
        }
        printf("\n");
    }

    return 0;
}
