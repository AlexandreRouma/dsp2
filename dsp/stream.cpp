#include "Stream.h"
#include "./complex.h"
#include "stereo.h"

namespace dsp {
    template <typename T>
    Stream<T>::Stream(int channels, int bufferSize) {
        // Allocate both send and receive buffers aligned by the size of the type
        sendBuf = new T[bufferSize, sizeof(T)];
        recvBuf = new T[bufferSize, sizeof(T)];
    }

    template <typename T>
    Stream<T>::~Stream() {
        // Free both send and receive buffers
        delete[] sendBuf;
        delete[] recvBuf;
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
    bool Stream<T>::send(int count) {
        // Acquire the sender variables
        std::unique_lock<std::mutex> slck(sendMtx);

        // Wait until the sender can send or is notified it should stop
        sendCV.wait(slck, [=](){ return canSend || stopSend; });

        // If asked to stop, return true
        if (stopSend) { return true; }

        // Mark that data can no longer be sent
        canSend = false;

        // Acquire the receiver variables
        std::unique_lock<std::mutex> rlck(recvMtx);

        // Swap buffers
        T* tmp = sendBuf;
        sendBuf = recvBuf;
        recvBuf = tmp;

        // Release the sender variables
        slck.unlock();

        // Set the number of items that are readable
        available = count;

        // Release the receiver variables
        rlck.unlock();

        // Notify the receiver thread that there are items available
        recvCV.notify_all();
    }

    template <typename T>
    int Stream<T>::recv() {
        // Acquire the receiver variables
        std::unique_lock<std::mutex> rlck(recvMtx);

        // Wait until there are items that are readable or the receiver is notified that it should stop
        recvCV.wait(rlck, [=](){ return available || stopRecv; });

        // Return the number of readable items or -1 if the receiver should stop
        return  stopRecv ? -1 : available;
    }

    template <typename T>
    void Stream<T>::ack() {
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
    template class Stream<Stereo>;
}