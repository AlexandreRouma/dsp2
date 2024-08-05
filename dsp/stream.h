#pragma once
#include <mutex>
#include <condition_variable>

#define DSP_DEFAULT_BUFFER_SIZE 1000000

namespace dsp {
    /**
     * Represents a class that can signal to its acting threads to stop. (TODO: Better name)
    */
    class Signaler {
    public:
        /**
         * Notify the sending thread that it should stop.
        */
        virtual void stopSender() = 0;

        /**
         * Clear the sender stop flag to allow restarting the sender thread.
        */
        virtual void clearSendStop() = 0;

        /**
         * Notify the receiving thread that it should stop.
        */
        virtual void stopReceiver() = 0;

        /**
         * Clear the receiver stop flag to allow restarting the sender thread.
        */
        virtual void clearRecvStop() = 0;
    };

    /**
     * Streams allow to exchange samples between two threads.
     * The samples have to be of type (u)int8_t, (u)int16_t, (u)int32_t, (u)int64_t, float, double or Complex.
    */
    template <typename T>
    class Stream : public Signaler {
    public:
        /**
         * Create a stream object.
         * @param bufferSize Number of items in the buffers.
        */
        Stream(int channels = 1, int bufferSize = DSP_DEFAULT_BUFFER_SIZE);

        ~Stream();

        /**
         * Notify the sending thread that it should stop. clearSendStop() must be called once the thread is stopped to clear the stop flag.
        */
        void stopSender();

        // TODO: More consistent naming

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
         * Send a buffer of samples.
         * @param count Number of samples in the send buffer.
         * @return True if the sender thread must exist, false otherwise.
        */
        bool send(int count);

        /**
         * Wait for buffer of samples. May also return in case of a signal to exit. ack() must be called as soon as the receive buffer has been entirely processed.
         * @return Number of samples or -1 if the worker thread must exit.
        */
        int recv();

        /**
         * Acknowledge reception and processing of the samples. Allows sender thread to send a new buffer.
        */
        void ack();

        /**
         * Get the sending buffer.
         * @param channel ID of the channel to get the buffer for.
         * @return Sending buffer.
        */
        T* getSendBuffer(int channel = 0);

        /**
         * Get the receiving buffer.
         * @param channel ID of the channel to get the buffer for.
         * @return Sending buffer.
        */
        const T* getRecvBuffer(int channel = 0);

    private:
        // Sender variables
        std::condition_variable sendCV;
        std::mutex sendMtx;
        bool canSend = true;
        bool stopSend = false;
        T* sendBuf;

        // Receiver variables
        std::condition_variable recvCV;
        std::mutex recvMtx;
        int available = 0;
        bool stopRecv = false;
        T* recvBuf;
    };
}