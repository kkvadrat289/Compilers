#include <iostream>
#include "Visitor.h"
#include <assert.h>

void testFunction();

int main(){
    std::cout << "Hello, World" <<std::endl;
    testFunction();
    return 0;
}


void testFunction(){
    CTrue* myTrue = new CTrue();
    assert(myTrue);
}
