#include "Memory.hpp"

ObjectMemPool::~ObjectMemPool()
{
    delete begin;
    delete b_array;
}

void ObjectMemPool::Allocate(std::string obj_class, size_t class_size)
{
    auto option = mem_alloc_options.find(obj_class);
    if (option != mem_alloc_options.end())
    {
        begin = static_cast<char *>(malloc((option->second) * class_size));
        end = begin + (option->second) * class_size;
        iterator = begin;
        byte_size = class_size;
        b_array = static_cast<bool *>(malloc(option->second));
        max_objects = option->second;
        std::fill(b_array, b_array + max_objects, true);
    }
    else
    {
        begin = static_cast<char *>(malloc(mem_alloc_default_value * class_size));
        end = begin + mem_alloc_default_value * class_size;
        iterator = begin;
        byte_size = class_size;
        b_array = static_cast<bool *>(malloc(mem_alloc_default_value));
        max_objects = mem_alloc_default_value;
        std::fill(b_array, b_array + max_objects, true);
    }
}

void *ObjectMemPool::AllocateObject()
{
    for (size_t i = last_allocated; i < max_objects; i++)
    {
        if (b_array[i])
        {
            // (Object*)(begin + byte_size * i)->SetMemStorageInfo(i, storage_id);
            b_array[i] = false;
            last_allocated = i + 1;
            allocated++;
            last_allocated_obj = (void *)(begin + byte_size * i);
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
            last_allocated_obj = (void *)(begin + byte_size * i);
            return (void *)(begin + byte_size * i);
        }
    }
    return nullptr;
}

void *MemoryPool::AllocateObject(std::string obj_class, size_t class_size)
{
    auto mem_pool = object_pools.find(obj_class);
    if (mem_pool != object_pools.end())
    {
        for (size_t i = 0; i < mem_pool->second.size(); i++)
        {
            if(!(mem_pool->second[i].IsFull()))
                return (mem_pool->second[i].AllocateObject());
        }
        int s_id = mem_pool->second.size();
        mem_pool->second.emplace_back(s_id);
        mem_pool->second[s_id].Allocate(obj_class, class_size);
        return mem_pool->second[s_id].AllocateObject();
    }
    else
    {
        object_pools.insert({obj_class, {ObjectMemPool(0)}});
        object_pools[obj_class][0].Allocate(obj_class, class_size);
        return (object_pools[obj_class][0].AllocateObject());
    }
}

bool MemoryPool::IsSpaceAvailable(std::string obj_class)
{
    return true;
    // auto mem_pool = object_pools.find(obj_class);
    // if (mem_pool == object_pools.end())
    //     return true;
    // else
    // {
    //     for (size_t i = 0; i < mem_pool->second.size(); i++)
    //     {
    //         if(!mem_pool->second[i].IsFull()) return true;
    //     }
    //     return false;
    // }
}

void MemoryPool::DebugMemory()
{
    int pool_size = 0;
    for (auto const& [key, value] : object_pools)
    {
        pool_size += value[0].max_objects * value[0].byte_size * value.size();
        EngineDebugger::PrintDebugMessage(key + ": " + std::to_string(value[0].max_objects * value[0].byte_size * value.size()) + " bytes; chunks: " + std::to_string(value.size()), al_map_rgb(255, 255, 0), 0.0f, 99999);
    }
    EngineDebugger::PrintDebugMessage("Memory pool: " + std::to_string(pool_size) + " bytes", al_map_rgb(255, 255, 0), 0.0f, 99998);
}
