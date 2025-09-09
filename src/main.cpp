#include <stdio.h>
#include "dsp/window.h"
#include "dsp/window/all.h"

void testFunc(dsp::Window win) {
    printf("win(0.0) = %f\n", win(0.0));
    printf("win(0.5) = %f\n", win(0.5));
    printf("win(1.0) = %f\n", win(1.0));
}

int main() {
    try {
        testFunc(dsp::window::Hann());

        dsp::Window win = dsp::window::Triangular();
        dsp::Window win2 = dsp::window::Hann();

        win = dsp::window::Hann();

        return 0;
    }
    catch (const std::exception& e) {
        fprintf(stderr, "ERROR: %s\n", e.what());
        return -1;
    }
}