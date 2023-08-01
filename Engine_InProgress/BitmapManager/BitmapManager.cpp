#include "BitmapManager.hpp"

ALLEGRO_BITMAP *BitmapManager::LoadBitmap(std::string path_to_bitmap)
{
    auto r = loaded_bitmaps.find(path_to_bitmap);
    if(r != loaded_bitmaps.end())
        return (*r).second;
    else
    {
        ALLEGRO_BITMAP *n = al_load_bitmap(path_to_bitmap.c_str());
        if(n == nullptr)
            return nullptr;
        loaded_bitmaps[path_to_bitmap] = n;
        return n;
    }
}

BitmapManager::~BitmapManager()
{
    for (auto const& x : loaded_bitmaps)
    {
        al_destroy_bitmap(x.second);
    }
}