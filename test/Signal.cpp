#include <iostream>
#include <Signal.hpp>

int main() {
    sfu::Signal<int> sig;

    auto id1 = sig.connect([](int i) {
        std::cout << i << " [槽1] 触发！\n";
    });

    auto id2 = sig.connect([](int i) {
        std::cout << i << " [槽2] 触发！\n";
    });

    sig(1); // 第一次触发

    sig.disconnect(id1);

    sig(2); // 第二次触发（只触发槽2）

    return 0;
}
