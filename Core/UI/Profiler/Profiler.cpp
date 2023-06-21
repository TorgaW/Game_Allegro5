#include "Profiler.h"

DebugScreenMessage::DebugScreenMessage(std::string msg, ALLEGRO_COLOR clr, float duration)
{
    message = msg;
    color = clr;
    time = duration;
}

Profiler::Profiler(uint32_t id, uint64_t timestamp, std::string name) : Widget(id, timestamp, name)
{
}

void Profiler::Update()
{
    std::reverse(Messages.begin(), Messages.end());
    for (size_t i = 0; i < Messages.size(); i++)
    {
        al_draw_text(StaticFonts::Get().GetUbuntu16R(), Messages[i].color, 5, 16*i+5, 0, Messages[i].message.c_str());
        Messages[i].time -= Render::Get().GetDeltaTime();
    }
    Messages.erase(std::remove_if(Messages.begin(), Messages.end(),
    [](const DebugScreenMessage& msg) { 
        return msg.time <= 0.0f;
    }), Messages.end());
}

void Profiler::PrintDebugMessage(std::string text, ALLEGRO_COLOR text_color, float duration)
{
    DebugScreenMessage dsm(text, text_color, duration);
    Messages.push_back(dsm);
}
