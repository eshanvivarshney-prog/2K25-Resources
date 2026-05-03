#include<iostream>
#include<map>
#include<vector>
#include<queue>
using namespace std;

int main(){
    int n, m;
    cin >> n >> m;

    map<int, vector<int>> adj;
    for(int i=0; i<m; i++){
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    vector<int> visited(n+1, 0);
    int pathsToAdd = 0; //! number of paths to connect different components of graph, will be components - 1, connect any node of 1 component to any node of other component
    vector<pair<int, int>> components; //! stores the start and end of each component

    for(int i=1; i<=n; i++){
        if(visited[i] == 0){
            queue<int> q;
            q.push(i);
            visited[i] = 1;
            int start = i, end = i;
            while(!q.empty()){
                int node = q.front();
                q.pop();
                for(int neighbour: adj[node]){
                    if(visited[neighbour] == 0){
                        visited[neighbour] = 1;
                        q.push(neighbour);
                        end = neighbour;
                    }
                }
            }
            components.push_back({start, end});
        }
    }

    pathsToAdd = components.size() - 1;
    cout << pathsToAdd << '\n';

    for(int i=0; i<pathsToAdd; i++){
        cout << components[i].first << " " << components[i+1].first << '\n';
    }

    cout << endl;
}