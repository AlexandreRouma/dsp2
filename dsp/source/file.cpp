#include "file.h"
#include "../complex.h"
#include <stdint.h>

// TODO: Thread safety

namespace dsp::source {
    template <class T>    
    File<T>::File() {}

    template <class T>
    File<T>::File(const std::string& path, bool repeat) {
        // Open the file
        open(path, repeat);
    }

    template <class T>
    File<T>::~File() {
        // Close the file if its open
        close();
    }

    template <class T>
    void File<T>::open(const std::string& path, bool repeat) {
        // Save the repeat flag
        this->repeat = repeat;

        // Open the file
        file.open(path, std::ios::in | std::ios::binary);
    }

    template <class T>
    bool File<T>::isOpen() {
        // Return the open status
        return file.is_open();
    }

    template <class T>
    void File<T>::close() {
        // Close the file
        file.close();
    }

    template <class T>
    size_t File<T>::source(T* out, size_t maxCount) {
        // Read samples and return number read
        file.read((char*)out, maxCount * sizeof(T));

        // TODO: Handle repeat flag

        // TODO: Check how much was actually read
        return maxCount;
    }

    // Instantiate the class
    template class File<uint8_t>;
    template class File<uint16_t>;
    template class File<uint32_t>;
    template class File<uint64_t>;
    template class File<int8_t>;
    template class File<int16_t>;
    template class File<int32_t>;
    template class File<int64_t>;
    template class File<float>;
    template class File<double>;
    template class File<Complex>;
}