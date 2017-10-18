#include <stdio.h>
#include <stdlib.h>
#include <stack> 

typedef struct node 
{
  int data;
  struct node * next;
}Node, *LinkList;

Node * createList(const int a[], int n) 
{
  Node *head, *endPtr;
  head = endPtr = NULL;
  for(int i=n-1; i>=0; i--) {
    Node *temp = new Node;
    temp->data = a[i];
    temp->next = NULL;
    if(i==n-1) {
      head = endPtr = temp;
    } else {
      endPtr->next = temp;
      endPtr = temp;
    }
  }
  return head;
}

int _add(Node *sumNode, const int a, const int b, const int carry)
{
  sumNode->data = (a+b+carry)%10;
  if(a+b+carry >= 10) {
    return 1;
  }
  return 0;
}

Node * add(const LinkList a, const LinkList b) 
{
  if(a == NULL) {
    return b;
  }
  if(b == NULL) {
    return a;
  }
  Node *sum = new Node;
  sum->next = NULL;
  int carry = _add(sum, a->data, b->data, 0);
  Node* tempA = a->next;
  Node* tempB = b->next;
  Node *pSum = sum;
  while(tempA != NULL || tempB!=NULL) {
    if(tempA == NULL) {
      Node *pNode = new Node;
      pNode->next = NULL;
      carry = _add(pNode, 0, tempB->data, carry);
      pSum->next = pNode;
      pSum = pNode;
      tempB = tempB->next;
    } else if(tempB == NULL){
      Node *pNode = new Node;
      pNode->next = NULL;
      carry = _add(pNode, 0, tempA->data, carry);
      pSum->next = pNode;
      pSum = pNode;
      tempA = tempA->next;
    } else {
      Node *pNode = new Node;
      pNode->next = NULL;
      carry = _add(pNode, tempA->data, tempB->data, carry);
      pSum->next = pNode;
      pSum = pNode;
      tempA = tempA->next;
      tempB = tempB->next;
    }
  }
  if(carry >= 1) {
      Node *pNode = new Node;
      pNode->next = NULL;
      carry = _add(pNode, 0, 0, carry);
      pSum->next = pNode;
      pSum = pNode;
  }
  return sum;
}

void printListReversing(LinkList pHead)
{
  std::stack<Node*> nodes; 
  Node *temp = pHead;
  while(temp != NULL) {
    nodes.push(temp);
    temp = temp->next;
  }
  while(!nodes.empty())   //出栈  
  {  
    temp = nodes.top();   //删除栈顶元素  
    nodes.pop();   //删除栈顶元素  
    printf("%d", temp->data);
    if(!nodes.empty()) {
      printf("<-");
    }
  }  
  printf("\n");
}

int len(const int array[]){
  printf("%lu/%lu\n", sizeof(array), sizeof(array[0]));
  return sizeof(array) / sizeof(array[0]);
}

int main() 
{
  int a[] =    {9, 9, 3, 4, 3};
  int b[] =    {9, 2, 7, 4, 3};
  LinkList listA =  createList(a, 5);
  LinkList listB =  createList(b, 5);
  printListReversing(listA); 
  printListReversing(listB); 
  LinkList listS = add(listA, listB);
  printListReversing(listS); 
  return 0;
}
