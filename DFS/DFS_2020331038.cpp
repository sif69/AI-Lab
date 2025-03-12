#include<bits/stdc++.h>
using namespace std;

const int N = 1e5;

// graph
vector<int>g[N];
int vis[N];
int level[N];
vector<int>ans;

/*-----------Implementation of DFS by Graph traversal-----------------------*/
void Dfs(int source){
         
     vis[source] = 1;
     ans.push_back(source);
     for(auto child:g[source]){
         
         if(vis[child]) continue;
         cout<<"Parent "<<source<<"'s "<<"Child is "<<child<<'\n';
         Dfs(child);
     }
}


/*   sample Input for testing purpose

     n(number_of_nodes) = 5 , m(number_of_edges) = 4 
     
            5 4 
            1 3 
            1 4 
            3 2 
            3 5 
            
            
            1     level : 0
          /  \ 
         3    4   level : 1
        / \
       2   5      level : 2     
    
    traversal order : 1 3 2 5 4

*/


int main(){

     int n,m,i,j; 
     cin >> n >> m;
     int x,y;
     for(i=0;i<m;i++){

          cin >> x >> y;

          g[x].push_back(y);
          g[y].push_back(x);

     }
     
     Dfs(1);
     
    cout<<"Traversal Order : "<<'\n';
    for(auto it:ans){
        cout<<it<<" ";
    }
    cout<<'\n';
    
    
    
    
    

     
}