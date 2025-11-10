#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

typedef struct Node {
    char op;       
    int num;       
    int isNum;     
    struct Node* left;
    struct Node* right;
} Node;

char expr[10005];
int pos = 0;

Node* newNum(int num) {
    Node* node = (Node*)malloc(sizeof(Node));
    node->num = num;
    node->isNum = 1;
    node->left = node->right = NULL;
    return node;
}

Node* newOp(char op, Node* left, Node* right) {
    Node* node = (Node*)malloc(sizeof(Node));
    node->op = op;
    node->isNum = 0;
    node->left = left;
    node->right = right;
    return node;
}

void skipSpaces() {
    while (expr[pos] == ' ') pos++;
}

void printPreorder(Node* root) {
    if (!root) return;
    if (root->isNum) printf("%d ", root->num);
    else printf("%c ", root->op);
    printPreorder(root->left);
    printPreorder(root->right);
}

Node* parseExpr();
Node* parseTerm();
Node* parseFactor();

Node* parseFactor() {
    skipSpaces();
    if (expr[pos] == '(') {
        pos++; // skip '('
        Node* node = parseExpr();
        skipSpaces();
        pos++; // skip ')'
        return node;
    } else {
        int num = 0;
        while (isdigit(expr[pos])) {
            num = num * 10 + (expr[pos++] - '0');
        }
        return newNum(num);
    }
}

Node* parseTerm() {
    Node* node = parseFactor();
    while (1) {
        skipSpaces();
        if (expr[pos] == '*' || expr[pos] == '/') {
            char op = expr[pos++];
            Node* right = parseFactor();
            node = newOp(op, node, right);
        } else break;
    }
    return node;
}

Node* parseExpr() {
    Node* node = parseTerm();
    while (1) {
        skipSpaces();
        if (expr[pos] == '+' || expr[pos] == '-') {
            char op = expr[pos++];
            Node* right = parseTerm();
            node = newOp(op, node, right);
        } else break;
    }
    return node;
}

int calc(Node* root) {
    if (root->isNum) return root->num;
    int a = calc(root->left);
    int b = calc(root->right);
    switch (root->op) {
        case '+': return a + b;
        case '-': return a - b;
        case '*': return a * b;
        case '/': return a / b;
    }
    return 0;
}

int main() {
    fgets(expr, sizeof(expr), stdin);
    Node* root = parseExpr();

    int result = calc(root); 
    printf("%d\n", result);

    printPreorder(root);
    printf("\n");

    return 0;
}
