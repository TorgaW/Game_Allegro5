#include "ObjectManager/ObjectManager.hpp"


int main(int argc, char const *argv[])
{
    std::vector<ObjRef<Object>> refs;
    for (size_t i = 0; i < 50000; i++)
    {
        refs.push_back(ObjectManager::CreateObject<Object>("Aboba", "class_Object"));
    }
    for (size_t i = 0; i < refs.size(); i++)
    {
        ObjectManager::DestroyObject(refs[i]);
    }
    refs.clear();
    for (size_t i = 0; i < 50000; i++)
    {
        refs.push_back(ObjectManager::CreateObject<Object>("Aboba", "class_Object"));
    }


    auto s1 = std::chrono::high_resolution_clock::now();
    for (size_t i = 0; i < refs.size(); i++)
    {
        refs[i]->Begin();
    }

    auto s2 = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(s2 - s1);
    std::cout << duration.count() << " microseconds";
    return 0;
}
