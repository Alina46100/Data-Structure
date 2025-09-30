#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_INIT 255
#define MAX_OP 2200000

char left[MAX_OP + MAX_INIT];
char right[MAX_OP + MAX_INIT];  

int main() {
    char init[MAX_INIT + 1];
    scanf("%s", init);
    int left_top = 0, right_top = 0;

    // u d9 g3
    for (int i = 0; init[i]; i++) {
        left[left_top++] = init[i];
    }

    int M;
    scanf("%d", &M);
    getchar(); // consume newline

    for (int i = 0; i < M; i++) {
        char op;
        op = getchar();

        if (op == 'L') {
            if (left_top > 0) right[right_top++] = left[--left_top];
        } else if (op == 'R') {
            if (right_top > 0) left[left_top++] = right[--right_top];
        } else if (op == 'D') {
            if (left_top > 0) left_top--;
        } else if (op == 'I') {
            getchar(); // consume space
            char c = getchar();
            left[left_top++] = c;
        }
        getchar(); // consume newline
    }

    for (int i = 0; i < left_top; i++) putchar(left[i]);//左
    
    for (int i = right_top - 1; i >= 0; i--) putchar(right[i]);//又
    putchar('\n');

    return 0;
}
