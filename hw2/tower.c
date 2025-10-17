#include <stdio.h>
#include <string.h>
void addNode(int nNumber);
void topMinusSecond();
void deleteNode(int deleteThisNode);
void addDeltaToidx(int idx, int Delta);
void sortUp(int currentNode);
void sortDown(int currentNode);
int N;
int optype;
int heap[251000];
int i = 0;
int main() {
    scanf("%d", &N);
    for (int i = 0; i < N; i++) {
        scanf("%d", &optype);
        if(optype == 0){
            int nNumber;
            scanf("%d", &nNumber);
            addNode(nNumber);
        }
        else if(optype == 1){
            topMinusSecond();
                //deleteNode();
                //addNode();
        }
        else if(optype == 2){
            int idx;
            int Delta;
            scanf("%d %d", &idx, &Delta);
            addDeltaToidx(idx, Delta);
        }
    }
    for(int n = 1; n <= i; n++)
    printf("%d ", heap[n]);
}

void addNode(int nNumber){
    i = i + 1;
    heap[i] = nNumber;
    int currentNode = i;

    while((currentNode >1) && (heap[currentNode] > heap[currentNode/2])){
        int tempuNum = heap[currentNode];
        heap[currentNode] = heap[currentNode/2];
        heap[currentNode/2] = tempuNum;
        currentNode = currentNode/2;
    }
}
void topMinusSecond(){
    int bigNode = 1;
    int newNodeNumber;
    if(i <= 2){
        newNodeNumber = heap[1] - heap[2];
    }
    else if(heap[2] >= heap[3]){
        newNodeNumber = heap[1] - heap[2];
        bigNode = 2;
    }
    else{
        newNodeNumber = heap[1] - heap[3];
        bigNode = 3;
    }
    deleteNode(bigNode);
    deleteNode(1);
    addNode(newNodeNumber);
}
void deleteNode(int deleteThisNode){
    int currentNode = deleteThisNode;
    heap[deleteThisNode] = heap[i];
    heap[i] = 0;
    i--;
    int tempuNumber;
    sortDown(currentNode);
}
void addDeltaToidx(int idx, int Delta){
    heap[idx + 1] = heap[idx + 1] + Delta;

    if(Delta >= 0){
        sortUp(idx + 1);
    }
    else{
        sortDown(idx + 1);
    }
}

void sortUp(int currentNode){
    while((currentNode > 1) && (heap[currentNode] > heap[currentNode/2])){
        int tempuNum = heap[currentNode];
        heap[currentNode] = heap[currentNode/2];
        heap[currentNode/2] = tempuNum;
        currentNode = currentNode/2;
    }
}
void sortDown(int currentNode){
    int tempuNumber;
    int left = currentNode * 2;
    int right = currentNode * 2 + 1;

    // 判斷左右子節點是否存在
    while(currentNode * 2 <= i){
        int left = currentNode * 2;
        int right = currentNode * 2 + 1;
        int largest = currentNode;

        if((left <= i) && (heap[left] > heap[largest])) largest = left;
        if((right <= i )&& (heap[right] > heap[largest])) largest = right;

        if(largest == currentNode) break;

        tempuNumber = heap[currentNode];
        heap[currentNode] = heap[largest];
        heap[largest] = tempuNumber;

        currentNode = largest;
    }
}