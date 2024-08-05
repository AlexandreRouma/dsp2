#pragma once

namespace dsp {
    /**
     * Filter tap container.
    */
    template <class T>
    class Taps {
    public:
        Taps();
        
        /**
         * Create a tap bank holding count taps.
         * @param count Number of taps.
         * @param zero Zero out the taps.
        */
        Taps(int count, bool zero = true);

        /**
         * Create a tap bank from an array.
         * @param taps Array contianing taps.
         * @param count Number of taps to load.
        */
        Taps(T* taps, int count);

        Taps(const Taps<T>& b);
        Taps(Taps<T>&& b);
        ~Taps();

        Taps<T>& operator=(const Taps<T>& b);
        Taps<T>& operator=(Taps<T>&& b);

        /**
         * Get the number of taps in the filter.
        */
        inline int size() const { return count; }

        inline operator const T*() const { return data; }

        inline operator bool() const { return data && count; }

        /**
         * Get a tap by index.
         * @param index Index of the tap
         * @return Tap at index.
        */
        inline const T& operator[](int index) const { return data[index]; }

    protected:
        void reallocate(int count);

        int count = 0;
        T* data = nullptr;
    };
}