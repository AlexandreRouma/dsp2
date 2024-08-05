#pragma once
#include "stream.h"

namespace gui {
    /**
     * Mailboxes allow to exchange objects between two threads.
    */
    template <typename T>
    class Mailbox : public Signaler {
    public:
        /**
         * Create a mailbox object.
        */
        Mailbox();

        ~Mailbox();

        /**
         * Notify the sending thread that it should stop.
        */
        void stopSender();

        /**
         * Notify the receiving thread that it should stop.
        */
        void stopReceiver();

        /**
         * Send an object.
         * @return True if the sender thread must exist, false otherwise.
        */
        bool send();

        /**
         * Wait for an object. May also return in case of a signal to exit. ack() must be called as soon as the received object has been processed.
         * @return True if the receiver thread must exist, false otherwise.
        */
        bool recv();

        /**
         * Acknowledge reception and processing of the samples. Allows sender thread to send a new buffer.
        */
        void ack();

        /**
         * Get the sending object.
         * @return Sending object.
        */
        T* getSendObject() { return sendObj; }

        /**
         * Get the receiving object.
         * @return Sending object.
        */
        const T* getRecvObject() { return recvObj; }

    private:
        // Sender variables
        std::condition_variable sendCV;
        std::mutex sendMtx;
        bool canSend = true;
        bool stopSend = false;
        T* sendObj;

        // Receiver variables
        std::condition_variable recvCV;
        std::mutex recvMtx;
        bool available = false;
        bool stopRecv = false;
        T* recvObj;
    };
}