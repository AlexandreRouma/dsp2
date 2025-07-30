#pragma once
#include <mutex>
#include <condition_variable>
#include "block.h"

namespace dsp {
    /**
     * Set of buffers and associated metadata.
    */
    template <typename T>
    struct BufferSet {
        /**
         * Sample buffer for each channel.
        */
        T** buffer;

        /**
         * Number of channels, and thus channel buffers.
        */
        size_t channels;

        /**
         * Maximum number of samples that each buffer can contain. This is assigned by Stream<T>::reserve().
        */
        size_t capacity;

        /**
         * Number of valid samples in each buffer. This is assigned by Stream<T>::send().
        */
        size_t samples;
    };

    /**
     * Streams allow to exchange samples between two threads.
     * The samples have to be of type (u)int8_t, (u)int16_t, (u)int32_t, (u)int64_t, float, double or Complex.
     * This class is thread-safe.
    */
    template <typename T>
    class Stream : public StopNotifier {
    public:
        // Default constructor
        Stream();

        // Destructor
        ~Stream();

        /**
         * Notify the sending thread that it should stop. clearSendStop() must be called once the thread is stopped to clear the stop flag.
        */
        void stopSender();

        /**
         * Clear the sender stop flag to allow restarting the sender thread.
        */
        void clearSendStop();

        /**
         * Notify the receiving thread that it should stop. clearRecvStop() must be called once the thread is stopped to clear the stop flag.
        */
        void stopReceiver();

        /**
         * Clear the receiver stop flag to allow restarting the sender thread.
        */
        void clearRecvStop();

        /**
         * Obtain a buffer set for sending.
         * @param bufferSize Number of samples in each channel buffer.
         * @param channels Number of channels.
         * @return Buffer set to use for sending.
        */
        const BufferSet<T>& reserve(size_t bufferSize, size_t channels = 1);

        /**
         * Send a set of sample buffers.
         * @param count Number of valid samples in each channel buffer.
         * @param channels Number of valid channels channels.
         * @return False if the sender thread must exist, true otherwise.
        */
        bool send(size_t count);

        /**
         * Receive a set of sample buffers. May also return in case of a signal to exit, in which case the number of samples in the set is zero.
         * @return Set of sample buffers.
        */
        const BufferSet<T>& recv();

        /**
         * Flush the received buffer. Allows sender thread to send a new buffer.
        */
        void flush();

    private:
        // Sender variables
        std::condition_variable sendCV;
        std::mutex sendMtx;
        bool canSend = true;
        bool stopSend = false;
        BufferSet<T>* sendSet = NULL;

        // Receiver variables
        std::condition_variable recvCV;
        std::mutex recvMtx;
        bool available = false;
        bool stopRecv = false;
        BufferSet<T>* recvSet = NULL;
    };
}