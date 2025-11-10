#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct node {
    int key;
    struct node* leftChild;
    struct node* rightChild;
};

struct node* newNode(int key);
struct node* insert(struct node* root, int key);
struct node* search(struct node* root, int key);
struct node* deleteNode(struct node* root, int key);
void inorderPrint(struct node* root);
// 層序列印
void levelOrderPrint(struct node* root) {
    if (root == NULL) return;

    struct node* queue[3000]; // 假設最多 1000 個節點
    int front = 0, rear = 0;

    queue[rear++] = root;

    while (front < rear) {
        struct node* curr = queue[front++];
        printf("%d ", curr->key);

        if (curr->leftChild != NULL)
            queue[rear++] = curr->leftChild;
        if (curr->rightChild != NULL)
            queue[rear++] = curr->rightChild;
    }
}
int main() {
    struct node* root = NULL;
    char command[10];
    int key;

    while (1) {
        scanf("%s", command);
        if (strcmp(command, "exit") == 0) break;
        scanf("%d", &key);

        if (strcmp(command, "insert") == 0) {
            root = insert(root, key);  // 更新 root
        } else if (strcmp(command, "delete") == 0) {
            root = deleteNode(root, key); // 更新 root
        }
    }

    levelOrderPrint(root);
    printf("\n");
    return 0;
}

// 建立新節點
struct node* newNode(int key) {
    struct node* node = (struct node*)malloc(sizeof(struct node));
    node->key = key;
    node->leftChild = NULL;
    node->rightChild = NULL;
    return node;
}

// 插入節點
struct node* insert(struct node* root, int key) {
    if (root == NULL) return newNode(key);

    if (key < root->key)
        root->leftChild = insert(root->leftChild, key);
    else if (key > root->key)
        root->rightChild = insert(root->rightChild, key);

    return root;
}

// 搜尋節點
struct node* search(struct node* root, int key) {
    while (root != NULL && root->key != key) {
        if (key < root->key)
            root = root->leftChild;
        else
            root = root->rightChild;
    }
    return root;
}

// 刪除節點
struct node* deleteNode(struct node* root, int key) {
    if (root == NULL) return NULL;

    if (key < root->key)
        root->leftChild = deleteNode(root->leftChild, key);
    else if (key > root->key)
        root->rightChild = deleteNode(root->rightChild, key);
    else {
        // 找到要刪除的節點
        if (root->leftChild == NULL) {
            struct node* temp = root->rightChild;
            free(root);
            return temp;
        } else if (root->rightChild == NULL) {
            struct node* temp = root->leftChild;
            free(root);
            return temp;
        } else {
            // 兩個子節點
            struct node* temp = root->rightChild;
            // 找右子樹最左節點
            while (temp->leftChild != NULL)
                temp = temp->leftChild;
            root->key = temp->key; // 用中序後繼取代
            root->rightChild = deleteNode(root->rightChild, temp->key); // 刪掉後繼節點
        }
    }
    return root;
}


