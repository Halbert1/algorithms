shoppe面试题

#include <iostream>

class TestA;
class TestB;

class TestA {
public: 
    int value;
    TestB *bObj;
        
    TestA(int _value, TestB *_bObj): value(_value), bObj(_bObj) {
    }
};

class TestB {
public:
    int value;
    TestA *aObj;
        
    TestB(int _value, TestA *_aObj): value(_value), aObj(_aObj) {
    }
};

// Implement two functions, DeepCopyTestA and PrintTestA
// DeepCopyTestA is to deep copy class TestA and return a new object, 
// if TestA's property bObj is not null, you need to deepcopy bObj, and so on
    
TestA* DeepCopyTestA(TestA *obj) {
    return NULL;
};
    
void PrintTestA(TestA *obj) {
}

int main(void)
{
     std::cout<<"begin" <<std::endl;
      // Case 1
     TestA *a5 = new TestA(5, NULL);
     TestB *b4 = new TestB(4, a5);
     TestA *a3 = new TestA(3, b4);
        
     TestA *new_a3 = DeepCopyTestA(a3);
     PrintTestA(new_a3);
        
     // Case 2
    TestB *b2 = new TestB(2, a3);
    TestA *a1 = new TestA(1, b2);
        
    a5->bObj = b2;
    TestA *new_a1 = DeepCopyTestA(a1);
    PrintTestA(new_a1);
    return 0;
}

