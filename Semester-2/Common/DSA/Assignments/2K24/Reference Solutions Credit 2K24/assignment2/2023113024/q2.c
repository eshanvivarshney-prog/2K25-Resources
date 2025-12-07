#include<stdio.h>
#include<stdlib.h>
//TODO: USE POST ORDER TRAVERSAL AND BUILD UP BACKWARDS
//* 0 means no phone, 1 means shared phone, 2 means has phone

struct node {
    int hasPhone;
    struct node *left;
    struct node *right;
};

typedef struct node* node;
struct trieNode {
    int bit;
    unsigned long long int count;
    struct trieNode *left;
    struct trieNode *right;
};

typedef struct trieNode* trieNode;

trieNode createTrieNode(){
    trieNode newNode = (trieNode)malloc(sizeof(struct trieNode));
    newNode->bit = 0;
    newNode->count = 0;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

void insertTrie(trieNode head, unsigned long long int num){
    trieNode curr = head;
    for(int i=63; i>=0; i--){
        int bit = (num>>i)&1;
        curr->count++;
        if(bit==0){
            if(curr->left==NULL){
                curr->left = createTrieNode();
            }
            curr = curr->left;
        } else {
            if(curr->right==NULL){
                curr->right = createTrieNode();
            }
            curr = curr->right;
        }
    }
    curr->count++;
}

unsigned long long int findXORs(trieNode head, unsigned long long int n, unsigned long long int l){
    //! finds the number of elements in the trie that gives xor with n greater than l
    trieNode curr = head;
    int ans=0;

    for(int i=63;i>=0;i--){
        int bit = (n>>i)&1;
        int bitL = (l>>i)&1;

        if(bitL==0){
            //? find a bit such that xor with bit gives 0
            if(bit == 0){
                if(curr->right!=NULL){
                    ans += curr->right->count;
                }
                if(curr->left!=NULL){
                    curr = curr->left;
                } else {
                    break;
                }
            }else{
                if(curr->left!=NULL){
                    ans += curr->left->count;
                }
                if(curr->right!=NULL){
                    curr = curr->right;
                } else {
                    break;
                }
            }
        }else{
            //? find a bit such that xor with bit gives 1
            if(bit == 0){
                if(curr->right!=NULL){
                    curr = curr->right;
                } else {
                    break;
                }
            }else{
                if(curr->left!=NULL){
                    curr = curr->left;
                } else {
                    break;
                }
            }
        }
    }
    return ans;
}

unsigned long long int findXORsBetween(trieNode head, unsigned long long int n, unsigned long long int primes[n], unsigned long long int l, unsigned long long int r){
    unsigned long long int ans = 0;
    if(l==0) l = 1;

    for(int i=0;i<n;i++){
        ans += findXORs(head, primes[i], l-1) - findXORs(head, primes[i], r);
    }

    ans/=2;
    ans = (n*(n-1)/2) - ans;
    return ans;
}

node createNode(){ 
    node newNode = (node)malloc(sizeof(struct node));
    newNode->hasPhone = 0;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

void createTree(node root, unsigned long long int n){
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

void countPhones(node head, unsigned long long int *ans){
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
    unsigned long long int n;
    scanf("%lld", &n);
    
    node root = createNode();
    createTree(root, n);

    unsigned long long int ans = 0;
    countPhones(root, &ans);

    if(root->hasPhone==0) ans++;
    printf("%lld\n", ans);

    //! we only need `ans` number of primes
    //! we can use a trie to store the numbers

    trieNode head = createTrieNode();
    //? insert the primes after finding them, into the trie
    //? then we can find the number of XORs that are NOT BETWEEN left and right

    unsigned long long int* primes = (unsigned long long int*)malloc(sizeof(unsigned long long int)*ans);
    primes[0] = 2;
    int index = 1;

    insertTrie(head, 2);
    for(unsigned long long int i=3; index<ans; i+=2){
        int isPrime = 1;
        for(unsigned long long int j=0; primes[j]*primes[j]<=i; j++){
            if(i%primes[j]==0){
                isPrime = 0;
                break;
            }
        }
        if(isPrime){
            insertTrie(head, i);
            primes[index++] = i;
        }
    }

    unsigned long long int l, r;
    scanf("%lld %lld", &l, &r);

    if(ans==0){
        printf("0\n");
        return 0;
    }

    printf("%lld\n", findXORsBetween(head, ans, primes, l, r));

    return 0;
}