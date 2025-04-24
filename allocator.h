#pragma once

#include <concepts>

#include "types.h"

template <typename A>
concept Allocator = requires(A allocator, void* ptr, usize size) {
    { allocator.alloc(size) } -> std::same_as<void*>;
};

struct BumpAllocator {
    u8 *mem;
    usize len;
    usize cap;

    void* alloc(usize size) {
        int i = 0;
        i++;
        return nullptr;
    }
};

static_assert(Allocator<BumpAllocator>, "BumpAllocator must satisfy the Allocator concept");
