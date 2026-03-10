#pragma once
#include <thread>
#include "stream.h"
#include "processor.h"
#include <type_traits>

namespace dsp {

    // TODO: Thread safety

    template <class PROC, class T_IN, class T_OUT>
    class SISOWorker : public PROC {
        static_assert(std::is_base_of<SISOProcessor<T_IN, T_OUT>, PROC>::value);
    public:
        // Default constructor
        inline SISOWorker() {}

        /**
         * Create a processor worker from the underlining processor block.
         * @param proc Processor instance.
        */
        inline SISOWorker(PROC&& proc) : PROC(proc) {}

        /**
         * Create a processor worker from the underlining processor block and set its input stream.
         * @param proc Processor instance.
         * @param in Input stream.
        */
        inline SISOWorker(PROC&& proc, dsp::Stream<T_IN>* in) : PROC(proc) {
            // Set the input stream
            setInput(in);
        }

        /**
         * Create a processor worker from the underlining processor block and set its input and/or output stream.
         * @param proc Processor instance.
         * @param in Input stream. Null if unused.
         * @param out Output stream. Null if unused.
        */
        inline SISOWorker(PROC&& proc, dsp::Stream<T_IN>* in, dsp::Stream<T_OUT>* out) : PROC(proc) {
            // Set the input stream if it was given
            if (in) { setInput(in); };

            // Set the output stream if it was given
            if (out) { setOutput(out); };
        }

        // Destructor
        ~SISOWorker() {
            // Stop the worker
            stop();
        }

        // TODO: Copy and move constructors and assignments

        /**
         * Get the input stream.
         * @return Input stream. If one doesn't exist yet, it is created.
        */
        inline dsp::Stream<T_IN>* in() {
            // If it doesn't exists, create it
            if (!_in) {
                // Allocate the stream
                setInput(new dsp::Stream<T_IN>());

                // Mark ownership
                ownIn = true;
            }

            // Return the input stream
            return _in;
        }

        /**
         * Set the input stream. If one had been automatically created, it is freed.
         * @param in New input stream.
        */
        inline void setInput(dsp::Stream<T_IN>* in) {
            // If the input exists and is owned, free it
            if (_in && ownIn) { delete _in; }

            // Save the input
            this->_in = in;

            // Mark non-ownership
            ownIn = false;
        }

        /**
         * Get the output stream.
         * @return Output stream. If one doesn't exist yet, it is created.
        */
        inline dsp::Stream<T_OUT>* out() {
            // If it doesn't exists, create it
            if (!_out) {
                // Allocate the stream
                setOutput(new dsp::Stream<T_OUT>());

                // Mark ownership
                ownOut = true;
            }

            // Return the output stream
            return _out;
        }

        /**
         * Set the output stream. If one had been automatically created, it is freed.
         * @param in New output stream.
        */
        inline void setOutput(dsp::Stream<T_OUT>* out) {
            // If the output exists and is owned, free it
            if (_out && ownOut) { delete _out; }

            // Save the output
            this->_out = out;

            // Mark non-ownership
            ownOut = false;
        } 

        inline void start() {
            // If already running, do nothing
            if (run) { return; }

            // Start the worker thread
            workerThread = std::thread(&SISOWorker<PROC, T_IN, T_OUT>::worker, this);
        }

        inline void stop() {
            // If not running, do nothing
            if (!run) { return; }

            // Set the stop signal
            _in->stopReceiver();
            _out->stopSender();

            // Wait for the thread to exit
            if (workerThread.joinable()) { workerThread.join(); }

            // Clear the stop signal
            _in->clearRecvStop();
            _out->clearSendStop();
        }

        inline bool running() {
            return run;
        }

    private:
        void worker() {
            while (true) {
                // Receive a buffer of samples
                auto inBuf = _in->recv();
                if (!inBuf.samples) { break; }

                // Reserve an output buffer (TODO: Query the proc)
                auto outBuf = _out->reserve(inBuf.samples);

                // Process the samples
                size_t outCount = processSafe(inBuf.buffer[0], outBuf.buffer[0], inBuf.samples);

                // Flush the input buffer
                _in->flush();

                // Send the output samples
                if (!_out->send(outCount)) { break; }
            }
        }

        using PROC::process;

        bool run = false;
        dsp::Stream<T_IN>* _in = NULL;
        dsp::Stream<T_OUT>* _out = NULL;
        bool ownIn = false;
        bool ownOut = false;
        std::thread workerThread;
    };
}