#include <stdio.h>
#include <string.h>

#define MAXN 2000005  

int L[MAXN], R[MAXN], val[MAXN];
int head = 0, tail = 0;

int main() {
    int N, Q;
    scanf("%d %d", &N, &Q);
    for (int i = 1; i <= N; i++) {
        scanf("%d", &val[i]);
        L[i] = i - 1;
        R[i] = (i == N ? 0 : i + 1);
    }
    head = 1;
    tail = N;

    int cur_id = N;

    for (int qi = 0; qi < Q; qi++) {
        char op[5];
        scanf("%s", op);

        if (strcmp(op, "H") == 0) {
            int x; 
            scanf("%d", &x);
            int id = ++cur_id;
            val[id] = x;
            L[id] = 0;
            R[id] = head;
            if (head != 0) L[head] = id;
            head = id;
            if (tail == 0) tail = id;
        }
        else if (strcmp(op, "T") == 0) {
            int x; 
            scanf("%d", &x);
            int id = ++cur_id;
            val[id] = x;
            R[id] = 0;
            L[id] = tail;
            if (tail != 0) R[tail] = id;
            tail = id;
            if (head == 0) head = id;
        }
        else if (strcmp(op, "A") == 0) {
            int k, x; 
            scanf("%d %d", &k, &x);
            int id = ++cur_id;
            val[id] = x;
            R[id] = R[k];
            L[id] = k;
            if (R[k] != 0) L[R[k]] = id;//原k+1接上id
            R[k] = id;
            if (tail == k) tail = id;
        }
        else if (strcmp(op, "B") == 0) {
            int k, x; 
            scanf("%d %d", &k, &x);
            int id = ++cur_id;
            val[id] = x;
            L[id] = L[k];
            R[id] = k;
            if (L[k] != 0) R[L[k]] = id;//原k-1接上id
            L[k] = id;
            if (head == k) head = id;
        }
        else if (strcmp(op, "D") == 0) {
            int k; 
            scanf("%d", &k);
            if (L[k] != 0) R[L[k]] = R[k];//k左邊的元素右邊接到原k的右邊
            else head = R[k];
            if (R[k] != 0) L[R[k]] = L[k];
            else tail = L[k];
        }
        else if (strcmp(op, "MH") == 0) {
            int k; 
            scanf("%d", &k);
            if (k != head) {
                if (L[k] != 0) R[L[k]] = R[k];
                if (R[k] != 0) L[R[k]] = L[k];
                if (k == tail) tail = L[k];
                L[k] = 0;
                R[k] = head;
                L[head] = k;
                head = k;
            }
        }
        else if (strcmp(op, "MT") == 0) {
            int k; 
            scanf("%d", &k);
            if (k != tail) {
                if (L[k] != 0) R[L[k]] = R[k];
                if (R[k] != 0) L[R[k]] = L[k];
                if (k == head) head = R[k];
                R[k] = 0;
                L[k] = tail;
                R[tail] = k;
                tail = k;
            }
        }
    }
    // 從 head 到 tail
    for (int i = head; i != 0; i = R[i]) {
        printf("%d", val[i]);
        if (R[i] != 0) printf(" ");
    }
    if((head == tail)&&(tail == 0)){ 
        printf("EMPTY\n");    
    }
    else{
        printf("\n");
    }

    // 從 tail 到 head
    for (int i = tail; i != 0; i = L[i]) {
        printf("%d", val[i]);
        if (L[i] != 0){ 
            printf(" ");
        }
    }
    if((head == tail)&&(tail == 0)){ 
        printf("EMPTY");    
    }
    else{
        printf("\n");
    }

    return 0;
}
