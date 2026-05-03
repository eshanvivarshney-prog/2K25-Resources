#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <stdbool.h>
#define ll long long int

/*
* n : number of stations
* k : initial oxygen amt
* d : required depth to travel
* p : oxygen amt per station
* ti : time to fill air at station i at depth yi (1 <= i <= n)
* Basically en route to depth d, he can fill air at station which fills p oxygen.
* each station takes ti time to fill air
* 1 oxygen depleted per unit depth
* we need to find total time taken to reach depth d
*/

typedef struct Station {
    int depth;
    ll time;
} station;

typedef struct BinaryHeap {
    station* arr;
    int capacity;
    int size;
} binaryheap;

binaryheap* createBinaryHeap(int capacity) {
    binaryheap* bh = (binaryheap*)malloc(sizeof(struct BinaryHeap));
    bh->arr = (station*)malloc(capacity * sizeof(station));
    bh->capacity = capacity;
    bh->size = 0;
    return bh;
}

void swap(station* a, station* b) {
    station temp = *a;
    *a = *b;
    *b = temp;
}

void heapify(binaryheap* bh, int i) {
    int smallest = i;
    int left = 2*i+1;
    int right = 2*i+2;

    if(left < bh->size && bh->arr[left].time < bh->arr[smallest].time) smallest = left;
    if(right < bh->size && bh->arr[right].time < bh->arr[smallest].time) smallest = right;

    if(smallest != i) {
        swap(&bh->arr[i], &bh->arr[smallest]);
        heapify(bh, smallest);
    }
}

void insert(binaryheap* bh, station data) {
    if(bh->size == bh->capacity) return;
    bh->arr[bh->size] = data;
    int i = bh->size;
    bh->size++;

    while(i>0 && bh->arr[(i-1)/2].time > bh->arr[i].time) {
        swap(&bh->arr[i], &bh->arr[(i-1)/2]);
        i = (i-1)/2;
    }
}

station extractMin(binaryheap* bh) {
    if(bh->size == 0) {
        station temp;
        temp.time = -1;
        return temp;    
    }
    if(bh->size == 1) {
        bh->size--;
        return bh->arr[0];
    }

    station root = bh->arr[0];
    bh->arr[0] = bh->arr[bh->size-1];
    bh->size--;
    heapify(bh, 0);
    return root;
}

void printHeap(binaryheap* bh) {
    for(int i=0;i<bh->size;i++) {
        printf("%d %lld - ", bh->arr[i].depth, bh->arr[i].time);
    }
    printf("\n");
}

int compare(const void* a, const void* b) {
    return ((station*)a)->depth - ((station*)b)->depth;
}

int main() {
    int n, k, d, p;
    scanf("%d %d %d %d", &n, &k, &d, &p);

    station nodes[n];
    for(int i=0;i<n;i++) scanf("%d", &nodes[i].depth);
    for(int i=0;i<n;i++) scanf("%lld", &nodes[i].time);
    qsort(nodes, n, sizeof(station), compare);

    ll time = 0;
    binaryheap* bh = NULL;
    bh = createBinaryHeap(n);

    int ptr = 0;    
    while(k<d){
        if(nodes[ptr].depth <= k && ptr<n){
            insert(bh, nodes[ptr]);
            ptr++;
        }else{
            if(bh->size == 0){
                break;
            }
            station temp = extractMin(bh);
            k+=p;
            time+=temp.time;
        }  
        //printf("k: %d, time: %lld\n", k, time);
        //printHeap(bh);
    }

    if(k>=d) printf("%lld\n", time);
    else printf("-1 %d\n",k);

    return 0;
}