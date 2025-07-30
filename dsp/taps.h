#pragma once

namespace dsp {
    /**
     * Filter tap container.
     * This class is NOT thread-safe.
    */
    template <class T>
    class Taps {
    public:
        // Default constructor
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

        // Copy constructor
        Taps(const Taps<T>& b);

        // Move constructor
        Taps(Taps<T>&& b);

        // Destructor
        virtual ~Taps();

        // Copy assignment operator
        Taps<T>& operator=(const Taps<T>& b);

        // Move assignment operator
        Taps<T>& operator=(Taps<T>&& b);

        /**
         * Get the number of taps in the filter.
        */
        inline int size() const { return count; }

        /**
         * Get a pointer to the tap buffer.
        */
        inline const T* data() const { return buffer; }

        // Cast to bool operator
        inline operator bool() const { return count; }

        /**
         * Get a tap by index.
         * @param index Index of the tap
         * @return Tap at index.
        */
        inline const T& operator[](int index) const { return buffer[index]; }

    protected:
        void reallocate(int count);

        int count = 0;
        T* buffer = nullptr;
    };
}