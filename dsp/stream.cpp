#include "stream.h"
#include "./complex.h"

namespace dsp {
    template <typename T>
    Stream<T>::Stream() {
        // Allocate both send and receive buffer sets
        sendSet = new BufferSet<T>;
        recvSet = new BufferSet<T>;

        // Initialize them to zero
        sendSet->buffer = new T*;
        *sendSet->buffer = NULL;
        recvSet->buffer = new T*;
        *recvSet->buffer = NULL;
        sendSet->capacity = 0;
        recvSet->capacity = 0;
        sendSet->samples = 0;
        recvSet->samples = 0;
    }

    template <typename T>
    Stream<T>::~Stream() {
        // Free both send and receive buffer sets
        delete sendSet;
        delete recvSet;
    }

    template <typename T>
    void Stream<T>::stopSender() {
        // Acquire the sender variables
        std::unique_lock<std::mutex> slck(sendMtx);

        // Set the stop flag
        stopSend = true;

        // Release the sender variables
        slck.unlock();

        // Notify the sender thread
        sendCV.notify_all();
    }

    template <typename T>
    void Stream<T>::clearSendStop() {
        // Acquire the sender variables
        std::unique_lock<std::mutex> slck(sendMtx);

        // Clear the stop flag
        stopSend = false;
    }

    template <typename T>
    void Stream<T>::stopReceiver() {
        // Acquire the receiver variables
        std::unique_lock<std::mutex> rlck(recvMtx);

        // Set the stop flag
        stopRecv = true;

        // Release the receiver variables
        rlck.unlock();

        // Notify the receiver thread
        recvCV.notify_all();
    }

    template <typename T>
    void Stream<T>::clearRecvStop() {
        // Acquire the sender variables
        std::unique_lock<std::mutex> rlck(recvMtx);

        // Clear the stop flag
        stopRecv = false;
    }

    template <typename T>
    const BufferSet<T>& Stream<T>::reserve(size_t bufferSize, size_t channels) {
        // Acquire the sender variables
        std::unique_lock<std::mutex> slck(sendMtx);

        // If the capacity is too small or too large, reallocate 
        if (bufferSize > sendSet->capacity || bufferSize < (sendSet->capacity >> 1) || sendSet->channels != channels) {
            // Free all buffers
            delete[] sendSet->buffer[0];
            delete[] sendSet->buffer;

            // TODO: Use volk instead

            // Reallocate buffers
            sendSet->buffer = new T*[channels];
            T* base = new T[channels * bufferSize];
            for (size_t i = 0; i < channels; i++) {
                sendSet->buffer[i] = &base[bufferSize * i];
            }
        }

        // Return the send buffer set
        return *sendSet;
    }

    template <typename T>
    bool Stream<T>::send(size_t count) {
        // Acquire the sender variables
        std::unique_lock<std::mutex> slck(sendMtx);

        // Update the sample count
        sendSet->samples = count;

        // Wait until the sender can send or is notified it should stop
        sendCV.wait(slck, [=](){ return canSend || stopSend; });

        // If asked to stop, return true
        if (stopSend) { return false; }

        // If trying to send no samples, do nothing
        if (!count) { return true; }

        // Mark that data can no longer be sent
        canSend = false;

        // Acquire the receiver variables
        std::unique_lock<std::mutex> rlck(recvMtx);

        // Swap the buffers sets
        BufferSet<T>* tmp = sendSet;
        sendSet = recvSet;
        recvSet = tmp;

        // Release the sender variables
        slck.unlock();

        // Set the available flag
        available = true;

        // Release the receiver variables
        rlck.unlock();

        // Notify the receiver thread that there are items available
        recvCV.notify_all();

        // Return successfully
        return true;
    }

    template <typename T>
    const BufferSet<T>& Stream<T>::recv() {
        // Acquire the receiver variables
        std::unique_lock<std::mutex> rlck(recvMtx);

        // Wait until there are items that are readable or the receiver is notified that it should stop
        recvCV.wait(rlck, [=](){ return available || stopRecv; });

        // Reset the available flag
        available = false;

        // Zero out the number of samples if asked to stop
        if (stopRecv) { recvSet->samples = 0; }

        // Return the buffer set
        return  *recvSet;
    }

    template <typename T>
    void Stream<T>::flush() {
        // Acquire the sender variables
        std::unique_lock<std::mutex> slck(sendMtx);

        // Mark that data can be sent
        canSend = true;

        // Release the sender variables
        slck.unlock();

        // Notify the sender thread
        sendCV.notify_all();
    }

    // Instantiate the class
    template class Stream<uint8_t>;
    template class Stream<uint16_t>;
    template class Stream<uint32_t>;
    template class Stream<uint64_t>;
    template class Stream<int8_t>;
    template class Stream<int16_t>;
    template class Stream<int32_t>;
    template class Stream<int64_t>;
    template class Stream<float>;
    template class Stream<double>;
    template class Stream<Complex>;
}