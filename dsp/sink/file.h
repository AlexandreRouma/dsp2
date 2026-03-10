#pragma once
#include <string>
#include <fstream>

namespace dsp::sink {
    template <class T>
    class File {
    public:
        // Default constructor
        File();

        /**
         * Create a file sink and open a file for writing.
         * @param path Path to the file to write to.
         * @param append True to append samples to those already in the file if it exists, False otherwise.
        */
        File(const std::string& path, bool append = false);

        // Destructor
        ~File();

        /**
         * Open a file for writing.
         * @param path Path to the file to write to.
         * @param append True to append samples to those already in the file if it exists, False otherwise.
        */
        void open(const std::string& path, bool append = false);

        /**
         * Check if a file is open.
         * @return True if a file is open, False otherwise.
        */
        bool isOpen();

        /**
         * Close the file if one is open. Does nothing if no file is open.
        */
        void close();

        /**
         * Sink samples.
         * @param in Buffer of samples to sink.
         * @param count Number of samples to sink.
        */
        void sink(const T* in, size_t count);

    private:
        std::ofstream file;
    };
}