#include "Memory.hpp"

void ObjectMemPool::Allocate(std::string obj_class, size_t class_size)
{
    auto option = mem_alloc_options.find(obj_class);
    if (option != mem_alloc_options.end())
    {
        begin = static_cast<char *>(malloc((option->second) * class_size));
        end = begin + (option->second) * class_size;
        iterator = begin;
        byte_size = class_size;
        b_array = static_cast<bool*>(malloc(option->second));
        max_objects = option->second;
        std::fill(b_array, b_array+max_objects, true);
    }
    else
    {
        begin = static_cast<char *>(malloc(mem_alloc_default_value * class_size));
        end = begin + mem_alloc_default_value * class_size;
        iterator = begin;
        byte_size = class_size;
        b_array = static_cast<bool*>(malloc(mem_alloc_default_value));
        max_objects = mem_alloc_default_value;
        std::fill(b_array, b_array+max_objects, true);
    }
}

void *ObjectMemPool::AllocateObject()
{
    for (size_t i = last_allocated; i < max_objects; i++)
    {
        if (b_array[i])
        {
            b_array[i] = false;
            last_allocated = i+1;
            allocated++;
            return (void *)(begin + byte_size * i);
        }
    }
    for (size_t i = 0; i < last_allocated; i++)
    {
        if (b_array[i])
        {
            b_array[i] = false;
            last_allocated = i;
            allocated++;
            return (void *)(begin + byte_size * i);
        }
    }
    return nullptr;
}

bool MemoryPool::IsSpaceAvailable(std::string obj_class)
{
    auto mem_pool = object_pools.find(obj_class);
    if(mem_pool == object_pools.end()) return true;
    return !(mem_pool->second.IsFull());
}
