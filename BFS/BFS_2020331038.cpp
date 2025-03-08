#include<bits/stdc++.h>
using namespace std;

const int N = 1e5;

// graph
vector<int>g[N];
int vis[N];
int level[N];
/*-----------Implementation of BFS by Graph traversal-----------------------*/
void Bfs(int source){
         
     queue<int>q;
     q.push(source);
     vis[source] = 1;
     int cur_n;
     
     // using Queue to traverse the graph level by level
     cout<<"order of Traversal :"<<'\n';
     while(!q.empty()){
           
          cur_n = q.front();
          // order of traversal 
          
          cout<<cur_n<<" ";
          q.pop();
          for(auto it: g[cur_n]){
               if(!vis[it]){
               q.push(it);
               vis[it] = 1;
               level[it] = level[cur_n] + 1;
               }
          }
         
     } 
     cout<<'\n';
}

/*   sample Input for testing purpose

            5 4 
            1 3 
            1 4 
            3 2 
            3 5 
            
            
            1    level : 0
          /  \
         3    4  level : 1
        / \
       2   5     level : 2     
    

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
     
     Bfs(1);
     
     for(i=1;i<=n;i++){
         cout<<"Node "<<i<<" in level "<<level[i]<<'\n';
     }

     


     
}