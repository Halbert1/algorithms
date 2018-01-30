#include <iostream>
#include <stdio.h>
#include <stdlib.h>
using namespace std;

#define maxNum 100

typedef struct 
{
  char v[maxNum]; //图的顶点信息
  int e[maxNum][maxNum]; //边的信息
  int vNum; //顶点个数
  int eNum; //边的个数
} graph;

void createGraph(graph *g)//创建图g  
{  
    cout<<"正在创建无向图..."<<endl;  
    cout<<"请输入顶点个数vNum:";  
    cin>>g->vNum;  
    cout<<"请输入边的个数eNum:";  
    cin>>g->eNum;  
    int i,j;  
  
    //输入顶点信息  
    //cout<<"请输入顶点信息："<<endl;  
    //for(i=0;i<g->vNum;i++)  
    //  cin>>g->v[i];  
  
    //初始画图g  
    for(i=0;i<g->vNum;i++)  
        for(j=0;j<g->vNum;j++)  
            g->e[i][j]=0;  
  
    //输入边的情况  
    cout<<"请输入边的头和尾"<<endl;  
    for(int k=0;k<g->eNum;k++)  
    {  
        cin>>i>>j;  
        g->e[i][j]=1;  
        g->e[j][i]=1;  
    }  
}

void dfs(graph *g, int i, int * visited){
  printf("%d\n", i);
  visited[i]=1;
  for(int j=0; j<g->vNum; j++) {
    if(g->e[i][j] !=0 && visited[j]==0) {
      dfs(g,j, visited);
    }
  }
}

void DFS(graph *g)//深度优先
{
  int visited[maxNum] ={0}; //标记已经被访问过的节点
  for(int i=0; i<g->vNum; i++) {
    if(visited[i] == 0) {
      dfs(g, i, visited);
    }
  }
}

void BFS(graph *g)
{
}


int main(int argc, char *argv[])
{
  graph *g = new graph();
  createGraph(g);
  DFS(g);
  return 0;
}
