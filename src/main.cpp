#include <stdio.h>
#include <exception>

int main() {
    try {
        

        return 0;
    }
    catch (const std::exception& e) {
        fprintf(stderr, "ERROR: %s\n", e.what());
        return -1;
    }
}