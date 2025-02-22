#include <iostream>
#include "SoutienFlow.h"

int main() {
    using namespace SoutienFlow;

    auto a = []() { std::cout << "a() executed\n"; };
    auto b = []() { std::cout << "b() executed\n"; };
    auto c = []() { std::cout << "c() executed\n"; };
    auto d = []() { std::cout << "d() executed\n"; };

    auto task_a = createGuardedFunction(a, "a");
    task_a();
    
    auto task_b = createGuardedFunction(b, "b");
    
    auto task_c = GUARDED_FUNCTION(c, task_a, task_b);
    task_c();
    
    auto task_d = GUARDED_FUNCTION(d, task_c);
    task_d();
}
