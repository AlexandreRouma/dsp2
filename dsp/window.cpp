#include "window.h"

namespace dsp {
    Window::~Window() {}

    void Window::generate(float* data, size_t len) const {
        for (size_t i = 0; i < len; i++) {

        }
    }

    template <class T>
    void Window::apply(T* data, size_t len) const {
        // TODO
    }
}