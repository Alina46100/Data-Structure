#include "mst.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    Edge **data;
    int size;
    int capacity;
} MinHeap;

MinHeap *createHeap(int cap) {
    MinHeap *h = (MinHeap *)malloc(sizeof(MinHeap));
    h->data = (Edge **)malloc(sizeof(Edge *) * (cap + 1));
    h->size = 0;
    h->capacity = cap;
    return h;
}

void push(MinHeap *h, Edge *e) {
    if (h->size >= h->capacity) return;
    int i = ++h->size;
    while (i > 1 && h->data[i / 2]->w > e->w) {
        h->data[i] = h->data[i / 2];
        i /= 2;
    }
    h->data[i] = e;
}

Edge *pop(MinHeap *h) {
    if (h->size == 0) return NULL;
    Edge *min = h->data[1];
    Edge *last = h->data[h->size--];
    int i = 1, child;
    while (i * 2 <= h->size) {
        child = i * 2;
        if (child < h->size && h->data[child]->w > h->data[child + 1]->w)
            child++;
        if (last->w <= h->data[child]->w) break;
        h->data[i] = h->data[child];
        i = child;
    }
    h->data[i] = last;
    return min;
}

void generate_mst(Node *start) {
    static char visited[MAX_NODES];
    memset(visited, 0, sizeof(visited));

    MinHeap *heap = createHeap(MAX_EDGES);
    int visited_count = 0;

    visited[start->id] = 1;
    visited_count++;

    for (int i = 0; i < start->edge_count; i++) {
        push(heap, start->edges[i]);
    }

    while (heap->size > 0) {
        Edge *e = pop(heap);
        Node *u = e->u;
        Node *v = e->v;

        Node *next = NULL;
        if (visited[u->id] && !visited[v->id])
            next = v;
        else if (visited[v->id] && !visited[u->id])
            next = u;
        else
            continue;

        e->keep = 1;
        visited[next->id] = 1;
        visited_count++;

        for (int i = 0; i < next->edge_count; i++) {
            Edge *ne = next->edges[i];
            Node *a = ne->u, *b = ne->v;
            if (!visited[a->id] || !visited[b->id])
                push(heap, ne);
        }

        //if (visited_count >= MAX_NODES) break; 
}
    free(heap->data);
    free(heap);

}
