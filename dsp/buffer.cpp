#include "buffer.h"

namespace dsp {
    template <class T>
    Buffer<T>::Buffer() {

    }

    template <class T>
    Buffer<T>::Buffer(size_t size, bool zero = false) {

    }

    template <class T>
    Buffer<T>::Buffer(T* taps, int count) {

    }

    template <class T>
    Buffer<T>::Buffer(const Buffer<T>& b) {

    }

    template <class T>
    Buffer<T>::Buffer(Buffer<T>&& b) {

    }

    template <class T>
    Buffer<T>::~Buffer() {

    }

    template <class T>
    Buffer<T>& Buffer<T>::operator=(const Buffer<T>& b) {

    }

    template <class T>
    Buffer<T>& Buffer<T>::operator=(Buffer<T>&& b) {

    }

    template <class T>
    void Buffer<T>::realloc(size_t size, bool zero = false) {

    }

    template <class T>
    void Buffer<T>::free() {

    }
}