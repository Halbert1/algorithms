#include <stdio.h>
#include <stdlib.h>


void print(int *p, int length){
  for(int i = 0; i<length; i++) {
    printf("%d ", p[i]);
  }
  printf("\n");
}

void swap(int &a, int &b) {
  int c = b;
  b = a;
  a = c;
}

void bubbleSort(int *p, int length) {
  for(int i=0; i<length; i++) {
    for(int j=0; j<length-i-1; j++) {
      if(p[j] >= p[j+1]) {
        swap(p[j], p[j+1]);
      }
    }
  }
}

int main(int argc, char *args[])
{
  int buf[] = {12, 4, 35, 6, 8};
  int m = sizeof(buf)/sizeof(int);
  printf("m=%d\n", m);
  printf("before:\n");
  print(buf, m);
  bubbleSort(buf, m);
  printf("after:\n");
  print(buf, m);
  return 0;
}
