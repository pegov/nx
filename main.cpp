#include <iostream>

#include "array.h"
#include "allocator.h"

int main() {
    int value = 10;
    auto v = Foo<int>{.value = &value};

    auto a = Array<int>::create();
    a.append(1);
    a.append(2);

    auto av = a.view();

    for (auto v : av) {
        std::cout << v << std::endl;
    }

    auto ba = BumpAllocator{
        .mem = nullptr,
        .len = 0,
        .cap = 0,
    };

    return 0;
}
