#pragma once

#include <functional>
#include <unordered_map>
#include <atomic>

namespace sfu
{

template<typename... Args>
class Signal {
public:
    using SlotType = std::function<void(Args...)>;
    using SlotId = size_t;

    Signal();

    SlotId connect(SlotType slot);
    void disconnect(SlotId id);
    void emit(Args... args);
    void operator()(Args... args);

private:
    std::unordered_map<SlotId, SlotType> slots;
    std::atomic<SlotId> currentId;
};

} // namespace sfu

#include <Signal.tpp>
