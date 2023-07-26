#include "EngineDebugger.hpp"

void EngineDebugger::PrintDebugMessage(std::string msg, ALLEGRO_COLOR clr, float time, int priority)
{
    if(messages_queue.size() > 60) return;
    messages_queue.emplace_back(msg, clr, time, priority);
}

void EngineDebugger::Update(float delta)
{
    if (messages_queue.size() > 0)
    {
        messages_queue.erase(std::remove_if(messages_queue.begin(), messages_queue.end(),
        [](const EngineDebugMessage &dbg_msg)
        {
            return dbg_msg.live_time < 0.0f;
        }),
        messages_queue.end());

        std::sort(messages_queue.begin(), messages_queue.end(), 
        [](const EngineDebugMessage& a, const EngineDebugMessage& b)
        {
            return a.priority > b.priority;
        }
        );

        int message_y = 25;

        for (size_t i = 0; i < messages_queue.size(); i++)
        {
            al_draw_text(debug_font, messages_queue[i].color, 0, message_y, 0, messages_queue[i].message.c_str());
            message_y += 15;
            messages_queue[i].live_time -= delta;
        }
    }
}
