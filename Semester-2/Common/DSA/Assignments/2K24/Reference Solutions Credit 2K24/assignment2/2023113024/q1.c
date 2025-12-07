#include<stdio.h>
#include<stdlib.h>

//TODO: USE POST ORDER TRAVERSAL AND BUILD UP BACKWARDS
//* 0 means no phone, 1 means shared phone, 2 means has phone
\
struct node {
    int hasPhone;
    struct node *left;
    struct node *right;
};

typedef struct node* node;

node createNode(){ 
    node newNode = (node)malloc(sizeof(struct node));
    newNode->hasPhone = 0;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

void createTree(node root, int n){
    //! NOTE: 1 is node exists, 0 is not exists
    //! LEVEL ORDER TRAVERSAL
    node queue[300001];

    int front = 0, rear = 0;
    queue[rear++] = root;

    int left, right;
    int rootExists;
    scanf("%d", &rootExists);
    n--;

    while(n){
        node curr = queue[front++];
        scanf("%d", &left);
        n--;

        if(left == 1){
            curr->left = createNode();
            queue[rear++] = curr->left;
        }
        if(n!=0){
            scanf("%d", &right);
            n--;

            if(right == 1){
                curr->right = createNode();
                queue[rear++] = curr->right;
            }
        }
    }
}

void countPhones(node head, int *ans){
    if(head == NULL) return;
    countPhones(head->left, ans);
    countPhones(head->right, ans);

    if(head->left==NULL && head->right==NULL){
        return;
    }

    if((head->left!=NULL && head->left->hasPhone==0) || ( head->right!=NULL && head->right->hasPhone==0)){
        head->hasPhone = 2;
        *ans += 1;
    } else if((head->left!=NULL && head->left->hasPhone==2) || ( head->right!=NULL && head->right->hasPhone==2)){
        head->hasPhone = 1;
    }
}

int main() {
    int n;
    scanf("%d", &n);
    
    node root = createNode();
    createTree(root, n);

    int ans = 0;
    countPhones(root, &ans);

    if(root->hasPhone==0) ans++;
    printf("%d\n", ans);

    return 0;
}