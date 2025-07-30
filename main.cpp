#include <stdio.h>
// #include "dsp/stream.h"
// #include "dsp/complex.h"
#include "dsp/window.h"
#include "dsp/window/rectangular.h"

// void sendWorker(dsp::Stream<float>& stream) {
//     while (true) {
//         // Obtrain a stereo buffer set
//         auto set = stream.reserve(240, 2);

//         // Fill the buffer
//         for (int i = 0; i < set.capacity; i++) {
//             set.buffer[0][i] = rand();
//             set.buffer[1][i] = rand();
//         }

//         // Send the buffer
//         if (!stream.send(set.capacity)) { break; }
//     }
// }

// void recvWorker(dsp::Stream<float>& stream) {
//     while (true) {
//         // Receive a buffer set
//         auto set = stream.recv();
//         if (!set.samples) { break; }

//         // Process
//         // TODO: Do something

//         // Flush the buffer set
//         stream.flush();
//     }
// }

void test(const dsp::Window& win) {
    float test[7];
    win.generate(test, 7);
    for (int i = 0; i < 7; i++) {
        printf("window[%d] = %f\n", i, test[i]);
    }
}

int main() {
    test(dsp::window::Rectangular());
    return 0;
}