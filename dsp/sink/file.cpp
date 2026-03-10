#include "file.h"
#include "../complex.h"
#include <stdint.h>

// TODO: Thread safety

namespace dsp::sink {
    template <class T>
    File<T>::File() {}

    template <class T>
    File<T>::File(const std::string& path, bool append) {
        // Open the given file
        open(path, append);
    }

    template <class T>
    File<T>::~File() {
        // Close the file in case it's open
        close();
    }

    template <class T>
    void File<T>::open(const std::string& path, bool append) {
        // Open the file
        file.open(path, std::ios::out | std::ios::binary | (append ? std::ios::app : std::ios::trunc));
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
    void File<T>::sink(const T* in, size_t count) {
        // Write the samples to the file
        file.write((char*)in, count * sizeof(T));
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