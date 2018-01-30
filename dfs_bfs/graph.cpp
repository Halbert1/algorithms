#include <iostream>
#include <stdio.h>
#include <stdlib.h>
using namespace std;

#define maxNum 100

typedef struct 
{
  char v[maxNum]; //ͼ�Ķ�����Ϣ
  int e[maxNum][maxNum]; //�ߵ���Ϣ
  int vNum; //�������
  int eNum; //�ߵĸ���
} graph;

void createGraph(graph *g)//����ͼg  
{  
    cout<<"���ڴ�������ͼ..."<<endl;  
    cout<<"�����붥�����vNum:";  
    cin>>g->vNum;  
    cout<<"������ߵĸ���eNum:";  
    cin>>g->eNum;  
    int i,j;  
  
    //���붥����Ϣ  
    //cout<<"�����붥����Ϣ��"<<endl;  
    //for(i=0;i<g->vNum;i++)  
    //  cin>>g->v[i];  
  
    //��ʼ��ͼg  
    for(i=0;i<g->vNum;i++)  
        for(j=0;j<g->vNum;j++)  
            g->e[i][j]=0;  
  
    //����ߵ����  
    cout<<"������ߵ�ͷ��β"<<endl;  
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

void DFS(graph *g)//�������
{
  int visited[maxNum] ={0}; //����Ѿ������ʹ��Ľڵ�
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
