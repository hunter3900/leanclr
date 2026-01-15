#pragma once

#include "general_allocation.h"

namespace leanclr::alloc
{
class MetadataAllocation
{
  public:
    static void* malloc(size_t size)
    {
        return GeneralAllocation::malloc(size);
    }

    static void* malloc_zeroed(size_t size)
    {
        return GeneralAllocation::malloc_zeroed(size);
    }

    template <typename T>
    static T* malloc_any()
    {
        void* ptr = malloc(sizeof(T));
        return static_cast<T*>(ptr);
    }

    template <typename T>
    static T* malloc_any_zeroed()
    {
        void* ptr = malloc_zeroed(sizeof(T));
        return static_cast<T*>(ptr);
    }

    static void* calloc(size_t count, size_t size)
    {
        size_t total_size = count * size;
        return malloc_zeroed(total_size);
    }

    template <typename T>
    static T* calloc_any(size_t count)
    {
        void* ptr = calloc(count, sizeof(T));
        return static_cast<T*>(ptr);
    }
};
} // namespace leanclr::alloc
