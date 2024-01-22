
#include <cstdint>
#include <functional>
#include <iostream>
#include <limits>
#include <map>
#ifndef TIMER_HPP
#define TIMER_HPP
char foo(int c) { return -c; }
float foo(bool c) { return +c; }
uint32_t foo(uint8_t c) { return -c; }
long double foo(int8_t c) { return +c; }

using ID = uint8_t;
static constexpr auto ID_MAX = std::numeric_limits<uint16_t>::max();

struct Manager {
    auto getNewId() -> ID { return id++; };
    uint16_t id{0};
};
using Callback = std::function<void(void)>;
struct TimerManager {
    void startTimer(ID id, Callback callback) { callbacks[id] = callback; }
    void call(ID id) {
        std::cout << "B]CALL with " << +id << "\n";
        if (auto search = callbacks.find(id); search != callbacks.end()) {
            search->second();
        } else {
            std::cerr << "ID =" << +id << " not found\n";
        }
        std::cout << "E]CALL with " << +id << "\n";
    }
    void cancelTimer(uint16_t id) {
        std::cout << "B]cancelTimer with " << +id << "\n";

        if (auto search = callbacks.find(id); search != callbacks.end()) {
            search->second();
            std::cout << "REMOVING ID =" << +id << "\n";

            callbacks.erase(search);
        } else {
            std::cerr << "ID =" << +id << " not found to remove\n";
        }
        std::cout << "E]cancelTimer with " << +id << "\n";
    }
    std::map<ID, Callback> callbacks;
};

constexpr static auto CAP_BITS = 23l;
static const uint32_t sMaxCapacity = 1u < CAP_BITS;
auto get_id_to_cancel()
{
    return 258;
}

void run_examaple() {
    std::cout << +foo('s') << "\n";
    std::cout << sMaxCapacity << "\n";

    Manager mgr{};
    TimerManager timerMgr{};
    for (auto i = 0; i < ID_MAX; i++) {
        const ID id = mgr.getNewId();
        timerMgr.startTimer(
            id, [id]() { std::cout << "CALLING [" << +id << "]\n"; });
    }
    
    const ID id = mgr.getNewId();
    timerMgr.startTimer(id,
                        [id]() { std::cout << "CALLING [" << +id << "]\n"; });
    timerMgr.call(id);

    /**/
    //constexpr ID idToCancel =258;
    timerMgr.cancelTimer(get_id_to_cancel());
    timerMgr.call(get_id_to_cancel());
    
}
#endif