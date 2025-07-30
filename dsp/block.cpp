#include "block.h"
#include <stdexcept>

namespace dsp {
    Block::Block() {}

    Block::~Block() {
        // Stop the worker
        stop();
    }

    void Block::start() {
        // Acquire worker variables
        std::lock_guard<std::mutex> lck(workerMtx);

        // Do nothing if the block is already running
        if (_running) { return; }

        // Mark as running
        _running = true;

        // Start the worker thread
        workerThread = std::thread(&Block::worker, this);
    }

    void Block::stop() {
        // Acquire worker variables
        std::lock_guard<std::mutex> lck(workerMtx);

        // Do nothing if the block is not running
        if (!_running) { return; }

        // Set the receive stop flag on all input streams
        for (const auto& input : inputs) {
            input->stopReceiver();
        }

        // Set the send stop flag on all output streams
        for (const auto& output : outputs) {
            output->stopSender();
        }

        // Wait for the thread to exist
        if (workerThread.joinable()) { workerThread.join(); }

        // Clear the receive stop flag on all input streams
        for (const auto& input : inputs) {
            input->clearRecvStop();
        }

        // Clear the send stop flag on all output streams
        for (const auto& output : outputs) {
            output->clearSendStop();
        }

        // Mark as not running
        _running = false;
    }

    bool Block::running() const {
        // Acquire worker variables
        std::lock_guard<std::mutex> lck(workerMtx);

        // Return run state
        return _running;
    }

    void Block::registerInput(StopNotifier* input) {
        // Acquire worker variables
        std::lock_guard<std::mutex> lck(workerMtx);

        // Save to the input list
        inputs.push_back(input);
    }

    void Block::unregisterInput(StopNotifier* input) {
        // Acquire worker variables
        std::lock_guard<std::mutex> lck(workerMtx);
        
        // Find the notifier
        auto it = std::find(inputs.begin(), inputs.end(), input);
        if (it == inputs.end()) { return; }

        // Remove it from the list
        inputs.erase(it);
    }

    void Block::registerOutput(StopNotifier* output) {
        // Acquire worker variables
        std::lock_guard<std::mutex> lck(workerMtx);

        // Save to the output list
        outputs.push_back(output);
    }

    void Block::unregisterOutput(StopNotifier* output) {
        // Acquire worker variables
        std::lock_guard<std::mutex> lck(workerMtx);
        
        // Find the notifier
        auto it = std::find(outputs.begin(), outputs.end(), output);
        if (it == outputs.end()) { return; }

        // Remove it from the list
        inputs.erase(it);
    }

    void Block::worker() {
        // Call the run function repeatedly
        while (run());
    }
}