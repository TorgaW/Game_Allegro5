#include "GarbageCollector.hpp"

void GarbageCollector::RegisterKillCandidate(ObjRef<Object> candidate)
{   
    // auto result = std::find_if(gc_objects_storage.begin(), gc_objects_storage.end(), 
    // [candidate](ObjRef<Object> item){
    //     return candidate == item;
    // });

    // if(result != gc_objects_storage.end())
    // {
    //     gc_kill_candidates.push_back(*result);
    //     candidate.Disable();
    // }

    gc_kill_candidates.push_back(candidate);

}

void GarbageCollector::CheckGarbage()
{

    for (size_t i = 0; i < gc_kill_candidates.size(); i++)
    {
        int t = gc_kill_candidates[i]->GetObjStorageIndex();
        // std::cout << "Index: " << t << "\n";
        gc_objects_storage_t[t].Free();
        gc_objects_storage_t.Remove(t);
    }
    gc_kill_candidates.clear();
    

    // if(gc_kill_candidates.size() > GC_CLEAN_THRESHOLD)
    // {
    //     if(gc_kill_candidates.size() < GC_MAX_CLEAN_OBJECTS_THRESHOLD)
    //     {
            // gc_objects_storage.erase(
            //     std::remove_if(gc_objects_storage.begin(), gc_objects_storage.end(),
            //     [](ObjRef<Object> item){
            //         if(std::find(gc_kill_candidates.begin(), gc_kill_candidates.end(), item) != gc_kill_candidates.end())
            //         {
            //             item.Free();
            //             return true;
            //         }
            //         return false;
            //     }),
            //     gc_objects_storage.end()
            // );
            // gc_kill_candidates.clear();
        // }
        // else
        // {
            // uint16_t counter = 0;
            // std::vector<ObjRef<Object>> temp;
            // for (size_t i = 0; i < gc_objects_storage.size(); i++)
            // {
            //     if(counter >= GC_MAX_CLEAN_OBJECTS_THRESHOLD) break;
            //     auto l = std::find(gc_kill_candidates.begin(), gc_kill_candidates.end(), gc_objects_storage[i]);
            //     if(l != gc_kill_candidates.end())
            //     {
            //         temp.push_back(*l);
            //         gc_kill_candidates.erase(l);
            //         counter++;
            //     }
            // }

            // gc_objects_storage.erase(std::remove_if(gc_objects_storage.begin(), gc_objects_storage.end(),
            // [temp](ObjRef<Object> item){
            //     if(std::find(temp.begin(), temp.end(), item) != temp.end())
            //     {
            //         item.Free();
            //         return true;
            //     }
            //     return false;
            // }), gc_objects_storage.end());

            // temp.clear();
            
            // gc_objects_storage.erase(
            //     std::remove_if(gc_objects_storage.begin(), gc_objects_storage.end(),
            //     [counter](ObjRef<Object> item) mutable {
            //         std::cout << counter << "\n";
            //         if(counter >= GC_MAX_CLEAN_OBJECTS_THRESHOLD) return false;
            //         auto p = std::find(gc_kill_candidates.begin(), gc_kill_candidates.end(), item);
            //         if(p != gc_kill_candidates.end())
            //         {
            //             item.Free();
            //             gc_kill_candidates.erase(p);
            //             counter++;
            //             return true;
            //         }
            //         return false;
            //     }),
            //     gc_objects_storage.end()
            // );
        // }
    // }

}