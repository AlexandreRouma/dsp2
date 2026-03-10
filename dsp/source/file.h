#pragma once
#include <string>
#include <fstream>

namespace dsp::source {
    template <class T>
    class File {
    public:
        // Default constructor
        File();

        /**
         * Create a file sink and open a file for reading.
         * @param path Path to the file to read from.
         * @param repeat True if the file should seek back to the beginning at the end.
        */
        File(const std::string& path, bool repeat = false);

        // Destructor
        ~File();

        /**
         * Open a file for reading.
         * @param path Path to the file to read from.
         * @param repeat True if the file should seek back to the beginning at the end.
        */
        void open(const std::string& path, bool repeat = false);

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
         * Source samples.
         * @param out Buffer to write the sourced samples to.
         * @param maxCount Maximum number of samples to source.
         * @return Number of samples sourced.
        */
        size_t source(T* out, size_t maxCount);

    private:
        bool repeat = false;
        std::ifstream file;
    };
}