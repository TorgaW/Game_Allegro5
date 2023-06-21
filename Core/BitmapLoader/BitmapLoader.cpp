#include "BitmapLoader.h"

ALLEGRO_BITMAP *BitmapLoader::LoadBitmap(std::string path)
{
    auto r = LoadedBitmaps.find(path);
    if(r != LoadedBitmaps.end())
        return (*r).second;
    else
    {
        ALLEGRO_BITMAP *n = al_load_bitmap(path.c_str());
        if(n == nullptr)
            return nullptr;
        LoadedBitmaps.insert({path, n});
        return n;
    }
}

BitmapLoader::~BitmapLoader()
{
    for (auto it = LoadedBitmaps.begin(); it != LoadedBitmaps.end(); it++)
    {
        al_destroy_bitmap((*it).second);
    }
    LoadedBitmaps.clear();
}
