#include "window.h"
#include "complex.h"
#include <stdexcept>

namespace dsp {
    Window::Window() {
        // Define the window with the default error
        define();
    }

    Window::Window(const Window& b) {
        // Copy the definition
        def = b.def;
    }

    Window::Window(Window&& b) {
        // Move the definition
        def = std::move(b.def);
    }

    Window::~Window() {}

    Window& Window::operator=(const Window& b) {
        // Copy the definition
        def = b.def;

        // Return self
        return *this;
    }

    Window& Window::operator=(Window&& b) {
        // Move the definition
        def = std::move(b.def);

        // Return self
        return *this;
    }

    void Window::generate(float* data, size_t len) const {
        // Compute the linear map ratio
        float ratio = 1.0f / ((float)(len + 1));

        // Iterate over all taps
        for (size_t i = 0; i < len; i++) {
            // Evaluate the window at the adimensional parameter
            data[i] = def(((float)(i + 1)) * ratio);
        }
    }

    template <class T>
    void Window::apply(T* data, size_t len) const {
        // Compute the linear map ratio
        float ratio = 1.0f / ((float)(len + 1));

        // Iterate over all taps
        for (size_t i = 0; i < len; i++) {
            // Evaluate the window at the adimensional parameter
            data[i] *= def(((float)(i + 1)) * ratio);
        }
    }
    template void Window::apply(float* data, size_t len) const;
    template void Window::apply(Complex* data, size_t len) const;

    void Window::define() {
        // Ensure an error is thrown if the undefined window is used
        def = Window::undefined;
    }

    float Window::undefined(float x) {
        // Called when a window function was not defined
        throw std::runtime_error("Undefined window");
        return 0;
    }
}