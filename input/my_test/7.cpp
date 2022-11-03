#include <iostream>

int main () {
    for (size_t i = 10; i >= 0; i--) {
        if(i % (503 * 503 * 503) == 0) std::cout << i;
    }
}
