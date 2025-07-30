#pragma once
#include <thread>
#include <mutex>
#include <vector>

namespace dsp {
    /**
     * Interface to be used by any blocking class (stream, mailbox, etc...) to allow cancelling an operation.
    */
    class StopNotifier {
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
     * General DSP block class handling the worker thread start/stop operations.
     * All input and output stop notifiers (usually streams) of the derived blocks must be registered using the appropriate functions.
     * This class is thread-safe.
    */
    class Block {
    public:
        // Default constructor
        Block();

        // Destructor
        virtual ~Block();

        /**
         * Start the block's worker thread.
        */
        void start();

        /**
         * Stop the block's worker thread.
        */
        void stop();

        /**
         * Check wether or not the block's worker thread is running.
        */
        bool running() const;

    protected:
        /**
         * Register an input stop notifier.
         * @param input Input stop notifier to register.
        */
        void registerInput(StopNotifier* input);

        /**
         * Unregister an input stop notifier.
         * @param input Input stop notifier to unregister.
        */
        void unregisterInput(StopNotifier* input);

        /**
         * Register an output stop notifier.
         * @param input Output stop notifier to register.
        */
        void registerOutput(StopNotifier* output);

        /**
         * Unregister an output stop notifier.
         * @param input Output stop notifier to unregister.
        */
        void unregisterOutput(StopNotifier* output);

        // TODO: Pause/Resume for when inputs/outputs change to avoid needing to restart a thread

        /**
         * Run the DSP code.
         * @return False if the worker thread should stop. True otherwise.
        */
        virtual bool run() = 0;

    private:
        /**
         * Worker thread function.
        */
        void worker();

        // Worker variables
        mutable std::mutex workerMtx;
        std::thread workerThread;
        std::vector<StopNotifier*> inputs;
        std::vector<StopNotifier*> outputs;
        bool _running = false;
    };
}