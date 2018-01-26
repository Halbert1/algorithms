#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <ext/hash_map>
#include <string>
using namespace std;
using namespace __gnu_cxx;

class TestA;
class TestB;

class TestA {
  public: 
    int value;
    TestB *bObj;

    TestA(int _value, TestB *_bObj): value(_value), bObj(_bObj) {
    }
    TestA(const TestA & obj) {
      value = obj.value;
      if(obj.bObj == NULL) {
        bObj = NULL;
      } else {
        bObj = new TestB(*(obj.bObj));
      }
    }
  private:
    // 赋值操作符待处理
    TestA& operator = (const TestA& other) {
    } 
};

class TestB {
  public:
    int value;
    TestA *aObj;

    TestB(int _value, TestA *_aObj): value(_value), aObj(_aObj) {
    }
    TestB(const TestB & obj) {
      value = obj.value;
      //aObj = new TestA(*(obj.aObj));
    }
  private:
    //赋值操作符待处理
     TestB& operator = (const TestB& other) {
     } 
};

// Implement two functions, DeepCopyTestA and PrintTestA
// DeepCopyTestA is to deep copy class TestA and return a new object, 
// if TestA's property bObj is not null, you need to deepcopy bObj, and so on
TestA* _DeepCopyTestA(TestA *obj, hash_map<long, long>&hash);

void printHash(hash_map<long, long>&hash) {
    hash_map<long, long>::iterator it = hash.begin();
    printf("printHash\n");
    while(it != hash.end()) {
      printf("%p->%p\n", (long *)it->first, (long*)it->second);
      it++;
    }
    printf("printHash end\n");
}

//递归方式实现深拷贝
TestB* _DeepCopyTestB(TestB *obj, hash_map<long, long>&hash) {
  TestB *pB = new TestB(obj->value, NULL);
  hash.insert(pair<long,long>((long)obj, (long)pB));
  if(obj->aObj != NULL) {
    TestA *pA = NULL;
    hash_map<long, long>::iterator it = hash.find((long)obj->aObj);
    if(it != hash.end()) { //found
      pA = (TestA *)hash[(long)obj->aObj];
    } else {
      pA = _DeepCopyTestA(obj->aObj, hash);
    }
    pB->aObj = pA;
  }
  return pB;
}

TestA* _DeepCopyTestA(TestA *obj, hash_map<long, long>&hash) {
  TestA *pA = new TestA(obj->value, NULL);
  hash.insert(pair<long,long>((long)obj, (long)pA));
  if(obj->bObj != NULL) {
    TestB *pB = NULL;
    hash_map<long, long>::iterator it = hash.find((long)obj->bObj);
    if(it != hash.end()) { //found
      pB = (TestB *)hash[(long)obj->bObj];
    } else {
      pB = _DeepCopyTestB(obj->bObj, hash);
    }
    pA->bObj = pB;
  }
  return pA;
}

TestA* DeepCopyTestA(TestA *obj) {
  hash_map<long, long> hash;
  TestA *pA = _DeepCopyTestA(obj, hash);
  printHash(hash);
  return pA;
};

void PrintTestA(TestA *obj) {
  TestA *pA = obj;
  TestB *pB = obj->bObj;
  int i = 0;
  hash_map<long, long> hash;
  while(pA != NULL || pB != NULL) {
    if(i%2 == 0) {
      if(pA == NULL) break;
      hash_map<long, long>::iterator it = hash.find((long)pA);
      if(it != hash.end()) { //found
        break;
      }
      printf("testA->value:%d\ntestA->bObj:%p\n", pA->value, pA->bObj);
      hash.insert(pair<long,long>((long)pA, 0));
      pB = pA->bObj;
    } else {
      if(pB==NULL) break;
      hash_map<long, long>::iterator it = hash.find((long)pB);
      if(it != hash.end()) { //found
        break;
      }
      printf("testB->value:%d\nteatB->aObj:%p\n", pB->value, pB->aObj);
      hash.insert(pair<long,long>((long)pB, 0));
      pA = pB->aObj;
    }
    i++;
  }
  printf("---------\n");
}

int main(void)
{
  std::cout<<"begin" <<std::endl;
  // Case 1
  TestA *a5 = new TestA(5, NULL);
  TestB *b4 = new TestB(4, a5);
  TestA *a3 = new TestA(3, b4);

  TestA *new_a3 = DeepCopyTestA(a3);
  PrintTestA(a3);
  PrintTestA(new_a3);


  // Case 2
  TestB *b2 = new TestB(2, a3);
  TestA *a1 = new TestA(1, b2);

  //a5->bObj = b2;
  a5->bObj = b4;
  TestA *new_a1 = DeepCopyTestA(a1);
  PrintTestA(a1);
  PrintTestA(new_a1);
  return 0;
}
