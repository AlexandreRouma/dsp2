#pragma once
#include <stdint.h>
#include <functional>
namespace dsp {
    /**
     * Window function.
     * This class is NOT thread-safe.
    */
    class Window {
    public:
        // Default constructor
        Window();

        // Copy constructor
        Window(const Window& b);

        // Move constructor
        Window(Window&& b);

        // Virtual destructor
        virtual ~Window();

        // Copy assignement operator
        Window& operator=(const Window& b);

        // Move assignement operator
        Window& operator=(Window&& b);

        /**
         * Compute the value of the window function.
         * @param x Point at which to compute the window at. Must be bounded between 0 and 1.
         * @return Value of the window bounded between 0 and 1.
        */
        inline float operator()(float x) { return def(x); }

        // TODO: Maybe have the windows function override the generate and apply functions for better performance

        /**
         * Generate a window of a given length.
         * @param data Samples buffer to write the window to.
         * @param len Length of the window.
        */
        void generate(float* data, size_t len) const;

        /**
         * Apply the window function to samples.
         * @param data Sample buffer to apply the window to.
         * @param len Length of the sample buffer.
        */
        template <class T>
        void apply(T* data, size_t len) const;

    protected:
        /**
         * Define the window function by setting the `def` member.
         * MUST be overriden by all window functions.
        */
        virtual void define();

        /**
         * The window function itself.
         * This member MUST be initialized by all window functions.
        */
        std::function<float(float)> def;

    private:
        static float undefined(float x);
    };
}