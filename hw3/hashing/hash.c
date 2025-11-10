#include "hash.h"
#include <stdlib.h>

#define TABLE_SIZE 10007

typedef struct Node {
    Data data;             
    struct Node *next;
} Node;

static Node* hash_table[TABLE_SIZE] = {0};

static int hash(int key) {
    if (key < 0) key = -key; 
    return key % TABLE_SIZE;
}

void insert(Data *data) {
    int h = hash(data->key);
    Node *node = malloc(sizeof(Node));
    if (!node) return; 
    node->data = *data;  
    node->next = hash_table[h];
    hash_table[h] = node;
}

void remove(int key) {
    int h = hash(key);
    Node *prev = NULL;
    Node *cur = hash_table[h];
    while (cur) {
        if (cur->data.key == key) {
            if (prev)
                prev->next = cur->next;
            else
                hash_table[h] = cur->next;
            free(cur);
            return;
        }
        prev = cur;
        cur = cur->next;
    }
}

int search(int key) {
    int h = hash(key);
    Node *cur = hash_table[h];
    while (cur) {
        if (cur->data.key == key)
            return cur->data.value;
        cur = cur->next;
    }
    return -1;
}
