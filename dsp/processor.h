#pragma once
#include <type_traits>
#include "block.h"
#include "stream.h"

namespace dsp {
    // TODO: Deal with the fact that always locking will be slow in hier blocks...

    /**
     * Class representing a DSP kernel taking one input and one output.
     * Dervied classes must be thread-safe by locking the provided `settingsMtx` mutex in any function changing settings.
    */
    template <class IN, class OUT>
    class ProcessorKernel {
    public:
        // Destructor
        virtual ~ProcessorKernel() {}

        // TODO: Copy/Move Constructor/Operator

        /**
         * Acquire a lock to the settings of the kernel. Mandatory if settings are changed in a different thread than the processing function.
         * @return Lock to the settings of the block.
        */
        inline std::lock_guard<std::recursive_mutex> getLock() const {
            return std::lock_guard<std::recursive_mutex>(settingsMtx);
        }

        /**
         * Process samples. This function is NOT thread-safe.
         * @param in Input buffer.
         * @param out Output buffer.
         * @param count Number of samples in the input buffer.
         * @return Number of samples in the output buffer.
        */
        virtual int process(const IN* in, OUT* out, int count) = 0;

    protected:
        /**
         * Mutex to be used for kernel settings.
        */
        mutable std::recursive_mutex settingsMtx;
    };

    template <class IN, class OUT>
    class ProcessorBlock : public Block {
    public:
        // Default constructor
        ProcessorBlock() {
            // TODO: Maybe something to do to prevent bad shit if started?
        }

        /**
         * TODO
        */
        ProcessorBlock(ProcessorSync<IN, OUT>* proc) {
            // Save the pointer to the processor
            this->proc = proc;

            // Set the streams
            setInput(NULL);
            setOutput(NULL);
        }

        /**
         * TODO
        */
        ProcessorBlock(ProcessorSync<IN, OUT>* proc, Stream<IN>* in) {
            // Save the pointer to the processor
            this->proc = proc;

            // Set the streams
            setInput(in);
            setOutput(NULL);
        }

        /**
         * TODO
        */
        ProcessorBlock(ProcessorSync<IN, OUT>* proc, Stream<IN>* in, Stream<OUT>* out) {
            // Save the pointer to the processor
            this->proc = proc;

            // Set the streams
            setInput(in);
            setOutput(out);
        }

        // Destructor
        virtual ~ProcessorBlock() {}

        /**
         * Set the input stream.
         * @param in Input stream.
        */
        void setInput(Stream<IN>* in) {
            // TODO: Lock

            // If the current input if it already was registered
            unregisterInput(_in);

            // TODO: Manage allocating and freeing streams

            // Update the input
            _in = in;

            // Register the new input
            registerInput(_in);
        }

        /**
         * Set the output stream.
         * @param in Output stream.
        */
        void setOutput(Stream<OUT>* out) {
            // TODO: Lock

            // If the current output if it already was registered
            unregisterOutput(_out);

            // TODO: Manage allocating and freeing streams

            // Update the output
            _out = out;

            // Register the new output
            registerOutput(_out);
        }

        Stream<IN>* in() const {
            // TODO: Lock
            return _in;
        }

        Stream<OUT>* out() const {
            // TODO: Lock
            return _out;
        }
    
    private:
        bool run() {
            // Read samples
            auto bufSet = _in->recv();
            if (!bufSet.samples) { return true; }

            // Process samples
            {
                auto lck = proc->getLock();
                proc->process(NULL/*TODO*/, NULL/*TODO*/, 0/*TODO*/);
            }

            // TODO: Write samples
            
            // TODO
            return false;
        }

        ProcessorKernel<IN, OUT>* proc;
        Stream<IN>* _in = NULL;
        Stream<OUT>* _out = NULL;
        bool ownInput = false;
        bool ownOutput = false;
    };
}