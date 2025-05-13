#pragma once

#include <Signal.hpp>

namespace sfu
{

template<typename... Args>
Signal<Args...>::Signal() : currentId(0) {}

template<typename... Args>
typename Signal<Args...>::SlotId Signal<Args...>::connect(SlotType slot) {
    SlotId id = ++ currentId;
    slots[id] = slot;
    return id;
}

template<typename... Args>
void Signal<Args...>::disconnect(SlotId id) {
    slots.erase(id);
}

template<typename... Args>
void Signal<Args...>::emit(Args... args) {
    for (const auto& pair : slots) {
        pair.second(args...);
    }
}

template<typename... Args>
void Signal<Args...>::operator()(Args... args) {
    emit(args...);
}

} // namespace sfu
