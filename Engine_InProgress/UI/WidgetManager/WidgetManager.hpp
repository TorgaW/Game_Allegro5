#ifndef E8843C69_007B_4A75_86BF_57C2B35FF3CC
#define E8843C69_007B_4A75_86BF_57C2B35FF3CC

#include "../Widget/Widget.hpp"
#include "../../ObjectManager/ObjectManager.hpp"
#include "../../Render/Render.hpp"
#include "../Fonts/Fonts.hpp"

#include <type_traits>

class WidgetManager
{
public:
    static inline std::vector<Ref<Widget>> widgets_storage;
    static inline std::map<std::string, Ref<Widget>> widgets_class_storage;

public:
    WidgetManager(){};
    ~WidgetManager(){};

    static inline std::vector<Ref<Widget>> *GetWidgetsStorage() { return &widgets_storage; };

    static inline void UpdateWidgets()
    {
        for (size_t i = 0; i < widgets_storage.size(); i++)
        {
            widgets_storage[i]->PropagateUpdate(Render::GetDeltaTime());
        }
        Render::DrawUI(widgets_storage);
    };

    template<class T>
    static Ref<T> CreateWidget(std::string name, std::string widget_class)
    {
        static_assert(std::is_base_of<Widget, T>::value, "Widget manager creation error: must be Widget at least.");
        return ObjectManager::CreateObject<T>(name, widget_class);
    }

    template<class T>
    static Ref<T> CopyWidget(Ref<T> candidate, std::string name)
    {
        static_assert(std::is_base_of<Widget, T>::value, "Widget manager copy error: must be Widget at least.");
        return ObjectManager::CopyObject<T>(candidate, name);
    }

    template<class T>
    static void AddToViewport(Ref<T> widget)
    {
        widget->CallBegin();
        widgets_storage.push_back(widget);
    }

    template<class T>
    static void RemoveFromViewport(Ref<T> widget)
    {
        widgets_storage.erase(std::remove_if(widgets_storage.begin(), widgets_storage.end(),
        [widget](Ref<T> t_widget)
        {
            return widget == t_widget;
        }),
        widgets_storage.end());
    }

    template<class T>
    static Ref<T> FindWidgetInViewport(std::string name, std::string widget_class)
    {
        auto r = std::find_if(widgets_storage.begin(), widgets_storage.end(), 
        [name, widget_class](Ref<T> t_widget)
        {
            return t_widget->GetName() == name && t_widget->GetClass() == widget_class;
        });
        if(r != widgets_storage.end())
            return (*r);
        else
            return Ref<T>();
    }   
};


#endif /* E8843C69_007B_4A75_86BF_57C2B35FF3CC */
