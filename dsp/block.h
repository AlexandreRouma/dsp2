#pragma once
#include <thread>
#include <vector>
#include "stream.h"

namespace dsp {
    /**
     * General DSP block class handling the worker thread start/stop operations.
     * All input and output streams of the derived blocks must be registered using the appropriate functions.
    */
    class Block {
    public:
        Block();
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
        bool running();

    protected:
        /**
         * Register an input stream.
         * @param input Input stream to register.
        */
        void registerInput(Signaler* input);

        /**
         * Unregister an input stream.
         * @param input Input stream to unregister.
        */
        void unregisterInput(Signaler* input);

        /**
         * Register an output stream.
         * @param input Output stream to register.
        */
        void registerOutput(Signaler* output);

        /**
         * Unregister an output stream.
         * @param input Output stream to unregister.
        */
        void unregisterOutput(Signaler* output);

        /**
         * Run the DSP code.
         * @return True if the worker thread should stop.
        */
        virtual bool run();

        /**
         * Mutex to be used for block settings.
        */
        std::recursive_mutex settingsMtx;

    private:
        /**
         * Worker thread function.
        */
        void worker();

        // Worker variables
        std::mutex workerMtx;
        std::thread workerThread;
        std::vector<Signaler*> inputs;
        std::vector<Signaler*> outputs;
        bool _running = false;
    };
}