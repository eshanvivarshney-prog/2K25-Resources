#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define QLIM 100000000000001

typedef struct{
    int src;
    int dest;
    ll cost;
    bool isSpecial;
} connection;

struct CompareCost {
    bool operator()(const connection& c1, const connection& c2) {
        if(c1.cost==c2.cost) return c1.isSpecial > c2.isSpecial;
        return c1.cost > c2.cost;
    }
};

int main(){
    int n, m, k;
    cin >> n >> m >> k;

    vector<vector<pair<ll,ll>>> normal(n+1);
    vector<ll> special(n+1,INT_MAX);

    for(int i=0; i<m; i++){
        ll a, b, c;
        cin >> a >> b >> c;
        normal[a].push_back({b,c});
        normal[b].push_back({a,c});
    }

    for(int i=0; i<k; i++){
        ll a, b;
        cin >> a >> b;
        special[a] = min(special[a], b);
    }

    vector<ll> dist(n+1, QLIM);
    int count = 0;
    priority_queue<connection, vector<connection>, CompareCost> pq;
    pq.push({1,1,0,false});

    for(int i=2; i<=n; i++){
        if(special[i]!=INT_MAX){
            connection c = {1,i,special[i],true};
            pq.push(c);
        }
    }

    while(!pq.empty()){
        connection c = pq.top();
        pq.pop();

        if(dist[c.dest] > c.cost){
            dist[c.dest] = c.cost;
            if(c.isSpecial) count++;
            for(auto &i:normal[c.dest]){
                if(dist[i.first] > c.cost + i.second){
                    connection temp = {c.dest, i.first, c.cost + i.second, false};
                    pq.push(temp);
                }
            }
        }
    }

    cout << k-count << endl;
}